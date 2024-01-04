lowercases="abcdefghijklmnopqrstuvwxyz"
def solution(x):
    return "".join(map(decrypt,x))
def decrypt(x):
    if x.islower():
        return lowercases[-1-lowercases.index(x)]
    else:
        return x
