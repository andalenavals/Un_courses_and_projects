from pylab import *
from numpy import *

k=.1
m=1
dt=0.1

def dvdt(x):
	return -k*x/m
	
def dxdt(v):
	return v

x=.1
v=0
t=0
xl=[]
vl=[]
tl=[]
for i in range(1000):
	xl.append(x)
	vl.append(v)
	tl.append(t)
	vo=v
	xo=x
	k1=dt*dxdt(vo)
	j1=dt*dvdt(xo)
	x1=x+(dt/2)*(dxdt(vo)+dxdt(k1))
	v1=v+(dt/2)*(dvdt(xo)+dvdt(j1))
	k2=dt*dxdt(vo+(j1/2)
	j2=dt*dvdt(xo+(k1/2)
	x2=x+(dt/2)*(dxdt(vo)+dxdt(k2))
	v2=v+(dt/2)*(dvdt(xo)+dvdt(j2))
	t=t+dt		
	
plot(tl,xl,label="pos")
plot(tl,vl,label="vel")
legend()
show()


