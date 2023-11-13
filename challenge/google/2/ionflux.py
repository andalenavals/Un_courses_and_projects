import math
import numpy as np


def solution(h,q):
    #return list(map(find_father,  [h]*len(q), q))
    return [find_father(h,x) for x in q]

def find_father(h,x):
    r=math.log2(x+1)
    u= 2**(int(r)+1)-1
    v= 2**int(r)-1
    if r%1==0:
        o=u
    else:
        if x==u-1 : return u
        x-= v
        o=find_father(int(r), x)+v
    if o>2**h-1: return -1
    return o



#A=list(np.random.randint(1,2**30-1,size=10000))  
#solution(30,A)
    
for i in range(1,16):
    print(i, find_father(4, i))

#print(find_father(30, 1070001824))

print(solution(5,[19,14,28]))
print(solution(3,[7,3,5,1]))

'''
def find_father(h,x):
    r=math.log2(x+1)
    ceil=int(r)
    top=int(r)+1
    if r%1==0:
        o= 2**top-1
    else:
        if x==2**top -2: return 2**top-1
        x-=2**(ceil)-1
        o=find_father(ceil, x)
        o+=2**(ceil)-1
    if o>2**h-1: return -1
    return o
'''



'''
def makeTree2(h):
    layers=[[] for i in range(h)]
    n=2**h-1
    q=0
    for i in range(1,n+1):
        for j in range(q,-1,-1):
            if j==0:
               layers[j].append(i)
               q=j+1
            if 2*(len(layers[j])+1)==len(layers[j-1]):
                layers[j].append(i)
                q=j+1
                break    
    #print(layers)
'''

'''
def makeTree3(h):
    layers=[[] for i in range(h)]
    n=2**h-1
    kcount=1
    keynode=1
    j=0
    for i in range(1,n+1):
        if i==keynode:
            layers[0].append(i)
            keynode+=3
            keynode+=get_times_div2(kcount)
            kcount+=1
            j=0
        else:
            layers[j].append(i)
            j+=1        
    #print(layers)
def get_times_div2(x):
    i=0
    while x%2==0:
        x*=0.5
        i+=1
    return i
'''

'''
def Gn3(h):
    nkeys=2**(h-2)
    keynodes=[0]*nkeys
    for i in range(1, h-1):
        m=(2**i)
        assert nkeys%m==0
        for j in range(nkeys//m):
            keynodes[(2**i)*(j+1)-1]+=1
    #print(keynodes)
    return keynodes
'''

'''
def get_key_nodes2(h):
    nkeys=2**(h-2)
    o=[]; s=0
    for n in range(nkeys):
        s+=count_adjent_ones(bin(n))
        o.append(1+3*(n+1)+s)
    #print(o)
    return(o)
def count_adjent_ones(a):
    i=0
    for s in a[::-1]:
        if s=='1': i+=1
        else: return i
'''

'''
def get_key_nodes2(h):
    knodes=[1]
    for j in range(2,h):
        knodes+=[l+2**j-1 for l in knodes]
    #print(knodes)
    return(knodes)
'''

'''
def Gn3(h):
    nkeys=2**(h-2)
    gn=[[i]*int(nkeys*0.5**(i+1)) for i in range(h-2) ]
    gn[-1].append(gn[-1][0]+1)
    while len(gn)>1:
        c=zipper(gn[-2:])
        del gn[-2:]
        gn.append(c)
    #print(gn)
    return gn[0]

def zipper(L):
    a,b=L
    #assert len(a)==len(b)
    #c=[0]*2*len(a)
    c=[0]*(len(a)+len(b))
    c[0::2]=a
    c[1::2]=b
    return c

def get_key_nodes3(h):
    nkeys=2**(h-2)
    gns=Gn3(h)
    #print(gns)
    #o=[sum(gns[:n])+1+3*n for n in range(1,nkeys+1)]
    o=[]; s=0
    for n in range(1,nkeys+1):
        s+=gns[n-1]
        o.append(1+3*n+s)
    #print(o)
    return(o)
'''

'''
def get_key_nodes(h):
    nkeys=2**(h-2)
    gns=Gn(h)
    o=[]; s=0
    for n in range(1,nkeys+1):
        s+=gns[n-1]
        o.append(1+3*n+s)
    #print(o)
    return(o)

def Gn(h):
    m=h-2
    nkeys=2**m
    a=[m-1, m]
    for i in range(m-1,0,-1):
        b=[i-1]*int(nkeys*0.5**(i))
        c=[0]*(len(a)+len(b))
        c[0::2]=b
        c[1::2]=a
        a=c
    #print(a)
    return a
'''



