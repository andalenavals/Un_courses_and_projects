import numpy as np
import itertools
import copy
from datetime import datetime

def f2(s):
    return s[1]/(s[1]+s[0])

def get_indexes(k):
    #get combinations for games
    #return (2**k,2**k) array 
    index=np.array(range(2**k))
    index=index.reshape([2]*k)
    ind_list=[]
    for a in itertools.product([1,0],repeat=k):
        axis=np.array(range(k))[np.array(a)==1]
        ind=np.flip(index, axis=axis).reshape(2**k)
        ind_list.append(ind)
    return np.array(ind_list)

def get_combinations(s,si,err=0.0):
    aux=0
    k=int(np.log2(len(s)))
    #sorting to process more likely first
    ind_list=get_indexes(k)[np.argsort(-s)]
    for ind in ind_list:
        cont=f2([s[ind[-1]],si])*F(s[ind])
        if cont < err: return aux
        #print(ind, cont)
        aux+=cont
    return aux
def F(s, err=0.0):
    if len(s)==2: return f2(s)
    return F(s[-len(s)//2:],err=err)*get_combinations(s[:len(s)//2],s[-1],err=err)
    


def main():
    k=7
    smax=10
    skills=np.random.uniform(1,smax,2**k)
    #skills=np.array([1.0]*(2**k))
    n=2**k

    starttime = datetime.now()
    prob=F(skills,err=1.e-15)
    endtime = datetime.now()
    last=1e3*(endtime - starttime).total_seconds()
    print("Final probability:", prob, "time: %.3f ms"%(last))
    starttime = datetime.now()
    prob=F(skills)
    endtime = datetime.now()
    last=1e3*(endtime - starttime).total_seconds()
    print("Final probability:", prob, "time: %.3f ms"%(last))
    

if __name__ == "__main__":
    main()
