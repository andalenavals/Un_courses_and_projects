from math import sin,cos,tan,asin,acos,atan,sqrt,log,exp
from math import sinh,cosh,tanh,asinh,acosh,atanh
 
ec=raw_input('De la funcion a resolver: ')
x1=float(input('de el extremo inferior del intervalo aproximado: '))
x2=float(input('de el extremo superior del intervalo aproximado: '))
errordeseado=input('De el error deseado: ')
 
def f(x):
    return eval(ec)
 
while True:
    xmed=(x1+x2)/2
    if f(xmed)==0.0:
        break
    if (f(x1)*f(xmed))<0:
        x2=xmed
    else:
        x1=xmed
    error=abs(x2-x1)
    if error<errordeseado:
        break
print 'La raiz es',xmed
