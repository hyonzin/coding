// https://programmers.co.kr/learn/courses/30/lessons/12938

def solution(n, s):
    return [-1] if n > s else [
        int(s/n) if n-i > s%n else int(s/n) + 1
        for i in range(n)]
