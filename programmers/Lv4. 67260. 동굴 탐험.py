# https://school.programmers.co.kr/learn/courses/30/lessons/67260

from collections import defaultdict, deque

def solution(n, path, order):
    # 통로 (paths[0] = [1, 2, 3, ...])
    paths = defaultdict(list)
    # 순서 (orders[2] = 1   : 1 먼저 가야 2 가능)
    orders = {}
    # 방문여부 (a 방문시 visits[a] = True)
    visits = {}
    
    # 통로 세팅
    for a_path in path:
        # [0, 1] 이면,  pahts[0].append(1); pahts[1].append(0);
        paths[a_path[0]].append(a_path[1])
        paths[a_path[1]].append(a_path[0])
    # 순서 세팅
    for a_order in order:
        orders[a_order[1]] = a_order[0]
    
    # 방문할 방 저장할 큐 (DFS)
    queue = deque()
    queue.append(0) #최초 0 방문
    
    # 기다린 횟수 체크 ()
    n_wait = 0
    n_remained_order_checked = len(order)
    
    while len(queue) > 0:
        # 다음 방 체크 (pop)
        look = queue.popleft()
        # 순서를 지켜야 할 방이면?
        if look in orders:
            # 먼저 가야할 방을 아직 안 들렀다면?
            if orders[look] not in visits:
                # 지금 방은 다음에 다시 들리기 (append)
                queue.append(look)
                # 기다린 횟수 체크
                n_wait += 1
                # 만약, 대기해야 되는 방 수보다 많이 이미 기다렸다면,
                # 더이상 갈 수 있는 방이 없다는 뜻
                if n_wait > n_remained_order_checked:
                    return False
                continue
            n_remained_order_checked -= 1
        n_wait = 0
        
        # 더이상 순서 기다려야 하는 방이 안 남았다면,
        # 남은 방은 모두 출입이 가능 -> True 리턴
        if n_remained_order_checked == 0:
            return True
        
        # 방문 체크
        visits[look] = True
        # 다음으로 갈 수 있는 방들 queue에 추가 (appendleft)
        for look_next in paths[look]:
            if look_next not in visits:
                queue.appendleft(look_next)
    return True
