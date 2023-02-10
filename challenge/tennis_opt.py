import numpy as np
import itertools
import copy
from datetime import datetime
from scipy import optimize

def f2(s):
    return s[1]/(s[1]+s[0])

def get_combinations(s,si):
    aux=0
    index=np.array(range(len(s)))
    k=int(np.log2(len(s)))
    index=index.reshape([2]*k)
    for a in itertools.product([1,0],repeat=k):
        axis=np.array(range(k))[np.array(a)==1]
        ind=np.flip(index, axis=axis).reshape(len(s))
        aux+=f2([s[ind[-1]],si])*F(s[ind])
    return aux
def F(s):
    if len(s)==2: return f2(s)
    return F(s[-len(s)//2:])*get_combinations(s[:len(s)//2],si=s[-1])

def plot_scatter(x,y, filename=None):
    import matplotlib.pyplot as plt
    plt.style.use('style.mplstyle')

    fig,ax = plt.subplots()

    ax.scatter(x,y)
    ax.set_xlabel(r"rounds $k$")
    ax.set_ylabel(r"Log($t$)")
    #ax.set_yscale('log')
    #ax.set_xscale('log')
    params, params_covariance = optimize.curve_fit(test_func, x, y,
                                               p0=[2, 2])
    print(params)
    ax.plot(x, test_func(x, params[0], params[1]),
            label=r'Log($t$)=%.2f$k$ %.2f'%(params[0],params[1]))
    ax.legend()
    print("estimated time for k=16",np.exp(test_func(16, params[0], params[1])))
    fig.tight_layout()
    if filename is not None:
        fig.savefig(filename,dpi=200)
    plt.close(fig)

def test_func(x, a, b):
    return a*x+b
def main():
    kmax=9
    smax=10
    #skills=np.random.uniform(1,smax,2**kmax)
    skills=np.array([1.0]*(2**kmax))
    times=[]
    rounds=np.array(range(1,kmax))
    for k in rounds:
        n=2**k
        starttime = datetime.now()
        aux=F(skills[-n:])
        endtime = datetime.now()
        last=1e3*(endtime - starttime).total_seconds()
        print("Tournament with %i player took %.3f ms"%(n, last))
        times.append(last)

    plot_scatter(rounds, np.log(times), "time.png")

        

if __name__ == "__main__":
    main()
