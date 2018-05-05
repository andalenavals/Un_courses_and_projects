#Return the roots of the (non-linear) equations defined by func(x) = 0 given a starting estimate
from scipy.optimize import fsolve
from numpy import *
def func(x):
	return x+2*cos(x)
print fsolve(func,.5)
print fsolve(sin,3)
