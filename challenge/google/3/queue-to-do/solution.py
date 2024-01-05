import math
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
