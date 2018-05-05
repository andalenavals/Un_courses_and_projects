from pylab import *
from numpy import *
g=10
L=1
dt=.1
def dot(w):
    return w
def dwt(o):
    return -(g/L)*sin(o)
for j in range (49):
    w=0
    o=j*pi/24
    t=0
    wl=[]
    ol=[]
    tl=[]
    for i in range (1000):
        wl.append(w)
        ol.append(o)
        tl.append(t)

        o1=dt*dot(w)
        w1=dt*dwt(o)

        o2=dt*dot(w+w1/2)
        w2=dt*dwt(o+o1/2)

        o3=dt*dot(w+w2/2)
        w3=dt*dwt(o+o2/2)    

        o4=dt*dot(w+w3)
        w4=dt*dwt(o+o3)

        t=t+dt

        o=o+o1/6+o2/3+o3/3+o4/6
        w=w+w1/6+w2/3+w3/3+w4/6
        print o,w,t
    print j
    subplot(6,8,j)
    plot (tl,ol,label='Angulo')
    plot (tl,wl,label='velocidad')
legend()
show()
