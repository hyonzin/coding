# https://school.programmers.co.kr/learn/courses/30/lessons/42628

from queue import PriorityQueue

def solution(operations):
    # insert한 개수    
    length = 0
    # delete한 개수
    consumed = 0
    # insert된 숫자들
    value_list = []
    # queue에 들어있는지 여부 (insert할때마다 True 삽입)
    active_list = []
    
    # min, max 이중 우선순위큐
    min_queue = PriorityQueue()
    max_queue = PriorityQueue()
    
    for line in operations:
        op, val = line.split()
        val = int(val)
        if op == 'I':
            # 숫자, active(True) 인서트
            value_list.append(val)
            active_list.append(True)
            # min, max 각각 인서트.
            #   (값, 인덱스) 인서트함.
            #     인덱스를 넣어야, 한 우선순위 큐에서 pop 했을 때
            #     active_list[idx] = False 업데이트 함으로써
            #     다른 우선순위 큐에서 그 값이 pop된 걸 알게 할 수 있으므로.
            #   첫번째 값이 정렬기준이 되므로(오름차순),
            #     max_queue는 첫번째 값을 -로 삽입.
            min_queue.put((val, length))
            max_queue.put((-val, length))
            # insert한 개수 +1
            length += 1
        elif op == 'D':
            # 하나도 없는 상태에서 delete 시도시 continue
            if length == consumed:
                continue
            # val에 따라 1이면 max, -1이면 min queue
            queue = max_queue if val == 1 else min_queue
            # 우선순위큐에서 값을 하나 뺌 (max 또는 min queue에서)
            get_from_queue(queue, val, active_list)
            # delete한 개수 +1
            consumed += 1
    
    if consumed == length:
        # 전부 delete된 상태라면 [0, 0] 리턴
        return [0, 0]
    else:
        # 최대값 pop
        max_val = get_from_queue(max_queue, 1, active_list)
        if consumed == length:
            # 하나도 안 남았다면(=값이 하나밖에 없었다면) 최대값==최소값
            return [max_val, max_val]
        # 최소값 pop
        min_val = get_from_queue(min_queue, -1, active_list)
        return [max_val, min_val]

# 큐에서 값을 pop하는 함수
#   min 또는 max queue를 받아, 값 한개를 pop함.
#   만약 pop한 값의 인덱스가 active_list[idx] == False 라면,
#     또다른 우선순위큐에서 pop한 값이라는 뜻이므로
#     다시 pop함.
def get_from_queue(queue, val, active_list):
    while True:
        value, idx = queue.get()
        if active_list[idx] == True:
            active_list[idx] = False
            return value * -val
