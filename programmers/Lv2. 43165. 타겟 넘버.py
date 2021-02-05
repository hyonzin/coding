# https://programmers.co.kr/learn/courses/30/lessons/43165

def check(numbers, target, Sum, idx):
    if idx == len(numbers):
        if target == Sum:
            return 1
        return 0
    return check(numbers, target, Sum+numbers[idx], idx+1) + \
           check(numbers, target, Sum-numbers[idx], idx+1)

def solution(numbers, target):
    answer = check(numbers, target, 0, 0)
    return answer
