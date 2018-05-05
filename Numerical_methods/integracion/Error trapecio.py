#~ from math import*
import numpy as np
from pylab import*
f=input('ingrese la funcion')
a=input('limite inferior')
b=input('limite superior')
#~ n=input()
def Integral(a,b,n):
	i=linspace(1,n-1,n-1)
	Xi=((b-a)/n)*i
	Xp=Xi+a
	return(((b-a)/n)/2)*(f(a)+f(b)+2.*f(Xp).sum())
#~ print Integral(a,b,n)

x=linspace(1,100,100)
for i in range (1,101):
	y=2-Integral(a,b,x[i])
xlabel('numero de particiones')
ylabel('error')
plot(x,y)
show()
