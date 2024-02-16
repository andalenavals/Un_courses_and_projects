import math
import numpy as np
def solution(dimensions, your_position, trainer_position, distance):
    w,h=dimensions
    x,y=your_position
    tx,ty=trainer_position
    R=distance

    #trivial solution
    if ((x==tx)|(y==ty))&(math.hypot(x-tx,y-ty)<=R):
        trivial_sol=1
        #trivial_direct={}
    else: trivial_sol=0
    
    #right, left
    hor=[w-x,x]; thor=[w-tx,tx]
    ver=[h-y,y]; tver=[h-ty,ty]  

    x_list ,tx_list=make_a_line(hor,thor, R)
    y_list ,ty_list=make_a_line(ver,tver, R)

    target_directions=0
    for [M,D],[Mt,Dt] in zip( get_slopes(x_list, y_list, R), get_slopes(tx_list, ty_list, R)):
        target_directions+=len(setter(Mt))
        for s in set(setter(M)).intersection(set(setter(Mt))):
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

    return l_list+r_list, tl_list+[ori]+tr_list


def get_slopes(xlist, ylist, R):
    D=np.hypot.outer(ylist, xlist)
    total_uniq_directions=np.divide.outer(ylist, xlist)*(D<=R)
    w,h=total_uniq_directions.shape
    ox=w/2; oy=h/2
    if xlist[oy]<0:oy+=1
    
    r=total_uniq_directions[:,oy:]  #right  
    l=total_uniq_directions[:,:oy]  # left

    dr=D[:,oy:]  # right  
    dl=D[:,:oy]  # left
    return [[r,dr], [l,dl]]

def aget_slopes(xlist, ylist, R):
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

def setter(l):
    fla=set(l.flatten())-{0}
    aux=[e for e in fla if (not math.isinf(e))&(not math.isnan(e)) ]
    return set(aux)

#print(solution([3,3], [1,1], [2,2], 10000) )
print(solution([2,5], [1,2], [1,4], 11) )
#solution([6,2], [5,1], [4,1], 4)
#solution([2,6], [1,5], [1,4], 4)

#solution([5,2], [1,1], [2,1], 2)
print(solution([6,2], [5,1], [4,1], 6))
#solution([5,3], [1,1], [2,3], 2)
print(solution([3,2], [1,1], [2,1], 7))
print(solution([3,2], [1,1], [2,1], 4))
#solution([3,2], [1,1], [2,1], 8)
#solution([300,275], [150,150], [185,100], 500)
print(solution([30,17], [15,15], [18,10], 10000)) #d=1000

print(solution([30,16], [14,14], [18,10], 1000)) #d=1000
print(solution([15,8], [7,7], [9,5], 100)) #d=1000
print(solution([15,8], [6,6], [9,5], 70)) #d=1000
print(solution([11,8], [6,6], [6,5], 60)) #d=1000

print(solution([14,8], [6,6], [6,4], 150)) #d=1000
print(solution([5,4], [3,3], [3,2], 22)) #d=1000
print(solution([7,5], [4,4], [3,2], 22)) #d=1000
