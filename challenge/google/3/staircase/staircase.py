import math
def number_solutions2(n, t):
    alpha=math.ceil(n*0.5)-1
    s=0 #alpha-t
    for j in range(1,alpha-t+1):
        s+=number_solutions2(n-t-j, j+t)+1
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
            c+=number_solutions1(n, t)
    return c

def number_solutions(n, t):
    n-=t+1
    c=0; t+=1
    while n>t:
        c+=number_solutions(n, t)+1
        n-=1; t+=1
    return c

def number_solutions_opt(n):
    r=alphai(n,2)
    a=alphai(n,3)
    i=3
    nind=1
    while a>0:
        for j in range(nind,0, -1):
            for k in range(1, alphai(n,j+2)+1 ):
                continue
        nind+=1
        
        i+=1
        a=alphai(n,i)
    print(alphas)
        



    
def alphai(n,i):
    #i is the number of cols
    #alphai is the column index up to which the sum should go
    return math.ceil((n+1-0.5*i*(i+1))/i)

def nsols_3d(n):
    b=alphai(n,3)
    aux=b*math.floor(0.5*(n-1))-0.25*3*b*(b+1)
    if n%2==0:
        aux+=0.5*(alphai(b,2)+1)
    else:
        aux-=0.5*(alphai(b,2)+1)
    return int(aux)
           
def get_nsols_with_dcols(n, d):
    #n number of bricks
    #d number of digits (columns in the stair)
    # return # number of solutions having d digits
    
    if d==1:
        if n<=0: return 0
        else: return 1
    
    elif d==2:
        if n<=2: return 0
        else: return int(math.ceil(0.5*(n-2)))

    elif d==3:
        if n<=5 : return 0
        else: return nsols_3d(n)
    
    r=get_nsols_with_dcols(n-d, d-1)
    if 2*n>=d*(d+1):
        r+=get_nsols_with_dcols(n-d, d)
    return r

def max_d(n):
    return int(math.floor(0.5*(math.sqrt(1+8*n)-1)))

def solution(n):
    return sum([get_nsols_with_dcols(n,i) for i in range(2,max_d(n)+1)])


print(solution(200))

#for i in range(3,22):
#    print(i, [get_nsols_with_dcols(i, d) for d in range(2,6)], max_d(i))

#for i in range(3,22):
#    print(i, nsols_3d(i), sum([get_nsols_with_dcols(i,d) for d in range(2,max_d(i)+1)]), number_solutions(i,0))

#for i in range(3,22):
#    print(i, nsols_3d(i))


            
#print(sum([get_nsols_with_dcols(200, d) for d in range(2,max_d(200)+1)]))


#n=200
#t=0
#print(number_solutions(n, t))

#n=200
#t=0
#print(number_solutions(n, t))


#for i in range(3,25):
#    print(i, number_solutions(i, 0))
