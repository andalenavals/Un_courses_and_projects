#recieve a str and change only not capital letters for the
# letter in the same position of the alphabet but in reverse order

lowercases="abcdefghijklmnopqrstuvwxyz"

def solution(x):
    assert isinstance(x,str)
    return "".join(map(decrypt,x))

def decrypt(x):
    assert isinstance(x,str)
    if x.islower():
        return transform(x)
    else:
        return x
    
def transform(x):
    return lowercases[-1-lowercases.index(x)]

#message="wrw blf hvv ozhg mrtsg'h vkrhlwv?"
message="Yvzs! I xzm'g yvorvev Lzmxv olhg srh qly zg gsv xlolmb!!"
print(solution(message))
