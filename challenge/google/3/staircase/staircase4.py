# How many different stairs can be done using n bricks
# the trick to solve this problem is to use memory to avoid nested loops
#sol with 2 cols, 3 cols+ ...

# if we put in a row the solutions with only two columns, and below we count how many child solutions are there we can observe 

#   * SOLS 2 COLS *  # SOLS 3 COLS  # SOLS 4 COLS  # 
# N  #     No Sols   # N  # No Sols # N  # No Sols #
# 3  # 1             # 6  # 1       # 10 # 1       # 15
# 4  # 1             # 7  # 1       # 11 # 1
# 5  # 1 1           # 8  # 2       # 12 # 2
# 6  # 1 1           # 9  # 2 1     # 13 # 3
# 7  # 1 1 1         # 10 # 3 1     # 14 # 4 1
# 8  # 1 1 1         # 11 # 3 2     # 15 # 5 1
# 9  # 1 1 1 1       # 12 # 4 2 1   # 16 # 7 2
# 10 # 1 1 1 1       # 13 # 4 3 1   #
# 11 # 1 1 1 1 1     # 14 # 5 3 2   #
# 12 # 1 1 1 1 1     # 15 # 5 4 2 1 #
# 13 # 1 1 1 1 1 1   # 16 # 6 4 3 1 #
# 14 # 1 1 1 1 1 1   # 
# 15 # 1 1 1 1 1 1 1 #
# 16 # 1 1 1 1 1 1 1 #  

# Three key points:
# A. Cols in this convinient matrix are repeated shifted dow as many positions as number of columns in the solution.
# B. Final response is just the sum of all the rows associated to a N
# C. the first column in a matrix is the sum of rows of the previous one (however notice N values are shifted)

import math

# given a col1, make matrixes like above where s is the shift parameter (or number of cols)
def make_matrix(col1, s):
    w=int(math.ceil(len(col1)/float(s)))
    ma=[[0]*len(col1)]*w
    ma[0]=col1
    for i in range(w-1):
        ma[i+1]=[0]*s*(i+1) +ma[0][:-s*(i+1)]
    return ma

def make_matrix1(col1, s):
    w=int(math.ceil(len(col1)/float(s)))
    ma=[col1]
    for i in range(w-1):
        ma.append([0]*s*(i+1) +col1[:-s*(i+1)])
    return ma

# given N, get the maximum number of colums a solution could have
#
def max_d(n):
    return int(math.floor(0.5*(math.sqrt(1+8*n)-1)))

def sols1(n):
    col=[1]*(n-2)
    s=0
    for j in range(2, max_d(n)+1):
        t=make_matrix(col, j)
        suma=[sum(e) for e in zip(*t)]
        s+=suma[-1]
        col=suma[:-(j+1)]
    return s

def sols(n):
    col=[1]*(n-2)
    s=0; min_n=2; j=2
    while n > min_n:
        t=make_matrix(col, j)
        suma=[sum(e) for e in zip(*t)]
        s+=suma[-1]
        col=suma[:-(j+1)]
        j+=1
        min_n+=j
    return s

assert sols(200) == 487067745
print(sols(4000))
