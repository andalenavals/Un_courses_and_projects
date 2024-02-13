import math
def solution(s):
    r=0
    for i in range(1, int(s)+1):
        #r+=math.floor(i*math.sqrt(2))
        r+=(i*math.sqrt(2))//1
    return str(int(r))

print(solution('5'))
print(solution('77'))
print(solution('1%s'%('0'*8)))

