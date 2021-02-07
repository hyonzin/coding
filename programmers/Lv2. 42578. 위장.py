# https://programmers.co.kr/learn/courses/30/lessons/42578

def solution(clothes):
    dic = dict()
    
    # 각 옷 종류의 개수 세기
    for name, cloth_type in clothes:
        if cloth_type not in dic:
            dic[cloth_type] = 0
        dic[cloth_type] += 1
    
    # 각 옷 종류의 경우의 수 구하기
    answer = 1
    for cloth_type in dic:
        # 안 입는 경우도 있으므로 +1
        answer *= (dic[cloth_type] + 1)
    # 전부 안 입는 경우는 빼기(-1)
    answer -= 1
    return answer
