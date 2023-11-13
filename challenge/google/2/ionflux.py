import math

def solution(h,q):
    return
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
def Gn2(h):
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



def Gn(h):
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

def get_key_nodes2(h):
    nkeys=2**(h-2)
    gns=Gn(h)
    #print(gns)
    #o=[sum(gns[:n])+1+3*n for n in range(1,nkeys+1)]
    o=[]; s=0
    for n in range(1,nkeys+1):
        s+=gns[n-1]
        o.append(1+3*n+s)
    #print(o)
    return(o)

def get_key_nodes(h):
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



def makeTree(h):
    layers=[[] for i in range(h)]
    n=2**h-1
    q=0


#get_key_nodes2(25)
get_key_nodes(25)
#print(Gn(4))
#Gn(7)
#Gn2(29)



#makeTree3(25)
            

'''
class Layer:
    def __init__(self):
        self.nodes=[]
    def add_node(n):
        
    
class Node:
    def __init__(self, number, child_l=None, child_l=None, father=None ):
        self.number = number #id
        self.child_l=child_l
        self.child_r=child_r
        self.father=father

class Tree:
    def __init__(self, h):
        self.layers=[]
    def fill(h):
        n=2**h-1
        nodes=[]
        for i in range(1,n+1):
            Node(i)

    def add_node(n):
        for i, l in enumerate(self.layers):
            if l.is_empty()|l.have_single_child()|(l.size==2*self.layers[i+1].size):
                l.add_node(n)
                return
'''
            

