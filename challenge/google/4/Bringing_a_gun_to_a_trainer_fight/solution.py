import numpy as np
def solution(dimensions, your_position, trainer_position, distance):
    w,h=dimensions
    x,y=your_position
    tx,ty=trainer_position
    R=distance

    #trivial solution
    if ((x==tx)|(y==ty))&(np.hypot(x-tx,y-ty)<=R): trivial_sol=1
    else: trivial_sol=0
    
    #right, left
    hor=[w-x,x]; thor=[w-tx,tx]
    ver=[h-y,y]; tver=[h-ty,ty]  

    x_list ,tx_list=make_a_line(hor,thor, R)
    y_list ,ty_list=make_a_line(ver,tver, R)

    target_directions=0
    for [M,D],[Mt,Dt] in zip( get_slopes(x_list, y_list, R), get_slopes(tx_list, ty_list, R)):
        uniqt=set(Mt.flatten())-{0}
        target_directions+=len(uniqt)
        for s in uniqt.intersection(set(M.flatten())-{0}):
            if min(D[M==s]) < min(Dt[Mt==s]):
                target_directions-=1
        
    return target_directions+trivial_sol
        
def make_a_line(hor,thor, R):
    l_list=[]; tl_list=[]
    r_list=[]; tr_list=[]
    dl=0; dr=0; tdl=0; tdr=0; ori=thor[1]-hor[1]
    while (dl<=R)&(dr<=R):
        if (dl>R)&(dr>R): break
        dl+=float(2*hor[1])
        dr+=float(2*hor[0])
        r_list+=[dr]
        l_list+=[-dl]
        hor.reverse()        
        tdl+=float(2*thor[1])
        tdr+=float(2*thor[0])
        tr_list+=[ori +tdr]
        tl_list+=[ori -tdl]
        thor.reverse()
    l_list.reverse()
    tl_list.reverse()
    if ori==0:
        return l_list+r_list, tl_list+tr_list
    else:
        return l_list+r_list, tl_list+[ori]+tr_list
    
def get_slopes(xlist, ylist, R):
    D=np.hypot.outer(ylist, xlist)
    total_uniq_directions=np.divide.outer(ylist, xlist)*(D<=R)
    w,h=total_uniq_directions.shape
    ox=w/2; oy=h/2
    if ylist[ox]<0:ox+=1
    if xlist[oy]<0:oy+=1

    tr=total_uniq_directions[ox:,oy:]  # top right
    br=total_uniq_directions[:ox,oy:]  # bottom right    
    tl=total_uniq_directions[ox:,:oy]  # top left
    bl=total_uniq_directions[:ox,:oy]  # bottom left

    dtr=D[ox:,oy:]   
    dbr=D[:ox,oy:]
    dtl=D[ox:,:oy]
    dbl=D[:ox,:oy]   

    return [tr,dtr],[br,dbr],[bl,dbl],[tl,dtl]
