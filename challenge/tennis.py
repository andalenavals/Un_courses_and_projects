import numpy as np
import itertools
import copy

def f2(s):
    return s[1]/(s[1]+s[0])
def f4(s):
    return f2(s[-2:])*(f2(s[[0,3]])*f2(s[[1,0]])+f2(s[[1,3]])*f2(s[[0,1]]))
def f8(s):
    return f4(s[-4:])*(f2(s[[0,-1]])*f4(s[[3,2,1,0]])+f2(s[[1,-1]])*f4(s[[3,2,0,1]])+f2(s[[2,-1]])*f4(s[[0,1,3,2]])+f2(s[[3,-1]])*f4(s[[0,1,2,3]]))

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


def f(players, si):
    ''' this function get the probability to win a branch for all the players
    and return the sum divided by si+sj

    players: list of skills sj of players
    '''
    
    n=len(players)
    n_nodes=n-1
    assert n>=2 #subtree must have at least two players
    k=np.log2(n) #number of rounds
    assert k%1==0
    
    index=[2**l -1 for l in range(int(k)+1)]; index.reverse()

    q_list=[]
    for a in itertools.product([1,0],repeat=n_nodes): #loop for all possible combinations
        prob_layer=[]; players_lay=copy.deepcopy(players); 
        #for i,j in itertools.pairwise(index): #propagate through layers
        for i,j in zip(index,index[1:]):
            selector=np.concatenate([s for s in zip(np.array(a)[j:i], 1^np.array(a)[j:i]) ])
            skillpair=np.concatenate([ [sum(players_lay[2*h:2*(h+1)])]*2 for h in range(len(players_lay)//2)])
            skillpair*=selector; skillpair=skillpair[skillpair !=0]
            players_lay*=selector; players_lay=players_lay[players_lay !=0]
            prob_layer.append(players_lay/skillpair)
        qj=np.prod(np.concatenate(prob_layer))
        qj/=si+players_lay
        q_list.append(qj)
    out=np.sum(q_list)
    assert out <1
    return out
            

def main():
    
    k=6
    n=2**k
    smax=10
    skills=np.random.uniform(1,smax,n)
    print(skills)
    print("Last player with skill %.2f has %.16f probability to win the tourment "%(skills[-1], F(skills)))

    si=skills[-1]
    p0=si/(si+skills[-2])
    
    #indexes characterizing subtree
    count=0; subtree=[]
    index=[n-2**l for l in range(1,k+1)];
    
    #for i,j in itertools.pairwise(index):
    for i,j in zip(index,index[1:]):
        print("Doing subtree %i"%(count))
        subtree.append(f(skills[j:i],si)*si)
        count+=1
    fp=np.product(subtree)*p0
    print("Last player with skill %.2f has %.16f probability to win the tourment "%(si, fp))
    

if __name__ == "__main__":
    main()
