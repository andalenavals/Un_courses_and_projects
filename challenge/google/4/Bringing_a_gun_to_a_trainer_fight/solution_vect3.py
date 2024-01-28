import math
import numpy as np
def solution(dimensions, your_position, trainer_position, distance):
    w,h=dimensions
    x,y=your_position
    tx,ty=trainer_position
    R=distance

    #trivial solution
    if ((x==tx)|(y==ty))&(math.hypot(x-tx,y-ty)<=R): tsol=1
    else: tsol=0
    
    #right, left
    hor=[w-x,x]; thor=[w-tx,tx]
    ver=[h-y,y]; tver=[h-ty,ty]  

    x_list ,tx_list, join_xlist=make_a_line(hor,thor, R)
    y_list ,ty_list, join_ylist=make_a_line(ver,tver, R)

    target_directions=0
    for M,Mt,D, Dt in zip( get_slopes(x_list, y_list, R), get_slopes(tx_list, ty_list, R), get_distances(x_list, y_list, R), get_distances(tx_list, ty_list, R)):
        target_directions+=len(setter(Mt))
        ar=0
        for s in set(setter(M)).intersection(set(setter(Mt))):
            #print(min(D[np.where(np.isclose(M,s))]) -  min(Dt[np.where(np.isclose(Mt,s))]))
            #if min(D[np.where(np.isclose(M,s))]) < min(Dt[np.where(np.isclose(Mt,s))]):
            #if min(D[np.where(M==s)]) < min(Dt[np.where(Mt==s)]):
            if min(D[M==s]) < min(Dt[Mt==s]):
                target_directions-=1
                ar+=1
        print(ar, len(set(setter(M)).intersection(set(setter(Mt)))))

    print(target_directions+tsol)
    return target_directions+tsol
        
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

    j_list=sorted(set(tl_list + l_list + [ori,0] + tr_list + r_list))
           
    return l_list+[0]+r_list, tl_list+[ori]+tr_list, j_list
    #return l_list+r_list, tl_list+[ori]+tr_list, j_list
    #return l_list+r_list, tl_list+tr_list

def get_slopes(xlist, ylist, R):
    D=np.hypot.outer(ylist, xlist)
    total_uniq_directions=np.divide.outer(ylist, xlist)*(D<=R)
    w,h=total_uniq_directions.shape
    ox=w/2; oy=h/2
           
    tr=total_uniq_directions[ox:,oy:]  # top right
    br=total_uniq_directions[:ox,oy:]  # bottom right    
    tl=total_uniq_directions[ox:,:oy]  # top left
    bl=total_uniq_directions[:ox,:oy]  # bottom left
    return tr,br,bl,tl

def get_distances(xlist, ylist, R):
    D=np.hypot.outer(ylist, xlist)
    w,h=D.shape
    ox=w/2; oy=h/2
           
    dtr=D[ox:,oy:]  # top right
    dbr=D[:ox,oy:]  # bottom right    
    dtl=D[ox:,:oy]  # top left
    dbl=D[:ox,:oy]  # bottom left
    return dtr,dbr,dbl,dtl


def setter(l):
    fla=set(l.flatten())-{0}
    aux=[e for e in fla if (not math.isinf(e))&(not math.isnan(e)) ]
    return aux
    


#solution([6,2], [5,1], [4,1], 4)
#solution([2,6], [1,5], [1,4], 4)

#solution([5,2], [1,1], [2,1], 2)
#solution([6,2], [5,1], [4,1], 6)
#solution([5,3], [1,1], [2,3], 2)
#solution([3,2], [1,1], [2,1], 7)
#solution([3,2], [1,1], [2,1], 4)
#solution([3,2], [1,1], [2,1], 8)
#solution([300,275], [150,150], [185,100], 500)
solution([30,17], [15,15], [18,10], 10000) #d=1000
