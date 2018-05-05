#~ x0cos(x1) = 4
#~ x0x1-x1 = 5

from scipy.optimize import fsolve
from numpy import *
def func2(x):
	out = [x[0]*cos(x[1]) - 4]
	out.append(x[1]*x[0] - x[1] - 5)
	return out
print fsolve(func2, [1, 1])
