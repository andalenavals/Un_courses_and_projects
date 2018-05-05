from math import*
from numpy import*
f=input('imprima la funcion')
a=input('limite inferior')
b=input('limite superior')
n=input('numero de particiones impar')
r=(b-a)/n
#~ def Integral(a,r,n):
	#~ X=linspace(a,b,n)
	#~ i=linspace(0,(n/2)-1,(n/2)-1)
	#~ j=linspace(0,(n/2)-2,(n/2)-2)
	#~ Xi=X[(2*i)+1]
	#~ Xp=Xi+a
	#~ return (r/3)*(sin(a)+sin(b)+4*sin(Xp).sum()+2*sin(Xi).sum())
#~ print Integral(a,r,n)
#~ 

def simpson(f,a,b,n=21):  
    X=linspace(a,b,n)
    Xi=X[1:-1:2]
    Xp=X[2:-2:2]
    return (r/3.)*(f(a)+f(b)+4.*f(Xi).sum()+2.*f(Xp).sum())
print simpson(f,a,b,n)


#~ y=linspace(1,10,20)
#~ m=y[::3]
#~ print y
#~ print m
