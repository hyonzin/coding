# https://programmers.co.kr/learn/courses/30/lessons/42861

from operator import itemgetter

def solution(n, costs):
    # 알고리즘:
    #   비용 순으로 오름차순 정렬하고 
    #   저렴한 것부터 보면서, 사이클이 만들어지지 않게 그룹 짓기
    
    # 우선 비용순 정렬
    costs = sorted(costs, key=itemgetter(2))
    # 각 섬의 그룹 (다리가 하나도 안 지어졌으면 0)
    group = [0 for i in range(n)]
    # 다리 건설 총 비용
    total_cost = 0
    # 다리 지은 갯수 (반드시 n-1개 짓게 됨)
    cnt = 0
    # 그룹 갯수 (그룹은 1부터 시작하고, 새로 만들어질 때마다 +1)
    group_cnt = 0
    
    # 가장 저렴한 다리부터 하나씩 보기
    for c0, c1, cost in costs:
        # c0, c1 섬이 서로 다른 그룹이면?
        if group[c0] != group[c1]:
            # 둘 중 하나가 아직 그룹이 안 지어졌으면
            # 다른 하나의 그룹과 같은 그룹이 됨
            if group[c0] == 0:
                group[c0] = group[c1]
            elif group[c1] == 0:
                group[c1] = group[c0]
            # 만약 둘이 서로 다른 그룹이면
            # 모든 섬 중, c0과 같은 그룹인 섬들을
            # c1 그룹에 들어가게 함
            else:
                old = group[c0]
                new = group[c1]
                for j in range(n):
                    if group[j] == old:
                        group[j] = new
            # 다리 건설
            total_cost += cost
            cnt += 1
            # 다리를 총 n-1개 지었으면 끝
            if cnt == n-1:
                break
        # 두 섬의 그룹 값이 같은데, 둘 다 그룹이 안 매겨졌다면
        # (= 다리가 아직 지어진 적 없다면)
        # 둘 다 새로운 그룹으로 추가
        elif group[c0] == 0:
            # 새로운 그룹
            group_cnt += 1
            # 두 섬 다 새로운 그룹에 추가
            group[c0] = group[c1] = group_cnt
            # 다리 건설
            total_cost += cost
            cnt += 1
            # 다리를 총 n-1개 지었으면 끝
            if cnt == n-1:
                break
    
    return total_cost
