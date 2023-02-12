import numpy as np
import scipy
from scipy.optimize import fsolve

mu=0.05    # returns distribution mean
sigma=0.1 # returns distribution std
p=0.01     # probality of wealth < L
C0=100.    # initial capital
b=0.5      # percentage of borrow possible
L=70.      # Minimum allowed wealth
N=5        #number of years

# CDF of a gaussian
def func(x):    
    return p-0.5*(1+scipy.special.erf((x-mu)/(sigma*np.sqrt(2))))

# see document
def X(C,r,b,L):
    return (L-C)/((1+b)*r)

#Just a quick logger.
def Verbose(C,B,BI,I,CNI, P):
    print("Borrowed money: ", BI)
    print("Acumulated borrowed money:", B)
    print("Investment: ", I)
    print("Save money: ", CNI)
    print("Profit: ", P)
    print("Wealth: ", C0+P)
    print("Capital: ", C, "\n")

def get_profit(returns,r,verbose=False):
    '''
    returns: list of returns
    r: minimum allowed return
    '''
    B=0
    C=C0
    if verbose: print( "Initial capital:", C0)
    for i, mu in enumerate(returns):
        CI=X(C-B,r,b,L)  # capital invested
        CNI=C-CI         # capital no invested
        if CI>C:
            assert CNI<0
            CI=C; CNI=0
        BI=b*CI          # borrowed money invested
        I=CI+BI          # total invesment for a year
        C=I*(1+mu)+CNI   # new capital    
        B+=BI            # accumulated borrowed money
        PROFIT=C-B-C0
        if verbose: Verbose(C,B,BI,I, CNI,PROFIT)
        if C0+PROFIT<L:
            if verbose: print("Game over limit exceeded, WEALTH %.3f"%(C0+PROFIT))
            assert mu < r
            return PROFIT, i+1
    return PROFIT, len(returns)

def plot_hist(x, filename=None):
    import matplotlib.pyplot as plt
    #plt.style.use('style.mplstyle')

    fig,ax = plt.subplots()
    
    histxkwargs = {"histtype":"stepfilled", "bins":100, "ec":"none", "color":"gray", "range":None, "log":False, "density":False}
    ax.hist(x, **histxkwargs)
    ax.set_xlabel("Profit")
    med=np.median(x)
    ax.axvline(med, color='blue', lw=1.5,ls="-", label="Median: %.2f"%(med))
    mean=np.mean(x)
    ax.axvline(mean, color='red', lw=1.5,ls=":", label="Mean: %.2f"%(mean))
    percs=[np.percentile(x,q) for q in [2.3,15.9, 50.0, 84.1, 97.7]]
    #for l in percs:
    #    ax.axvline(l, color='blue', lw=0.5)
    #ax.axvspan(percs[0], percs[1] , alpha=0.1, color='blue')
    #ax.axvspan(percs[-2], percs[-1] , alpha=0.1, color='blue')
    ax.axvspan(percs[1], percs[-2] , alpha=0.2, color='blue', label=r"68$\%$ percentile")
    #ax.set_xlim([-150,600])

    leg=ax.legend(loc='best', frameon=False)
    fig.canvas.draw()
    #plt.pause(100)
    legpos=leg.get_window_extent()
    ax.annotate(r"P(profit $<0$): %.3f"%(np.sum(x<0)/len(x)), xy=(legpos.p0[0],legpos.p1[1]))
    ax.annotate(r"E(profit): $%.1f^{+%.1f}_{%.1f}$"%(percs[2],percs[-2]-percs[2], percs[1]-percs[2] ), xy=(legpos.p0[0],legpos.p1[1]+1000))
  
    fig.tight_layout()
    if filename is not None:
        fig.savefig(filename,dpi=200)
    plt.close(fig)
    
def main():
    #Getting minimum allowed loss
    r=fsolve(func,-0.1826)[0]
    print("\n","Minimum allowed return is :", r, "\n")

    returns=[mu]*N
    finalprofit, cycles=get_profit(returns,r,verbose=True)
    print("*"*40)
    print("Final profit: ",finalprofit)
    print("*"*40, "\n")

    # EXTRA
    # Drawing from the distribution
    nexp=int(1e+5)
    print("Doing experiment with %i variable returns"%(nexp))
    
    prof_list=[]; cyc=0
    for n in range(nexp):
        returns=np.random.normal(loc=mu, scale=sigma, size=N)
        finalprofit, cycles=get_profit(returns,r)
        prof_list.append(finalprofit)
        cyc+=cycles

    print("Game overs %.6f percent"%(100*np.sum(np.array(prof_list)<-30)/(cyc)), "\n")
    plot_hist(np.array(prof_list), "profit_distribution_%iruns.png"%(nexp))
    print("Notice that percentage of game overs does not match 1.0 percent. This is because the first investment was maximal and represented a risk lower than 1.0 percent. In a circunstance where there is not maximal investments, for example set sigma 0.2. The percentage of game over will be 1.0 percent \n")

    
if __name__ == "__main__":
    main()
