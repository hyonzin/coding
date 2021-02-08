// https://programmers.co.kr/learn/courses/30/lessons/12978

from operator import itemgetter

def bfs(i):
    global K, queue, queue_cnt, ways, times, avail
    town, cur_time = queue[i]
    
    # 시간 기록한적 없거나, 현재 시간이 기록했던 시간보다 작을 때만 계속함
    if times[town] != -1 and cur_time >= times[town]:
        return
    
    # 현재 시간 기록
    times[town] = cur_time
    
    # K시간 이내에 가능한지는 queue에 넣을때 확인했으므로, 무조건 가능
    avail[town] = True
    
    # 현재 마을에서 갈 수 있는 모든 마을에 대해
    # (현재 걸린 시간 + 거기까지 가는 시간)이 K 이하인 경우에
    # 그 마을과 시간을 queue에 담음
    for town, time in ways[town]:
        if cur_time + time <= K:
            queue.append([town, cur_time + time])
            queue_cnt += 1

def solution(N, road, _K):
    global K
    K = _K
    answer = 0
    road = sorted(road, key=itemgetter(2))

    # 각 마을마다 갈수있는 마을과 가는 시간
    global ways
    ways = dict()
    for t1, t2, time in road:
        if t1 not in ways:
            ways[t1] = []
        if t2 not in ways:
            ways[t2] = []
        ways[t1].append([t2, time])
        ways[t2].append([t1, time])
    
    # 각 마을에 가는데 걸리는 시간
    global times
    times = [-1 for i in range(N+1)]
    
    # 각 마을에 갈 수 있는지 확인
    global avail
    avail = [False for i in range(N+1)]
    # 1에서 시작. 항상 배달 가능
    avail[1] = True
    
    # BFS
    global queue, queue_cnt
    queue_cnt = 1
    queue = [[1, 0]]
    i = 0
    while i < queue_cnt:
        bfs(i)
        i += 1
    
    # 배달 가능한 모든 마을의 수
    return sum(avail)
