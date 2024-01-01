import math
import numpy as np

def show_sol(w,h, path):
    smap=np.zeros((h,w), dtype=int)
    for x,y in path:
        smap[y,x]=1
    print(smap)

def tlist(l):
    return [inner_list for outer_list in l for inner_list in outer_list]

    
def where_can_move(path, smap):
    sol=[]
    w=len(smap[0])
    h=len(smap)
    x,y=path[0]
    assert x<w
    assert y<h
    smap=np.array(smap)
    if y-1>=0:
        if smap[y-1,x]==0:
            if (x,y-1) not in path: sol.append((x,y-1)) #up
    if y+1<=h-1:
        if smap[y+1,x]==0:
            if (x,y+1) not in path: sol.append((x,y+1)) #down
    if x+1<=w-1:
        if smap[y,x+1]==0:
            if (x+1,y) not in path: sol.append((x+1,y)) #right
    if x-1>=0:
        if smap[y,x-1]==0:
            if (x-1,y) not in path: sol.append((x-1,y)) #left
    return [[s]+path  for s in sol]

def solution(smap):
    w=len(smap[0])
    h=len(smap)
    allpaths=[[(0,0)]]
    i=0
    while (w-1, h-1) not in [s[0] for s in allpaths]:
        allpaths=tlist(map(where_can_move, allpaths, [smap]*len(allpaths)))
        i+=1
    print("steps", i+1)
    #print("\n", allpaths)
    rsol=[ p for p in allpaths if (w-1, h-1) in p]
    show_sol(w,h, rsol[0] )

#A=[[0]*6,[1]*5+[0],[0]*6,[0]+[1]*5,[0]+[1]*5,[0]*6]
#A=[[0]*6,[1]*4+[0]*2,[0]*6,[0]+[1]*5,[0]+[1]*5,[0]*6]

A=np.zeros((3,20))
#A=[[0]+[1]*19,[0]+[1]*19,[0]*20]
#A=[[0]*19+[1],[0]+[1]*19,[0]*20]
#A=[[0]*19+[1],[0,1]*10,[0]*20]
#A=[[0]*19+[1],[0]*2+[0,1]*9,[0]*20]
#A=[[0]*19+[1],[0]*6+[0,1]*7,[0]*20]


print(np.array(A))
solution(A)

#paths=[[(1,0),(0,0)], [(0,0),(1,0),(0,1)]]
#paths=[[(0,0)]]
#paths=[[(0, 1), (0, 0)], [(1, 0), (0, 0)]]

#print(tlist(map(where_can_move, paths,[A]*len(paths))))
#print(tlist(list(map(where_can_move, paths,[A]*len(paths)))))

    
