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
def Get_combinations(s,si,err=0.0):
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


def get_combinations(s,si,err=0.0):
    aux=0
    k=int(np.log2(len(s)))
    index=np.array(range(2**k)).reshape([2]*k)
    #sorting to process more likely first
    for a in np.argsort(-s):
        axis=np.where(np.concatenate(np.where(index==a))==0)[0]
        ind=np.flip(index, axis=axis).reshape(2**k)
        cont=f2([s[ind[-1]],si])*F(s[ind], err=err)
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
    #skills=np.array([10., 10., 10.,  1., 10.,  2., 10. , 1.])
    #skills = [3.4351751254046268, 7.506908579495099, 4.172984889649188, 2.8252811276015697, 7.851169979771698, 5.1640054754971505, 6.084822297295582, 2.4735577378914817, 4.9146353594698855, 7.93259893658587, 3.1664485420418442, 4.652253938862437, 3.6386354065424635, 2.7966011110176923, 8.000307921228647, 7.7089540024487455]
    #skills=np.array(skills)

    
    starttime = datetime.now()
    prob=F(skills,err=1.e-3)
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
