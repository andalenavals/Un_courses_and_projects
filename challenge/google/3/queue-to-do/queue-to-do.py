import math

def xorlist(l):
    r=0
    for e in l:
        r^=e
    return r
def xorlist_seq(s):
    i=s[0]
    l=len(s)
    if i%2==0:
        if l%2==0:
            if l%4==0: return 0
            else: return 1 
        else:
            if (l-1)%4==0: return s[-1]
            else: return 1^s[-1]
    else:
        if l%2==0:
            if (l-2)%4==0: return s[0]^s[-1]
            else: return 1^s[0]^s[-1]
        else:
            if (l-1)%4==0: return s[0]
            else: return 1^s[0]
        
 

def solution3(start,length):
    #ids=np.array(range(start,start+length**2))
    ids=[]
    for rind in range(length):
        row=list(range(start,start+length -rind ))
        #ids.append(row)
        #ids.append(xorlist(row))
        ids.append(xorlist_seq(row))
        start+=length
    o=xorlist(ids)
    print(o)
    return o

def solution2(start,length):
    #ids=np.array(range(start,start+length**2))
    r=0
    for rind in range(length):
        row=list(range(start,start+length -rind ))
        r^=xorlist_seq(row)
        start+=length
    print(r)
    return r

def solutionc(start,length):
    if start%2==0:
        if length%2==0:
            if length%4==0: r=0
            else: r=1
            inum=(length-1)*2
            for i in range(length//2):
                r^=inum*(i+1)+start
        else:
            if (length-1)%4==0: r=0
            else: r=1
            inum=length-1
            for i in range(length):
                r^=inum*(i+1)+start
            for i in range(length//2):
                r^=length*(2*i+1)+start
    else:
        r=0
        if length%2==0:
            inum=length-1
            for i in range(length):
                r^=length*(i)+start
            for i in range(length//2):
                r^=inum*(2*i+1)+start
        else:
            for i in range((length+1)//2):
                r^=length*2*i+start
    return r

def solution(start,length):
    r=0
    if start%2==0:
        if length%2==0:
            if length%4>0: r=1
            for i in range(length//2):
                r^=2*(length-1)*(i+1)+start
        else:
            if (length-1)%4>0: r=1
            for i in range(length):
                r^=(length-1)*(i+1)+start
            for i in range(length//2):
                r^=length*(2*i+1)+start
    else:
        if length%2==0:
            for i in range(length):
                r^=length*i+start
            for i in range(length//2):
                r^=(length-1)*(2*i+1)+start
        else:
            for i in range((length+1)//2):
                r^=length*2*i+start
    return r
    
    
2000000000

#solution(3219, 44721)
#solution2(3221, 44720)
print(solution(3221, 44720))
