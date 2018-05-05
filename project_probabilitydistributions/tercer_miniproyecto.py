# -*- coding: utf-8 -*-
from math import *
from pylab import *
from matplotlib.pylab import hist, show
from scipy.integrate import quad
from matplotlib.patches import Polygon
import numpy as np

def combinatoria(a,b):
	Comb=factorial(a)/(factorial(a-b)*factorial(b))
	return Comb

#~ Distribuciones Continuas

def binomial(x,n,p):
	q=1-p
	P=combinatoria(n,x)*(p**x)*(q**(n-x))
	return P

#~ def multinomial(k)
	#~ for i in range(1,k):
		#~ a
		#~ def eventos(k,

def hipergeometrica(x,N,n,k):
	P=(combinatoria(k,x)*combinatoria((N-k),(n-x)))/float(combinatoria(N,n))
	return P
	
#~ hipergeometricamultivariada


def binomialnegativa(x,k,p):
	q=1-p
	P=combinatoria((x-1),(k-1))*(p**k)*(q**(x-k))
	return P
	
def poisson(x,t):
	P=((e**-t)*(t**x))/factorial(x)
	return P


#~ Distribuciones Continuas

def Normal(x,u,s):
	P=(e**(-0.5*(((x-u)/float(s))**2)))/(float(sqrt(2*pi)*s))
	return P
def AreaNormal(x1,x2):
	def f(x):
		f=Normal(x,u,s)
		return f
	r=quad(f,x1,x2)
	a=r[0]
	return a

def Fgamma(q):
	if q>0:
		def f(x):
			f=(x**(q-1))*(e**(-x))
			return f
		r=quad(f,0,Inf)
		a=r[0]
		return a
	else:
		return('alfa debe se mayor que 0')
	
def gamma(x,q,B):
	f=((B**(-q))*(x**(q-1))*(e**(-x/B)))/float(Fgamma(q))
	return f
def Areagamma(x1,x2):
	def f(x):
		f=gamma(x,q,B)
        return f
	r=quad(f,x1,x2)
	a=r[0]
	return a

def exponencial(x,B):
	P=gamma(x,1,B)
	return P
	
def jicuadrada(x,v):
	P=gamma(x,v/float(2),2)
	return P
def Areajicuadrada(x1,x2):
	def f(x):
		f=jicuadrada(x,v)
		return f
	r=quad(f,x1,x2)
	a=r[0]
	return a
	
def weibull(x,q,B):
	P=(B/float(q))*((x/float(q))**(B-1))*(e**(-(x/float(q))**B))
	return P
def Areaweibull(x1,x2):
	def f(x):
		f=weibull(x,q,B)
		return f
	r=quad(f,x1,x2)
	a=r[0]
	return a



n=raw_input('Escriba "Dis" o "Cont" si la variable aleatoria es continua o discreta: ')

if n[0]=="D":
	m= raw_input("\nEscoja una de las siguientes variable aleatorias:\nXBin: número de éxitos en n experimentos independientes.\nXHiper: número de éxitos en una muestra aleatoria de tamaño n seleccionada de N resultados posibles,\n        de los cuales k son consideradas como éxito y N-k fracasos.\nXbin*: número de intentos en el cual ocurre el k-ésimo éxito.\nXPoiss: número de resultados que ocurren en un intervalo de tiempo dado o región específica.\n(Escriba solo el prefijo como aparece indicado)\n")
	if m[0]=="P":
		t=input('\ndigite el promedio de resultados por unidad de tiempo "t"')
		u=t
		s=sqrt(t)
		print'u=',u,'s=',s
		prob=[]
		x=[]
		for i in range(0,2*t):
			x.append(i)
			j=poisson(i,t)
			prob.append(j)
		plot(x,prob,'ko--')
		grid()	
		show()

	if m[0]=="B":
		n,p=input('\ndigite el numero de experimentos "n" y la probabilidad de exito "p"')
		u=n*p
		s=sqrt(n*p*(1-p))
		print'u=',u,'s=',s
		prob=[]
		x=[]
		for i in range(0,n+1):
			x.append(i)
			j=binomial(i,n,p)
			prob.append(j)
		plot(x,prob,'ko--')
		grid()	
		show()
			
		
	if m[0]=="b":
		k,p=input('\ndigite el numero del k-esimo exitos "k", la probabilidad de exito "p"')
		prob=[]
		x=[]
		for i in range(k,3000):
			if binomialnegativa(i,k,p)<(p**k):
				a=i
				break
		
		for i in range(k,i):
			x.append(i)
			j=binomialnegativa(i,k,p)
			prob.append(j)
		plot(x,prob,'ko--')
		grid()	
		show()
		
	if m[0]=="H":
		N,n,k=input('\ndigite el numero de resultados posibles "N", el tamaño de la muestra "n" y los considerados exito "k"')
		u=n*k/float(N)
		s=sqrt(((N-n)*n*k*(N-k))/float((N-1)*N*N))
		print'u=',u,'s=',s
		prob=[]
		x=[]
		for i in range(0,k+1):
			x.append(i)
			j=hipergeometrica(i,N,n,k)
			prob.append(j)
		plot(x,prob,'ko--')
		
		grid()	
		show()
		
