import numpy as np
def Paso_RK2(funcion,x,a,t,h):
	f1=funcion(x,a,t)
	f2=funcion(x+h*f1,a,t+h)
	r=x+0.5*h*(f1+f2)
	return r

def Paso_RK4(funcion,x,a,t,h):
	f1=funcion(x,a,t)
	f2=funcion(x+0.5*h*f1,a,t+0.5*h)
	f3=funcion(x+0.5*h*f2,a,t+0.5*h)
	f4=funcion(x+h*f3,a,t+h)
	r=x+(h/6.0)*(f1+2.0*f2+2.0*f3+f4)
	return r

def Paso_Euler(funcion,x,a,t,h):
	xp=funcion(x,a,t)
	x2=x+xp*h
	return x2
	
def Solver_explicito_paso_simple(integrador,funcion,x0,a,h,n,t0):
	resultado=[]
	x=[]
	t=t0
	for i in x0:
		resultado.append([i])
		x.append(0.0)
	for i in range(n):
		for j in range(len(x0)):
			x[j]=resultado[j][-1]
		r=integrador(funcion,x,a,t,h)
		for j in range(len(x0)):
			resultado[j].append(r[j])
		t=t+h
	return np.array(resultado)

def f1(x,a,t):
    r=x[0]*a[0]+a[0]
    return np.array([r])
     
r=Solver_explicito_paso_simple(Paso_Euler,f1,np.array([0.0]),np.array([6.0]),0.1,10,0.0)
     
r1=Solver_explicito_paso_simple(Paso_RK2,f1,np.array([0.0]),np.array([6.0]),0.1,10,0.0)
     
r2=Solver_explicito_paso_simple(Paso_RK4,f1,np.array([0.0]),np.array([6.0]),0.1,10,0.0)
 
import pylab
 
 
pylab.plot(r[0],'-+')
pylab.plot(r1[0],'-o')
pylab.plot(r2[0],'-*')
pylab.legend(('Euler','Runge-Kutta2','Runge-Kutta4'))
pylab.grid(True)
pylab.show()
