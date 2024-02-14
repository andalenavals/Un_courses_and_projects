import math
def solution(s):
    r=0
    for i in range(1, int(s)+1):
        #r+=math.floor(i*math.sqrt(2))
        r+=(i*math.sqrt(2))//1
    return str(int(r))

print(solution('9'))
print(solution('99'))
print(solution('999'))
print(solution('9'*7))

#print(solution('20'))
#print(solution('77'))
#print(solution('100'))
#print(solution('1000'))
#print(solution('25976'))

#print(solution('1%s'%('0'*8)))

