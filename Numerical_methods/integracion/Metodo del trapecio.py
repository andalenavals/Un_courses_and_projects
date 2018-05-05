from math import*
from numpy import*
f=input('ingrese la funcion')
a=input('limite inferior')
b=input('limite superior')
n=input('numero de particiones')
r=(b-a)/n
def Integral(a,r,n):
	i=linspace(1,n-1,n-1)
	Xi=r*i
	Xp=Xi+a
	return(r/2)*(f(a)+f(b)+2.*f(Xp).sum())
print Integral(a,r,n)
