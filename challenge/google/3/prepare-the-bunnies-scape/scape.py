import math
import numpy as np

def show_sol(w,h, path):
    smap=np.zeros((h,w), dtype=int)
    for x,y in path["path"]:
        smap[y,x]=1
    print(smap)

def simplify_map(smap):
    smap=np.array(smap)
    c=1

    #delete consecutive identical rows
    #WRONG it is not general  solution can cross multiple times the repeted rows
    '''
    rowind=[]
    for j in range(h-1):
        if list(smap[j,:])==list(smap[j+1,:]): rowind.append(j)
    smap=np.delete(smap,rowind,0)
    '''
    
    # delete consecutive empty rows
    h,w=smap.shape
    rowind=[]
    rows=(np.sum(smap,axis=1)==0)
    for j in range(h-1):
        if rows[j]&rows[j+1]: rowind.append(j)
    smap=np.delete(smap,rowind,0)
    # delete consecutive empty columns
    colind=[]
    cols=(np.sum(smap,axis=0)==0)
    for i in range(w-1):
        if cols[i]&cols[i+1]: colind.append(i)
    smap=np.delete(smap,colind,1)
    c+=len(rowind)+len(colind)

    # delete consecutive 2rows with one empty
    h,w=smap.shape
    rowind=[]
    for j in range(h-3):
        cond=(list(smap[j,:])==list(smap[j+2,:]))
        cond&=(list(smap[j+1,:])==list(smap[j+3,:]))
        cond&=((sum(smap[j,:])==0)|(sum(smap[j+1,:])==0))
        if cond : rowind+=[j,j+1]
    smap=np.delete(smap,rowind,0)
    c+=len(set(rowind))

    # delete consecutive 2cols with one empty
    colind=[]
    for j in range(w-4):
        cond=(list(smap[:,j])==list(smap[:,j+2]))
        cond&=(list(smap[:,j+1])==list(smap[:,j+3]))
        cond&=((sum(smap[:,j])==0)|(sum(smap[:,j+1])==0))
        if cond : colind+=[j,j+1]
    smap=np.delete(smap,colind,1)
    c+=len(set(colind))

    # filling empty blocks >= 3x3
    h,w=smap.shape
    coords=[]
    for i in range(1,w-1):
        for j in range(1,h-1):
             if np.all(smap[j-1:j+2,i-1:i+2]==0): coords.append((i,j))
    for x,y in coords:
        smap[y,x]=1

    return c,smap
            
def tlist(l):
    return [inner_list for outer_list in l for inner_list in outer_list]

def isclosed_path(path,smap,x0,y0):
    flag=False
    w=len(smap[0])
    h=len(smap)
    #*** selfclosed ***
    # check if current position is neigbor of any previous position not cosiderig last two steps
    flag|=any([ abs(p[0]-x0)+abs(p[1]-y0)==1 for p in path[2:]])
    #*** closed with borders ***
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

def select_paths(paths):
    ## if several path share current position keep only one preferible that
    ## have not used fire
    cpos=[p["path"][0] for p in paths]
    if len(set(cpos))==len(paths): return paths
    repeated_pos=[i for i in set(cpos) if cpos.count(i)>1]
    del_ind=[]
    for pos in repeated_pos:
        indx=np.array([[i,p["fire"]] for i,p in enumerate(paths) if p["path"][0]==pos])
        if (np.all(indx==0,axis=0)[1])|(np.all(indx==1,axis=0)[1]):
            del_ind+=list(indx[1:,0])
        else:
            for i, (_,fire) in enumerate(indx):
                if not fire:
                    aux=list(indx[:,0])
                    aux.pop(i)
                    del_ind+=aux
    return list(np.delete(paths,del_ind))

def solution(smap):
    print(np.array(smap))
    i, smap=simplify_map(smap)
    w=len(smap[0])
    h=len(smap)
    allpaths=[{"path":[(0,0)],"fire":False }]
    while (w-1, h-1) not in [s["path"][0] for s in allpaths]:
        allpaths=tlist(map(where_can_move, allpaths, [smap]*len(allpaths)))
        allpaths=select_paths(allpaths)
        i+=1
    rsol=[ p for p in allpaths if (w-1, h-1) == p["path"][0] ]
    print("steps:", i, "sols:", len(rsol), "paths:", len(allpaths))
    
    show_sol(w,h, rsol[0])
    print("\n")


A=[[0]*6,[1]*5+[0],[0]*6,[0]+[1]*5,[0]+[1]*5,[0]*6]
solution(A)

A=[[0]*6,[1]*4+[0]*2,[0]*6,[0]+[1]*5,[0]+[1]*5,[0]*6]
solution(A)

A=[[0,1,1,0],[0,0,0,1],[1,1,0,0],[1,1,1,0]]
solution(A)

A=[[0]*20,[1,0]*(20//4)+[0]*10]*1+[[0]*20]*2
solution(A)

s=20
A=[[0]*s,[1,0]*(s//2)]*1+[[0]*s]*2
solution(A)

A=[[0]*20,[1,0]*(20//4)+[0]*10]*1+[[0]*20]*2
solution(A)

A=[[0]*20]+[[0,1]*10,[0]*20]*10
solution(A)

A=np.zeros((20,19))
solution(A)

A=[[0]+[1]*19,[0]+[1]*19,[0]*20]
solution(A)

A=[[0]*19+[1],[0]+[1]*19,[0]*20]
solution(A)

A=[[0]*19+[1],[0,1]*10,[0]*20]
solution(A)

A=[[0]*19+[1],[0]*2+[0,1]*9,[0]*20]
solution(A)

A=[[0]*19+[1],[0]*6+[0,1]*7,[0]*20]
solution(A)

A=[[0]*24]+[[0,1]*12,[0,0,1]*8]*10
solution(A)

A=[[0]*22, [0,1]*11, [0]*22, [1,0]*11]*5
solution(A)

L=30
A=[[0]*(L-1)+[1],[0]*L,[1,0,0]*(L//3),[0]*(L-1)+[1],[0]*L, [0,1,0]*(L//3),[0]*(L-1)+[1],[0]*L, [0,0,1]*(L//3), [0]*L ]*2
solution(A)







#A=[list(range(6)),list(range(6,12)),list(range(12,18)),list(range(18,24))]
#print(np.array(A))
#print(simplify_map(A))





#paths=[{'path': [(0, 1), (0, 0)], 'fire': True}]
#print(tlist(map(where_can_move, paths,[A]*len(paths))))


    
