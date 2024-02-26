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

    al=set(); l=0
    for i,f in enumerate(fund):
        al=al.union(set(get_combinations(f)))
        print(len(al))
        if len(al)==l:
            print(i, f)
            raise ValueError
        l=len(al)
    assert len(al)==3**4
    '''
    
    
    a0=[[0,0],[0,0]]
    a1=[[2,2],[2,2]]
    a2=[[3,3],[3,3]]
    a3=[[2,3],[2,2]]
    a4=[[3,2],[3,3]]
    a5=[[2,2],[3,3]]
    a6=[[2,3],[2,3]]
    a7=[[2,3],[3,2]]
    a8=[[2,1],[1,1]]
    a9=[[3,1],[1,1]]
    a10=[[2,2],[1,1]]
    a11=[[3,3],[1,1]]
    a12=[[2,3],[1,1]]
    a13=[[1,2],[1,2]]
    a14=[[1,3],[1,3]]
    a15=[[1,2],[1,3]]
    a16=[[1,2],[2,1]]
    a17=[[1,3],[3,1]]
    a18=[[1,3],[2,1]]
    a19=[[1,2],[2,2]]
    a20=[[1,2],[3,2]]
    a21=[[1,2],[3,3]]
    a22=[[1,2],[2,3]]
    a23=[[1,3],[3,3]]
    a24=[[1,3],[2,2]]
    a25=[[1,3],[2,3]]
    a26=[[1,3],[3,2]]
    a27=[[1,1],[1,1]]
    
    a28=[[1,0],[0,0]]
    a29=[[2,0],[0,0]]
    a30=[[3,0],[0,0]]

    a31=[[1,1],[0,0]]
    a32=[[1,2],[0,0]]
    a33=[[1,3],[0,0]]
    a34=[[2,2],[0,0]]
    a35=[[2,3],[0,0]]
    a36=[[3,3],[0,0]]
    
    a37=[[0,1],[0,1]]
    a38=[[0,1],[0,2]]
    a39=[[0,1],[0,3]]
    a40=[[0,2],[0,2]]
    a41=[[0,2],[0,3]]
    a42=[[0,3],[0,3]]

    a43=[[0,1],[1,0]]
    a44=[[0,1],[2,0]]
    a45=[[0,1],[3,0]]
    a46=[[0,2],[2,0]]
    a47=[[0,2],[3,0]]
    a48=[[0,3],[3,0]]

    a49=[[0,1],[1,1]]
    a50=[[0,1],[1,2]]
    a51=[[0,1],[1,3]]
    a52=[[0,1],[2,1]]
    a53=[[0,1],[2,2]]
    a54=[[0,1],[2,3]]
    a55=[[0,1],[3,1]]
    a56=[[0,1],[3,2]]
    a57=[[0,1],[3,3]]
    a58=[[0,2],[1,1]]
    a59=[[0,2],[1,2]]
    a60=[[0,2],[1,3]]
    a61=[[0,2],[2,1]]
    a62=[[0,2],[2,2]]
    a63=[[0,2],[2,3]]
    a64=[[0,2],[3,1]]
    a65=[[0,2],[3,2]]
    a66=[[0,2],[3,3]]
    a67=[[0,3],[1,1]]
    a68=[[0,3],[1,2]]
    a69=[[0,3],[1,3]]
    a70=[[0,3],[2,1]]
    a71=[[0,3],[2,2]]
    a72=[[0,3],[2,3]]
    a73=[[0,3],[3,1]]
    a74=[[0,3],[3,2]]
    a75=[[0,3],[3,3]]
    

    fund=[a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,a71,a72,a73,a74,a75]

    al=set(); l=0
    for i,f in enumerate(fund):
        al=al.union(set(get_combinations(f)))
        print(len(al))
        if len(al)==l:
            print(i, f)
            raise ValueError
        l=len(al)
    assert len(al)==4**4
    
    

    
    
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
