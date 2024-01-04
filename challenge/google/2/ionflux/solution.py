import math
def solution(h,q):
    return [find_father(h,x) for x in q]

def find_father(h,x):
    r=math.log2(x+1)
    u= 2**(int(r)+1)-1
    v= 2**int(r)-1
    if (r%1==0)|(x==u-1): return u
    else:
        x-= v
        o=find_father(int(r), x)+v
    if o>2**h-1: return -1
    return o
