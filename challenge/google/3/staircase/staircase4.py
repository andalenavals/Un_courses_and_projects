# How many different stairs can be done using n bricks
# the trick to solve this problem is to use memory to avoid nested loops
# sol with 2 cols, 3 cols+ ...
#

import math

def make_tree(col1, s):
    w=int(math.ceil(len(col1)/float(s)))
    ma=[[0]*len(col1)]*w
    ma[0]=col1
    for i in range(w-1):
        ma[i+1]=[0]*s*(i+1) +ma[0][:-s*(i+1)]
    return ma

def max_d(n):
    return int(math.floor(0.5*(math.sqrt(1+8*n)-1)))

def sols(n):
    col=[1]*(n-2)
    s=0
    for j in range(2, max_d(n)+1):
        t=make_tree(col, j)
        suma=[sum(e) for e in zip(*t)]
        s+=suma[-1]
        col=suma[:-(j+1)]
    return s

print(sols(200))
