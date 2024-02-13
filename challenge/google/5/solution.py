import math
import decimal
import numpy as np

def solution(s):
    d2=np.array(decimal.Decimal(2).sqrt(decimal.Context(prec=100)).as_tuple().digits)
    group=np.array([d2*i for i in range(1,10)])

    
    r=0
    for i in range(1, int(s)+1):
        r+=math.floor(i*math.sqrt(2))
    return str(int(r))
