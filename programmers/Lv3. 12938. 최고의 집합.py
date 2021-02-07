// https://programmers.co.kr/learn/courses/30/lessons/12938

def solution(n, s):
    if n > s:
        return [-1]
    
    num = int(s/n)
    answer = [num for i in range(n)]
    
    for i in range(s - n*num):
        answer[-(1+i)] += 1
    
    return answer
