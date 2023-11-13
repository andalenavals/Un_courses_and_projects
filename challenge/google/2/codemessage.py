def solution(l,t):
    assert len(l)>=1
    assert len(l)<=100
    assert isinstance(t,int)
    assert t>0
    assert t<=250
    r=find(l,t)
    assert len(r)==2
    assert r[0]<=r[1]
    return r

def find(l,t):
    for i,e in enumerate(l):
        assert e>0
        assert e<=100
        if e==t:
            return [i,i]
        elif e>t:
            continue
        else:
            s=0; j=i
            while (s<t)&(j<len(l)) :
                s+=l[j]
                j+=1
            if s==t:
                return [i,j-1]

            if i==len(l)-1:
                return [-1,-1]

def tests():
    L=[4,3,10,2,8]
    T=12
    print(solution(L,T))
    assert solution(L,T)==[2,3]

    L=[1,2,3,4]
    T=15
    print(solution(L,T))
    assert solution(L,T)==[-1,-1]
    print("Sucess")


tests()

