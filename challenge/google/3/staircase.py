import math
def number_solutions2(n, t):
    alpha=math.ceil(n*0.5)-1
    s=0 #alpha-t
    for j in range(1,alpha-t+1):
        s+=number_solutions(n-t-j, j+t)+1
    return s

def number_solutions1(n, t):
    #N number of bricks
    #t threshold
    n-=t
    c=0
    while n>t:
        n-=1
        t+=1
        if n>t:
            c+=1
            c+=number_solutions(n, t)
    return c



def number_solutions(n, t):
    n-=t+1
    c=0; t+=1
    while n>t:
        c+=number_solutions(n, t)+1
        n-=1; t+=1
    return c



#n=200
#t=0
#print(number_solutions(n, t))

n=200
t=0
print(number_solutions(n, t))


#for i in range(3,25):
#    print(i, number_solutions(i, 0),number_solutions(i+1, 0)-number_solutions(i, 0))
