import math
import numpy as np

def alphai(n,i):
    return int(math.ceil((n+1-0.5*i*(i+1))/i))

def sols_1d(n):
    return [alphai(e,2) for e in range(3,n)]

'''
def sols_1d_alt(n):
    w=alphai(n,2)
    
    ma=[[0]*(n-2)]*w
    for i,c in enumerate(ma):
        c[2*i:]=[1]*(n-2-2*i)
        print(c[2*i:])
    print(ma)
    print(ma)
    ma[0]=[1]*(n-2)
    print(ma)
    for i in range(w):
        ma[i+1][2*i:]=ma[i][2*i:]
        print(ma)

    return ma
'''

'''
def sols_1d_alt(n):
    w=alphai(n,2)
    ma=np.array([[0]*(n-2)]*w)
    ma[0,:]=1
    for i in range(len(ma)-1):
        ma[i+1,2*(i+1):]=ma[i,2*(i+1):]
    return np.sum(ma,axis=0)
'''

def make_tree_py3(col1, s):
    w=int(math.ceil(len(col1)/s))
    ma=np.array([[0]*len(col1)]*w)
    ma[0,:]=col1
    for i in range(w-1):
        ma[i+1,s*(i+1):]=ma[0,:-s*(i+1)]
    return ma


def make_tree(col1, s):
    # col1: first col
    # s: shift
    w=int(math.ceil(len(col1)/float(s)))
    ma=np.array([[0]*len(col1)]*w)
    ma[0,:]=col1
    for i in range(w-1):
        ma[i+1,s*(i+1):]=ma[0,:-s*(i+1)]
    return ma

def max_d(n):
    return int(math.floor(0.5*(math.sqrt(1+8*n)-1)))

def sols(n):
    col=[1]*(n-2)
    s=0
    for j in range(2, max_d(n)+1):
        t=make_tree(col, j)
        #print(t)
        suma=np.sum(t, axis=0)
        s+=suma[-1]
        col=suma[:-(j+1)]
    return s
        #print(j, s)

#make_tree([1,1,2,2,3,3,4,4,5,5,6,6], 3)

#make_tree([1]*1,2)
#make_tree([1]*3,2)

print(sols(14))
#for n in range(3,22):
#    print(sols(n))
#print(max_d(17))

#n=200
#r=sols_1d_alt(n)
#r=sols_1d(n)
#sols_1d(9)
