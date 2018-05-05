'''
Integrate a system of ordinary differential equations.
Solve a system of ordinary differential equations using lsoda from the FORTRAN library odepack.
Solves the initial value problem for stiff or non-stiff systems of first order ode-s:
dy/dt = func(y, t0, ...)
where y can be a vector.
'''

from scipy.integrate import odeint
from pylab import *

def dydt(y, t):
	return -y*t
t = linspace(0, 1, 10)
y0 = 1
y = odeint(dydt, y0, t)
#exact solution
y1=exp(-t**2/2)
plot(t, y)
#plot(t, y1)
show()
