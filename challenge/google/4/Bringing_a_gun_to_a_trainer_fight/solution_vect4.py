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

    x_list ,tx_list=make_a_line(hor,thor, R)
    y_list ,ty_list=make_a_line(ver,tver, R)
    print("fast")
    
    target_directions=0
    for [M,D],[Mt,Dt] in zip( get_slopes(x_list, y_list, R), get_slopes(tx_list, ty_list, R)):
        print("q")
        mtdirs=np.unique(Mt)#[np.unique(Mt)!=0]
        mdirs=np.unique(M)#[np.unique(M)!=0]
        target_directions+=len(mtdirs)-1
        # print(mtdirs)
        for s in np.intersect1d(mtdirs,mdirs, assume_unique=True):
            if s==0: continue
            if min(D[M==s]) < min(Dt[Mt==s]):
                target_directions-=1
        print("s")
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

    return l_list+r_list, tl_list+[ori]+tr_list


def get_slopes(xlist, ylist, R):
    D=np.hypot.outer(ylist, xlist)
    total_uniq_directions=np.divide.outer(ylist, xlist)*(D<=R)
    w,h=total_uniq_directions.shape
    ox=w/2; oy=h/2

    r=total_uniq_directions[:,oy:]  #right  
    l=total_uniq_directions[:,:oy]  # left

    dr=D[:,oy:]  # right  
    dl=D[:,:oy]  # left
    return [[r,dr], [l,dl]]


#print(solution([3,3], [1,1], [2,2], 10000) )
#print(solution([2,5], [1,2], [1,4], 11) )
#solution([6,2], [5,1], [4,1], 4)
#solution([2,6], [1,5], [1,4], 4)

#solution([5,2], [1,1], [2,1], 2)
#solution([6,2], [5,1], [4,1], 6)
#solution([5,3], [1,1], [2,3], 2)
#print(solution([3,2], [1,1], [2,1], 7))
#print(solution([3,2], [1,1], [2,1], 4))
#solution([3,2], [1,1], [2,1], 8)
#solution([300,275], [150,150], [185,100], 500)
print(solution([30,17], [15,15], [18,10], 10000)) #d=1000
