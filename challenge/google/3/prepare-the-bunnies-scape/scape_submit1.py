import numpy as np

def tlist(l):
    return [inner_list for outer_list in l for inner_list in outer_list]

def isclosed_path(path,smap,x0,y0):
    flag=False
    w=len(smap[0])
    h=len(smap)
    flag|=any([ abs(p[0]-x0)+abs(p[1]-y0)==1 for p in path[2:]])
    x,y=path[0]
    if (x==0)|(x==w-1):
        flag|=y0<y
    if (y==0)|(y==h-1):
        flag|=x0<x
    return flag

def where_can_move(path, smap):
    sol=[]
    fire=[]
    w=len(smap[0])
    h=len(smap)
    x,y=path["path"][0]
    assert x<w
    assert y<h
    smap=np.array(smap)
    if y-1>=0:
        if not isclosed_path(path["path"], smap,x,y-1):
            if smap[y-1,x]==0:
                if (x,y-1) not in path["path"]:
                    sol.append((x,y-1)) #up
                    fire.append(path["fire"])
            else:
                if not path["fire"]:
                    sol.append((x,y-1))
                    fire.append(True)
    if y+1<=h-1:
        if not isclosed_path(path["path"], smap,x,y+1):
            if smap[y+1,x]==0:
                if (x,y+1) not in path["path"]:
                    sol.append((x,y+1)) #down
                    fire.append(path["fire"])
            else:
                if not path["fire"]:
                    sol.append((x,y+1))
                    fire.append(True)
    if x+1<=w-1:
        if not isclosed_path(path["path"], smap,x+1,y):
            if smap[y,x+1]==0:
                if (x+1,y) not in path["path"]:
                    sol.append((x+1,y)) #right
                    fire.append(path["fire"])
            else:
                if not path["fire"]:
                    sol.append((x+1,y))
                    fire.append(True)
    if x-1>=0:
        if not isclosed_path(path["path"], smap,x-1,y):
            if smap[y,x-1]==0:
                if (x-1,y) not in path["path"]:
                    sol.append((x-1,y)) #left
                    fire.append(path["fire"])
            else:
                if not path["fire"]:
                    sol.append((x-1,y))
                    fire.append(True)
    return [{"path":[s]+path["path"], "fire":f }  for s,f in zip(sol,fire)]

def simplify_map(smap):
    w=len(smap[0])
    h=len(smap)
    smap=np.array(smap)
    coords=[]
    for i in range(1,w-1):
        for j in range(1,h-1):
             if np.all(smap[j-1:j+2,i-1:i+2]==0): coords.append((i,j))
    for x,y in coords:
        smap[y,x]=1
    return smap

def solution(smap):
    smap=simplify_map(smap)
    w=len(smap[0])
    h=len(smap)
    allpaths=[{"path":[(0,0)],"fire":False }]
    i=1
    while (w-1, h-1) not in [s["path"][0] for s in allpaths]:
        allpaths=tlist(map(where_can_move, allpaths, [smap]*len(allpaths)))
        i+=1
    return i

A=[[0]*6,[1]*5+[0],[0]*6,[0]+[1]*5,[0]+[1]*5,[0]*6]
#A=[[0]*6,[1]*4+[0]*2,[0]*6,[0]+[1]*5,[0]+[1]*5,[0]*6]

#A=np.zeros((3,20))
#A=[[0]+[1]*19,[0]+[1]*19,[0]*20]
#A=[[0]*19+[1],[0]+[1]*19,[0]*20]
#A=[[0]*19+[1],[0,1]*10,[0]*20]
#A=[[0]*19+[1],[0]*2+[0,1]*9,[0]*20]
#A=[[0]*19+[1],[0]*6+[0,1]*7,[0]*20]


print(solution(A))


