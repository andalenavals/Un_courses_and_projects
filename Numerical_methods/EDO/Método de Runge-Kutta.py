#!/usr/bin/python
# -*- coding: utf8 -*-
from pylab import *
#método Runge-Kutha
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
	
	
	k2=dt*dxdt(vo+(j1/2))
	j2=dt*dvdt(xo+(k1/2))
	
	k3=dt*dxdt(vo+(j2/2))
	j3=dt*dvdt(xo+(k2/2))
	
	k4=dt*dxdt(vo+j3)
	j4=dt*dvdt(xo+k3)
		
	x=xo+(k1/6 +k2/3 + k3/3 + k4/6)
	v=vo+(j1/6 +j2/3 + j3/3 + j4/6)
	t=t+dt

plot(tl,xl,label="posición")
plot(tl,vl,label="velocidad")
legend()
show()









 
