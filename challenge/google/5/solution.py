import math
import decimal
import numpy as np

def solution(s):
    decimal.getcontext().prec=100
 
    M=[(i*decimal.Decimal(2).sqrt()).to_eng_string().split(".") for i in range(1,10) ]

    A=np.zeros((len(s),10))
    for i,e in enumerate(s):
         A[i][1:int(e)+1]=[ float('.'.join([ ''.join([ M[j][0],M[j][1][:len(s)-i-1] ]), M[j][1][len(s)-i-1:]]) ) for j in range(int(e))]

    if len(A)==1: return str(int(np.floor(A).sum()))

    aux=A[0]
    for i in range(len(A)-1):
        aux=np.add.outer(aux,A[i+1])
    return str(int(np.floor(aux).sum()))    


    

print(solution('9'))
print(solution('99'))
print(solution('999'))
print(solution('9'*7))
print(solution('9'*9))
#print(solution('9'*90))
#solution('20')    
#solution('100')     
#solution('1000')
#solution('3500')
#solution('25976')
#solution('1%s'%('0'*8))
#solution('1%s'%('0'*100))


    
    
        
        
    

