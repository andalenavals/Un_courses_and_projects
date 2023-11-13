import numpy as np
import itertools
import copy
from datetime import datetime

def f2(s):
    return s[1]/(s[1]+s[0])

def get_combinations(s,si,err=0.0, depth=1, app=True):
    aux=[]
    k=int(np.log2(len(s)))
    index=np.array(range(2**k)).reshape([2]*k)
    #sorting to process more likely first
    for a in np.argsort(-s):
        axis=np.where(np.concatenate(np.where(index==a))==0)[0]
        ind=np.flip(index, axis=axis).reshape(2**k)
        #cont=trim(np.outer(F(s[ind],err=err,depth=depth), f2([s[ind[-1]],si])).ravel(), err=err)
        cont=np.outer(F(s[ind],err=err,depth=depth,app=app), f2([s[ind[-1]],si])).ravel()
        aux.append(cont)
    return np.concatenate(aux)

#def trim(a,err=0.0):
#    return a[a>err]

def trim(a,err=0.0, app=True):
    sort=-np.sort(-a)
    if app: sort=sort[:1000]
    return sort

def F(s, err=0.0, depth=1, app=True):
    #print("Hola:", depth)
    if len(s)==2: return np.array([f2(s)])
    #R=trim(F(s[-len(s)//2:],err=err,depth=depth+1),err=err)
    #L=trim(get_combinations(s[:len(s)//2],s[-1],err=err, depth=depth+1),err=err)
    R=F(s[-len(s)//2:],err=err,depth=depth+1,app=app)
    L=get_combinations(s[:len(s)//2],s[-1],err=err, depth=depth+1,app=app)
    #print(R,L, depth)
    #return trim(np.outer(R,L).ravel(),err=err, app=app)
    return trim(np.outer(R,L).ravel(),err=err, app=app)
    


def main():
    import tennis_optimized
    k=5
    smax=10
    #skills=np.random.uniform(1,smax,2**k)
    skills=np.array([1.0]*(2**k))
    #skills=np.random.choice([1.0, 2.0,10],2**k)
    #skills=np.array(range(1,17))
    #skills=np.array(range(1,int(2**k)+1))
    print("skills =", list(skills))
 
    '''
    starttime = datetime.now()
    prob=F(skills,err=1.e-15)
    #print(list(prob))
    prob=np.sum(prob)
    endtime = datetime.now()
    last=1e3*(endtime - starttime).total_seconds()
    print("Final probability:", prob, "time: %.3f ms"%(last))
    '''
    
    '''
    starttime = datetime.now()
    prob=F(skills,err=0.0)
    #print(prob)
    #print(list(prob))
    prob=np.sum(prob)
    endtime = datetime.now()
    last=1e3*(endtime - starttime).total_seconds()
    print("Final probability:", prob, "time: %.3f ms"%(last))
    '''
    

    starttime = datetime.now()
    prob=F(skills,err=0.0,app=False)
    #print(prob)
    print(list(prob[-2020:-2000]), sum(prob[-20:]), len(prob))
    prob=np.sum(prob[:-10000])
    endtime = datetime.now()
    last=1e3*(endtime - starttime).total_seconds()
    print("Final probability:", prob, "time: %.3f ms"%(last))

    starttime = datetime.now()
    prob=tennis_optimized.F(skills,err=0.0)
    endtime = datetime.now()
    last=1e3*(endtime - starttime).total_seconds()
    print("Final probability:", prob, "time: %.3f ms"%(last))
    
    
  
    

if __name__ == "__main__":
    main()
