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
	xi=xo+dt*dxdt(vo)
	vi=v+(dt/2)*(dvdt(x)+dvdt(xi))
	x=x+(dt/2)*(dxdt(vo)+dxdt(vi))
	v=v+(dt/2)*(dvdt(xo)+dvdt(xi))
	t=t+dt		
	
plot(tl,xl,label="pos")
plot(tl,vl,label="vel")
legend()
show()


