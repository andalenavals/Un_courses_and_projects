def simplify_map(smap):
    c=1
    for k in range(2):
        h,w=len(smap),len(smap[0])
        ind=[]
        line=[sum(g)==0 for g in smap ]
        for j in range(h-1):
            if line[j]&line[j+1]: ind.append(j)
        for j in range(h-3):
            cond=(smap[j]==smap[j+2])
            cond&=(smap[j+1]==smap[j+3])
            cond&=((sum(smap[j])==0)|(sum(smap[j+1])==0))
            if cond : ind+=[j,j+1]
        smap=[r for i,r in enumerate(smap) if i not in ind ] #delete lines
        c+=len(set(ind))
        smap= [[row[i] for row in smap] for i in range(w)] #get transpose
            
    h,w=len(smap),len(smap[0])
    coords=[]
    for i in range(1,w-1):
        for j in range(1,h-1):
            if [r[i-1:i+2] for r in smap[j-1:j+2]]==[[0]*3]*3: coords.append((i,j))
    for x,y in coords: smap[y][x] = 1
    return (c,smap)

def isclosed_path(path,smap,x0,y0):
    flag=False
    h,w=len(smap),len(smap[0])
    x,y=path[0]
    if (x==0)|(x==w-1): flag|=y0<y
    if (y==0)|(y==h-1): flag|=x0<x
    return flag

def where_can_move(path, smap, forb_pos, forb_posf):
    sol=[]; fire=[]
    h,w=len(smap),len(smap[0])
    x,y=path["path"][0]
    for X,Y,cond in [(x,y+1,y+1<=h-1), (x+1,y,x+1<=w-1),  (x-1,y,x-1>=0), (x,y-1,y-1>=0)]:
        if not cond: continue
        if (X,Y) in forb_pos: continue
        if (path["fire"])&((X,Y) in forb_posf): continue
        if isclosed_path(path["path"], smap,X,Y): continue
        if smap[Y][X]==0:
            if (X,Y) not in path["path"]:
                sol.append((X,Y)); fire.append(path["fire"])
        else:
            if not path["fire"]:
                sol.append((X,Y)); fire.append(True)
    return [{"path":[s]+path["path"], "fire":f }  for s,f in zip(sol,fire)]

def select_paths(paths):
    twopos=[tuple(p["path"][:2]) for p in paths]
    repeated_twopos=[t for t in set(twopos) if twopos.count(t)>1]
    del_ind=[]
    for pos in repeated_twopos:
        indx=[]; fires=[]
        for i,p in enumerate(paths):
            if tuple(p["path"][:2])==pos:
                indx.append(i)
                fires.append(p["fire"])
        if (all(fires))|( not any(fires)):
            del_ind+=indx[1:]
        else:
            for i, fire in enumerate(fires):
                if not fire:
                    indx.pop(i)
                    del_ind+=indx
                    break
    return [r for i,r in enumerate(paths) if i not in del_ind ]

def solution(smap):
    i, smap=simplify_map(smap)
    h,w=len(smap),len(smap[0])
    allpaths=[{"path":[(0,0)],"fire":False }]
    forb_pos=[(0,0)]
    forb_posf=[] #forbiden position for path on fire
    while (w-1, h-1) not in [s["path"][0] for s in allpaths]:
        nps=len(allpaths)
        allpaths=[il for ol in map(where_can_move, allpaths, [smap]*nps, [forb_pos]*nps, [forb_posf]*nps)  for il in ol]
        forb_pos+=list(set([p["path"][0] for p in allpaths if not p["fire"]]))
        forb_posf+=list(set([p["path"][0] for p in allpaths if p["fire"]]))
        allpaths=select_paths(allpaths)
        i+=1
    return i
