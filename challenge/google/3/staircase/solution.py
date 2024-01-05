import math
def make_matrix(col1, s):
    w=int(math.ceil(len(col1)/float(s)))
    ma=[col1]
    for i in range(w-1):
        ma.append([0]*s*(i+1) +col1[:-s*(i+1)])
    return ma
def solution(n):
    col=[1]*(n-2)
    s=0
    for j in range(2, int(math.floor(0.5*(math.sqrt(1+8*n)-1)))+1):
        t=make_matrix(col, j)
        suma=[sum(e) for e in zip(*t)]
        s+=suma[-1]
        col=suma[:-(j+1)]
    return s
