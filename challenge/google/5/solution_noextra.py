import math
import decimal
import numpy as np

def solution(s):
    decimal.getcontext().prec=100
 
    M=[(i*decimal.Decimal(2).sqrt()).to_eng_string().split(".") for i in range(1,10) ]

    r=0
    l=len(s)
    for i, e in enumerate(s):
        l-=1
        for d in range(1,10):
            reps=get_reps(d,i,s)
            val=int(''.join([M[d-1][0],M[d-1][1][:l]]))
            r+=reps*val
    print(r)

#How many times a digit d can appear in the position i of a num as string
def get_reps(d,i,num):
    if d==int(num[i]):
        if i==0:
            return int(num[i+1:])+1
        elif i==len(num)-1:
            return int(num[:i])+1
        else:
            return (10**len(num[i+1:]))*(int(num[:i]))+(int(num[i+1:])+1)
    elif d>int(num[i]):
        if i==0:
            return 0
        elif i==len(num)-1:
            return int(num[:i])
        else:
            return (10**len(num[i+1:]))*int(num[:i])
    else:
        if i==0:
            return 10**len(num[i+1:])
        elif i==len(num)-1:
            return int(num[:i])+1
        else:
            return (10**len(num[i+1:]))*(int(num[:i])+1)


#solution('20')    
#solution('100')     
#solution('1000')
#solution('3500')
solution('25976')
#solution('1%s'%('0'*8))
#solution('1%s'%('0'*100))


    
    
        
        
    

