# https://school.programmers.co.kr/learn/courses/30/lessons/42897

import sys
# 재귀함수가 최대 100만 개(=집 최대개수) 불릴 수 있음
sys.setrecursionlimit(1000000)

def solution(money):
    # 첫번째를 터는 경우(마지막 집을 없는 셈 침), 안 터는 경우 중 큰 값 반환
    return max(money[0] + recur(money[2:-1]), recur(money[1:]))

def recur(money, depth=0, mem=None):
    if mem is None:
        mem = {}
    if depth >= len(money):
        return 0
    # 마지막 집이면 무조건 턴다(직전 집은 안 털렸다고 가정할 수 있음)
    if depth == len(money) - 1:
        return money[depth]
    # 이후의 집에 대해 이미 계산한 적 있으면, mem에서 꺼내서 리턴
    if depth in mem:
        return mem[depth]
    # 이 집을 터는 경우, 안 터는 경우 중 큰 값 반환
    n = max(money[depth] + recur(money, depth+2, mem),
            recur(money, depth+1, mem))
    # mem에 결과 기억하기
    mem[depth] = n
    return n
