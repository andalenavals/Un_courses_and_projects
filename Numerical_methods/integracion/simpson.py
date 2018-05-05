# -*- coding: utf-8 -*-
"""
Calculo de integrales utilizando el método de simpson
"""
from numpy import linspace,sin,cos,pi

def simpson(f,a,b,n=21):
    """
    Función que calcula la integral de f utilizando el método de simpson
    
    Argumentos
    
    f   Funcion a integrar
    a   Limite inferior de la integral
    b   Limite superior de la integral
    n   Numero de puntos a usar en el calculo
    """
    
    if n%2 !=1: raise ValueError("El numero de puntos debe ser impar")
    
    X,step=linspace(a,b,n,retstep=True)
    Xi=X[1:-1:2]
    Xp=X[2:-2:2]
    return (step/3.)*(f(a)+f(b)+4.*f(Xi).sum()+2.*f(Xp).sum())
    

if __name__ == "__main__":
    print "Ejemplo de calculo de integrales usando el el método de Simpson"
    print "El valor de la integral entre 0  y pi/2 de la función coseno es: ",simpson(cos,0,pi/2)
    print "El valor de la integral entre 0  y pi/2 de la función sin es: ",simpson(sin,0,pi/2)
    print "El valor de la integral entre 0  y pi de la función coseno es: ",simpson(cos,0,pi)
    print "El valor de la integral entre 0  y pi de la función sin es: ",simpson(sin,0,pi)
