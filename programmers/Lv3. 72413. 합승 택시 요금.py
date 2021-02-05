# https://programmers.co.kr/learn/courses/30/lessons/72413

def check_minimum_cost(now, cost_X, cur_cost):
    # 이전에 체크했을 때 이미 더 저렴한 가격으로 왔었다면, return
    if cost_X[now] != -1 and cost_X[now] <= cur_cost:
        return
    
    # 이 노드까지의 최소요금 업데이트
    cost_X[now] = cur_cost
    
    global ways
    global q_cnt
    global q
    
    # 이 노드와 연결된 다른 노드들 주소와, 가는 비용을 queue에 추가
    for way in ways[now]:
        q.append([way[0], cur_cost+way[1]])
        q_cnt += 1

def find_minimum_cost(now, cost_X):
    global ways
    
    # BFS를 위한 queue
    global q_cnt
    global q
    q_cnt = 1
    q = [[now, 0]]
    
    # 작업 queue에 남는게 없을 때까지 반복
    i = 0
    while i < q_cnt:
        # i번째 작업: [0]까지 갈때 [1] 요금이 드는데, 최소인지 확인
        check_minimum_cost(q[i][0], cost_X, q[i][1])
        i += 1

def solution(n, s, a, b, fares):
    
    global ways #  ways[i]: i노드에서 연결된 길들과 비용 [길, 비용]
    ways = []
    for i in range(n+1):
        ways.append([])
    for fare in fares:
        ways[fare[0]].append([fare[1], fare[2]])
        ways[fare[1]].append([fare[0], fare[2]])
    
    global cost_A # 각 노드에서 A까지의 최소요금
    global cost_B # 각 노드에서 B까지의 최소요금
    global cost_S # 각 노드에서 S까지의 최소요금
    cost_A = [-1 for i in range(n+1)]
    cost_B = [-1 for i in range(n+1)]
    cost_S = [-1 for i in range(n+1)]
    
    # 각 노드에서 A, B, S로 가는 최소요금 계산
    find_minimum_cost(a, cost_A)
    find_minimum_cost(b, cost_B)
    find_minimum_cost(s, cost_S)
    
    # 각 노드에서 A, B, S까지의 최소요금의 합의 최소값
    #  = S까지 같이 타고 A, B 따로 가는 요금의 최소값
    min_cost = -1
    for i in range(1, n+1):
        if cost_A[i] != -1 and cost_B[i] != -1 and cost_S[i] != -1:
            cost = cost_A[i] + cost_B[i] + cost_S[i]
            if min_cost == -1 or min_cost > cost:
                min_cost = cost
            
    return min_cost
