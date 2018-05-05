from pylab import *

dt=0.1
k=1
m=1
def dxdt(v):
	return v
def dvdt(x):
	return -k*x/m
xl=[]
vl=[]
tl=[]
x=1.
v=0.
#~ t=0.
for i in range(1000):
	xl.append(x)
	vl.append(v)
	tl.append(t)
	x1=x+(dt/2)*(dxdt(v))
	v1=v+(dt/2)*(dvdt(x))
	v=v+(dt/2)*(dvdt(x)+dvdt(x1))
	x=x+(dt/2)*(dxdt(v)+dxdt(v1))
	t=t+dt

plot(tl,xl,label="pos")
plot(tl,vl,label="vel")
legend()
show()



