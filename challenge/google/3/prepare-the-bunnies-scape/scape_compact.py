import numpy as np

def show_sol(w,h, path):
    smap=np.zeros((h,w), dtype=int)
    for x,y in path["path"]:
        smap[y,x]=1
    print(smap)
 
def simplify_map(smap):
    smap=np.array(smap)
    c=1
    # delete consecutive empty rows and cols
    h,w=smap.shape
    for k in range(2):
        ind=[]
        rows=(np.sum(smap,axis=[1,0][k])==0)
        for j in range([h,w][k]-1):
            if rows[j]&rows[j+1]: ind.append(j)
        smap=np.delete(smap,ind,k)
        c+=len(ind)

    # delete consecutive 2rows (2cols) being one empty'
    h,w=smap.shape
    for k in range(2):
        ind=[]
        for j in range([h,w][k]-3):
            cond=(list(smap[[(j,slice(None)),(slice(None),j)][k]])==list(smap[[(j+2,slice(None)),(slice(None),j+2)][k]]))
            cond&=(list(smap[[(j+1,slice(None)),(slice(None),j+1)][k]])==list(smap[[(j+3,slice(None)),(slice(None),j+3)][k]]))
            cond&=(sum(smap[[(j,slice(None)),(slice(None),j)][k]])==0)|(sum(smap[[(j+1,slice(None)),(slice(None),j+1)][k]])==0)
            if cond : ind+=[j,j+1]
        smap=np.delete(smap,ind,k)
        c+=len(set(ind))

    # filling empty blocks >= 3x3
    h,w=smap.shape
    coords=[]
    for i in range(1,w-1):
        for j in range(1,h-1):
             if np.all(smap[j-1:j+2,i-1:i+2]==0): coords.append((i,j))
    for x,y in coords: smap[y,x]=1

    return c,smap

def isclosed_path(path,smap,x0,y0):
    flag=False
    h,w=smap.shape
    flag|=any([ abs(p[0]-x0)+abs(p[1]-y0)==1 for p in path[2:]])
    x,y=path[0]
    if (x==0)|(x==w-1):
        flag|=y0<y
    if (y==0)|(y==h-1):
        flag|=x0<x
    return flag

def where_can_move(path, smap):
    sol=[]; fire=[]
    h,w=smap.shape
    x,y=path["path"][0]
    
    for X,Y,cond in [(x,y+1,y+1<=h-1),  (x,y-1,y-1>=0), (x+1,y,x+1<=w-1), (x-1,y,x-1>=0) ]: #down, up, right, left
    #for X,Y,cond in [(x,y+1,y+1<=h-1),  (x,y-1,y-1>=0), (x-1,y,x-1>=0), (x+1,y,x+1<=w-1)]: #down, up, left, right
    #for X,Y,cond in [(x,y+1,y+1<=h-1), (x+1,y,x+1<=w-1), (x,y-1,y-1>=0),  (x-1,y,x-1>=0) ]: #down, right, up, left #206
    #for X,Y,cond in [(x,y+1,y+1<=h-1), (x+1,y,x+1<=w-1),  (x-1,y,x-1>=0), (x,y-1,y-1>=0)]: #down, right, left, up #202
        if cond:
            if isclosed_path(path["path"], smap,X,Y): continue
            if "forb_pos" in path.keys():
                #print(path)
                if (x,y) in path["forb_pos"]:
                    #assert False
                    continue
            if smap[Y,X]==0:
                if (X,Y) not in path["path"]:
                    sol.append((X,Y)); fire.append(path["fire"])
            else:
                if not path["fire"]:
                    sol.append((X,Y)); fire.append(True)
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
            aux=list(indx[1:,0])
            del_ind+=aux
            paths[indx[0,0]].update({"forb_pos":[paths[k]["path"][1] for k in aux]} )
        else:
            for i, (_,fire) in enumerate(indx):
                if not fire:
                    aux=list(indx[:,0])
                    aux.pop(i)
                    del_ind+=aux
                    paths[i].update({"forb_pos":[paths[k]["path"][1] for k in aux]} )
    return list(np.delete(paths,del_ind))

def solution(smap):
    print(np.array(smap))
    i, smap=simplify_map(smap)
    w=len(smap[0])
    h=len(smap)
    allpaths=[{"path":[(0,0)],"fire":False }]
    while (w-1, h-1) not in [s["path"][0] for s in allpaths]:
        allpaths=[ilist for olist in map(where_can_move, allpaths, [smap]*len(allpaths))  for ilist in olist]
        #print("\n", allpaths)
        allpaths=select_paths(allpaths)                  
        #print(allpaths)
        i+=1
    rsol=[ p for p in allpaths if (w-1, h-1) == p["path"][0] ]
    print("steps:", i, "sols:", len(rsol), "paths:", len(allpaths))
    
    show_sol(w,h, rsol[0])
    #for i in range(len(allpaths)):
    #    show_sol(w,h, allpaths[i])
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

A=[[0,1]+[0]*3, [0]*3+[1,0], [1]*4+[0], [1]*5,[0]*5]
solution(A)

