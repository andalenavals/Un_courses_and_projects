def solution(l,t):
    for i,e in enumerate(l):
        s=0
        for j,f in enumerate(l[i:]):
            s+=f
            if s==t: return [i,j+i]
            if s>t: break
    return [-1,-1]