if n[0]=="C":
	m= raw_input("\nEscoja la distribución para la variable aleatoria:\nX~Nor: parametros media y desviacion estandar.\nX~Gamma: parametros alfa y Beta.\nX~Exp: parametro Beta.\nX~Ji: parametro grados de libertad.\nX~Wei: parametros alfa y Beta.\n")
	if m[0]=="N":
		saludo=("\nFuncion de densidad de la Distribucion Normal")
		print saludo
		u,s=input('\ndigite la media "u" y la desviacion estandar"s": ')
		me=u
		mo=u	
		n=input('digite el numero de intervalos')
		AREA=0
		A=[]
		for i in range(1,n+1):
			xi=input('\ndigite el intervalo (a,b)')
			A.append(xi)
			AREA=AREA+AreaNormal(xi[0],xi[1])

		for	i in range(1,n+1):
			x1=A[i-1][0]
			x2=A[i-1][1]
			if x1==-Inf:
				x1==-1*((4*s)+u)
			if x2==Inf:
				x2=((4*s)+u)
				
			ax = subplot(111)
			a,b = x1,x2
			x=linspace(-((4*s)+u),((4*s)+u),100)
			y=Normal(x,u,s)
			plot(x,y,linewidth=1,)	
		
			y=linspace(u,u,100)
			x=linspace(0,Normal(u,u,s),100)
			plot(y,x,'k--', linewidth=1)

			y=linspace(me,me,100)
			x=linspace(0,Normal(me,u,s),100)
			plot(y,x,'y--', linewidth=1)
		

			y=linspace(mo,mo,100)
			x=linspace(0,Normal(mo,u,s),100)
			plot(y,x,'g--', linewidth=1)
				
			ix = arange(a,b,0.01)
			iy = y=Normal(ix,u,s)
			verts = [(a,0)] + zip(ix,iy) + [(b,0)]
			poly = Polygon(verts, facecolor='0.8', edgecolor='k')
			ax.add_patch(poly)
			
			grid()
		legend(('F.densidad.P', ('Media='"{:7.5f}".format(u)),('Mediana='"{:7.5f}".format(me)),('Moda='"{:7.5f}".format(mo)),('Area='"{:7.5f}".format(AREA))))
		title('Funcion de densidad de probabilidad de la Normal')
		show()
		

	if m[0]=="G":
		saludo=("\nFuncion de densidad de la Distribucion Gamma")
		print saludo
		q,B=input('\ndigite alfa"q" y Beta"B": ')
		u=q*B
		s=sqrt(q*(B**2))
		me=q*((log(2)/log(e))**(1/float(B)))
		if B>1:
			mo=q*(((B-1)/float(B))**(1/float(B)))
			
		n=input('digite el numero de intervalos')
		AREA=0
		A=[]
		for i in range(1,n+1):
			xi=input('\ndigite el intervalo')
			A.append(xi)
			AREA=AREA+Areagamma(xi[0],xi[1])	
	
		for	i in range(1,n+1):
			x1=A[i-1][0]
			x2=A[i-1][1]
			if x1==-Inf:
				x1==-((4*s)+u)
			if x2==Inf:
				x2=((4*s)+u)
				
			ax = subplot(111)
			a,b = x1,x2
			x=linspace(0,((4*s)+u),100)
			y=gamma(x,q,B)
			plot(x,y,linewidth=1,)
		
		
			y=linspace(u,u,100)
			x=linspace(0,gamma(u,q,B),100)
			plot(y,x,'k--', linewidth=1)

			y=linspace(me,me,100)
			x=linspace(0,gamma(me,q,B),100)
			plot(y,x,'y--', linewidth=1)
		
			if B>1:
				y=linspace(mo,mo,100)
				x=linspace(0,gamma(mo,q,B),100)
				plot(y,x,'g--', linewidth=1)
				
				
			ix = arange(a,b,0.01)
			iy = y=gamma(ix,q,B)
			verts = [(a,0)] + zip(ix,iy) + [(b,0)]
			poly = Polygon(verts, facecolor='0.8', edgecolor='k')
			ax.add_patch(poly)
			
			if B<=1:
				mo='No esta definido'
			grid()
		legend(('F.densidad.P', ('Media='"{:7.5f}".format(u)),('Mediana='"{:7.5f}".format(me)),('Moda='"{:7.5f}".format(mo)),('Area='"{:7.5f}".format(AREA))))
		title('Funcion de densidad de probabilidad de la Gamma')
		show()
		
	if m[0]=="E":
		saludo=("\nFuncion de densidad de la Distribucion Exponencial")
		print saludo
		q=1
		B=input('\ndigite Beta"B": ')
		u=q*B
		s=sqrt(q*(B**2))
		me=((log(2)/log(e))*u)
		if B>1:
			mo=0
			
		n=input('digite el numero de intervalos')
		AREA=0
		A=[]
		for i in range(1,n+1):
			xi=input('\ndigite el intervalo')
			A.append(xi)
			AREA=AREA+Areagamma(xi[0],xi[1])
		
		for	i in range(1,n+1):
			x1=A[i-1][0]
			x2=A[i-1][1]
			if x1==-Inf:
				x1==-((4*s)+u)
			if x2==Inf:
				x2=((4*s)+u)
				
			ax = subplot(111)
			a,b = x1,x2
			x=linspace(0,((4*s)+u),100)
			y=gamma(x,q,B)
			plot(x,y,linewidth=1,)
		
		
			y=linspace(u,u,100)
			x=linspace(0,gamma(u,q,B),100)
			plot(y,x,'k--', linewidth=1)

			y=linspace(me,me,100)
			x=linspace(0,gamma(me,q,B),100)
			plot(y,x,'y--', linewidth=1)
		
			if B>1:
				y=linspace(mo,mo,100)
				x=linspace(0,gamma(mo,q,B),100)
				plot(y,x,'g--', linewidth=1)
				
				
			ix = arange(a,b,0.01)
			iy = y=gamma(ix,q,B)
			verts = [(a,0)] + zip(ix,iy) + [(b,0)]
			poly = Polygon(verts, facecolor='0.8', edgecolor='k')
			ax.add_patch(poly)
			
			if B<=1:
				mo='No esta definido'
			grid()
		legend(('F.densidad.P', ('Media='"{:7.5f}".format(u)),('Mediana='"{:7.5f}".format(me)),('Moda='"{:7.5f}".format(mo)),('Area='"{:7.5f}".format(AREA))))
		title('Funcion de densidad de probabilidad de la Exponencial')
		show()
		
	if m[0]=="J":
		saludo=("\nFuncion de densidad de probabilidad de Ji-cuadrada")
		print saludo
		v=input('\ndigite los grados de libertad v": ')
		u=v
		s=sqrt(2*v)
		me=v-(2/float(3))
		if v>=2:
			mo=v-2
			
		n=input('digite el numero de intervalos')
		AREA=0
		A=[]
		for i in range(1,n+1):
			xi=input('\ndigite el intervalo')
			A.append(xi)
			AREA=AREA+Areajicuadrada(xi[0],xi[1])
			
		for	i in range(1,n+1):
			x1=A[i-1][0]
			x2=A[i-1][1]
			if x1==-Inf:
				x1==-((4*s)+u)
			if x2==Inf:
				x2=((4*s)+u)
				
			ax = subplot(111)
			a,b = x1,x2
			x=linspace(0,((4*s)+u),100)
			y=jicuadrada(x,v)
			plot(x,y,linewidth=1,)
		
		
			y=linspace(u,u,100)
			x=linspace(0,jicuadrada(u,v),100)
			plot(y,x,'k--', linewidth=1)

			y=linspace(me,me,100)
			x=linspace(0,jicuadrada(me,v),100)
			plot(y,x,'y--', linewidth=1)
		
			if v>=2:
				y=linspace(mo,mo,100)
				x=linspace(0,jicuadrada(mo,v),100)
				plot(y,x,'g--', linewidth=1)
				
				
			ix = arange(a,b,0.01)     
			iy = y=jicuadrada(ix,v)
			verts = [(a,0)] + zip(ix,iy) + [(b,0)]
			poly = Polygon(verts, facecolor='0.8', edgecolor='k')
			ax.add_patch(poly)
			
			if v<2:
				mo='No esta definido'
			grid()
		legend(('F.densidad.P', ('Media='"{:7.5f}".format(u)),('Mediana='"{:7.5f}".format(me)),('Moda='"{:7.5f}".format(mo)),('Area='"{:7.5f}".format(AREA))))
		title('Funcion de densidad de probabilidad de la Ji-cuadrada')
		show()

	if m[0]=="W":
		saludo=("\nFuncion de densidad de la Distribucion Weibull")
		print saludo
		q,B=input('\ndigite alfa"q" y Beta"B": ')
		u=q*(Fgamma(1+(1/float(B))))
		s=sqrt((q**2)*((Fgamma(1+(2/float(B))))-(u**2)))
		me=q*((log(2)/log(e))**(1/float(B)))
		if B>1:
			mo=q*(((B-1)/float(B))**(1/float(B)))
			
		n=input('digite el numero de intervalos')
		AREA=0
		A=[]
		for i in range(1,n+1):
			xi=input('\ndigite el intervalo')
			A.append(xi)
			AREA=AREA+Areaweibull(xi[0],xi[1])
		
		print '\nla desviacion estandar es:',s,	

		for	i in range(1,n+1):
			x1=A[i-1][0]
			x2=A[i-1][1]
			if x1==-Inf:
				x1==-((4*s)+u)
			if x2==Inf:
				x2=((4*s)+u)
				
			ax = subplot(111)
			a,b = x1,x2
			x=linspace(0,((4*s)+u),100)
			y=weibull(x,q,B)
			plot(x,y,linewidth=1,)
		
		
			y=linspace(u,u,100)
			x=linspace(0,weibull(u,q,B),100)
			plot(y,x,'k--', linewidth=1)

			y=linspace(me,me,100)
			x=linspace(0,weibull(me,q,B),100)
			plot(y,x,'y--', linewidth=1)
		
			if B>1:
				y=linspace(mo,mo,100)
				x=linspace(0,weibull(mo,q,B),100)
				plot(y,x,'g--', linewidth=1)


			ix = arange(a,b,0.01)     
			iy = y=weibull(ix,q,B)
			verts = [(a,0)] + zip(ix,iy) + [(b,0)]
			poly = Polygon(verts, facecolor='0.8', edgecolor='k')
			ax.add_patch(poly)
		
			if B<=1:
				mo='No esta definido'
			grid()
		legend(('F.densidad.P', ('Media='"{:7.5f}".format(u)),('Mediana='"{:7.5f}".format(me)),('Moda='"{:7.5f}".format(mo)),('Area='"{:7.5f}".format(AREA))))
		title('Funcion de densidad de probabilidad de la Weibull')
		show()


