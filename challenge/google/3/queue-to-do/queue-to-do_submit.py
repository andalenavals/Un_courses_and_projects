#given an initial number start (in top left) a squeare matrix of size length
# is build you must return the xor (^) of the top left diagonal and the elements above

import math

#building cases, the key property is that x^x+1 where x is even is always=1
# and that x^x=0, using this the different cases are reduce to use only some
#elements of the diagonal or bordes
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
