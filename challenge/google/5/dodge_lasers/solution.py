import decimal
def solution(s):
    return sum_to_n(s).to_eng_string()[:-2]
      
def sum_to_n(n):
    decimal.getcontext().prec=250
    a=decimal.Decimal( (decimal.Decimal(n)*decimal.Decimal(2).sqrt()).to_eng_string().split(".")[0]) 
    np=a-decimal.Decimal(n)
    if int(a)>0: return decimal.Decimal(0.5)*a*(a+1)- np*(np+1) - sum_to_n(np)
    else: return decimal.Decimal(0)

print(solution('9'*90))
    
'''
print(solution('9'))
print(solution('99'))
print(solution('999'))
print(solution('9'*7))
print(solution('20'))
print(solution('77'))
print(solution('100'))
print(solution('1000'))
print(solution('25976'))

#print(solution('9'*9))
print(solution('9'*90))
'''


#solution('20')    
#solution('100')     
#solution('1000')
#solution('3500')
#solution('25976')
#solution('1%s'%('0'*8))
#solution('1%s'%('0'*100))


    
    
        
        
    

