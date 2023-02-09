import numpy as np
import scipy
from scipy.optimize import fsolve

mu=0.05
sigma=0.1
p=1./100.
C0=100
b=0.5
L=70

def func(x):    
    return p-0.5*(1+scipy.special.erf((x-mu)/(sigma*np.sqrt(2))))

def X(C,r,b,L):
    return (L-C)/((1+b)*r)

def Verbose(C,B,BI,I,CNI, P):
    print("Borrowed money: ", BI)
    print("Acumulated borrowed money:", B)
    print("Investment: ", I)
    print("Save money: ", CNI)
    print("Profit: ", P)
    print("Capital: ", C)


def get_profit(returns,r,verbose=False):
    
    B=0
    C=C0
    if verbose: print( "Initial capital:", C0)
    for mu in returns:
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
            if verbose: print("Game over limit exceeded")
            return PROFIT
        
    return PROFIT

def plot_hist(x, filename=None):
    import matplotlib.pyplot as plt
    plt.style.use('style.mplstyle')

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
    
    
    #maximum allow loss
    r=fsolve(func,-0.1826)[0]
    print(r)


    returns=[mu]*5
    finalprofit=get_profit(returns,r,verbose=True)
    print(finalprofit)

    
    nexp=100000
    nperiod=5
    prof_list=[]; returns_list=[]
    for n in range(nexp):
        returns=np.random.normal(loc=mu, scale=sigma, size=nperiod)
        finalprofit=get_profit(returns,r)
        prof_list.append(finalprofit)
        
    print(np.sum(np.array(prof_list)<-30)/(nexp*nperiod), "Game overs")
    plot_hist(np.array(prof_list), "profit_distribution_%iruns.png"%(nexp))
    

    
if __name__ == "__main__":
    main()
