from scipy.integrate import quad
from numpy import *
def func(x):
	return exp(-x)
r,e=quad(func,0,Inf)
print r,e
