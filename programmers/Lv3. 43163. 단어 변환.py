def solution(begin, target, words):
    if target not in words:
        return 0
    if dif(begin, target) == 1:
        return 1
    Bdist = [None] * len(words)
    Tdist = [None] * len(words)
    
    for i in range(len(words)):
        if dif(words[i], begin) == 1:
            Bdist[i] = 1
    
    for i in range(len(words)):
        if dif(words[i], target) == 1:
            Tdist[i] = 1
    
    for n in range(2, len(words)):
        for i in range(len(Tdist)):
            if Tdist[i] == n-1:
                for j in range(len(Tdist)):
                    if Tdist[j] == None:
                        if dif(words[i], words[j]) == 1:
                            Tdist[j] = n
                            if Bdist[j] == 1:
                                return n + 1
    return 0

def dif(word1, word2):
    nDif = 0
    for i in range(len(word1)):
        if ord(word1[i]) != ord(word2[i]):
            nDif += 1
            if nDif > 1:
                break
    return nDif
