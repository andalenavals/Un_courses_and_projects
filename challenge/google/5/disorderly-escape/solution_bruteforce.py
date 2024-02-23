import itertools
import copy

def solution(w, h, s):
    # Your code here

    '''
    a1=[[0,0],[0,0]]
    a2=[[1,0],[0,0]]
    a3=[[1,1],[0,0]]
    a4=[[0,1],[0,1]]
    a5=[[0,1],[1,0]]
    a6=[[0,1],[1,1]]
    a7=[[1,1],[1,1]]

    fund=[a1,a2,a3,a4,a5,a6,a7]

    al=set()
    for f in fund:
        al=al.union(set(get_combinations(f)))
    print(len(al))
    assert len(al)==2**4
    '''



    
    a0=[[0,0],[0,0]]
    a1=[[1,1],[1,1]]
    a2=[[2,2],[2,2]]
    a20=[[1,2],[1,1]]
    a21=[[2,1],[2,2]]
    a22=[[1,1],[2,2]]
    a23=[[1,2],[1,2]]
    a26=[[1,2],[2,1]]
    
    a3=[[1,0],[0,0]]
    a4=[[2,0],[0,0]]

    a5=[[1,1],[0,0]]
    a6=[[2,2],[0,0]]
    a7=[[1,2],[0,0]]
    
    a8=[[0,1],[0,1]]
    a9=[[0,2],[0,2]]
    a10=[[0,1],[0,2]]

    a11=[[0,1],[1,0]]
    a12=[[0,2],[2,0]]
    a13=[[0,2],[1,0]]

    a14=[[0,1],[1,1]]
    a17=[[0,1],[2,1]]
    a18=[[0,1],[2,2]]
    a19=[[0,1],[1,2]]
    
    a15=[[0,2],[2,2]]
    a16=[[0,2],[1,1]]
    a24=[[0,2],[1,2]]
    a25=[[0,2],[2,1]]
    

    fund=[a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26]

    al=set()
    for f in fund:
        print(len(al))
        al=al.union(set(get_combinations(f)))
    print(len(al))
    assert len(al)==3**4
    

    
    
    #comb=get_combinations(a)
    #print(set(comb))

def get_combinations(a):
    out=[]
    rows=len(a)
    cols=len(a[0])

    rowsind=[None]+list(itertools.combinations(range(rows),2))
    colsind=[None]+list(itertools.combinations(range(cols),2))
    
    for ci in colsind:
        for cj in rowsind:
            
            b=[ [None for _ in range(cols)] for __ in range(rows)]
            if (cj is None)&(ci is not None):
                x1,x2=ci
                for e,f in zip(b,a):
                    e[x2]=f[x1]
                    e[x1]=f[x2]
            elif (ci is None)&(cj is not None):
                y1,y2=cj
                b[y2]=a[y1]
                b[y1]=a[y2]
            elif (ci is None)&(cj is None):
                b=copy.deepcopy(a)
            else:
                y1,y2=cj
                x1,x2=ci
                b[y1][x2]=a[y2][x1]
                b[y1][x1]=a[y2][x2]
                b[y2][x2]=a[y1][x1]
                b[y2][x1]=a[y1][x2]

            out.append(tuple([tuple(e) for e in b]))
    return out


            
solution(2, 2, 2)
