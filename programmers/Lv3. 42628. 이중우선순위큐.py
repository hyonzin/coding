# https://school.programmers.co.kr/learn/courses/30/lessons/42628

from queue import PriorityQueue

def get_from_queue(queue, val, active_list):
    while True:
        value, idx = queue.get()
        if active_list[idx] == True:
            active_list[idx] = False
            return value * -val

def solution(operations):
    answer = []
    
    length = 0
    value_list = []
    active_list = []
    consumed = 0
    
    min_queue = PriorityQueue()
    max_queue = PriorityQueue()
    
    for line in operations:
        op, val = line.split()
        val = int(val)
        if op == 'I':
            value_list.append(val)
            active_list.append(True)
            min_queue.put((val, length))
            max_queue.put((-val, length))
            length += 1
        elif op == 'D':
            if length == consumed:
                continue
            queue = max_queue if val == 1 else min_queue
            get_from_queue(queue, val, active_list)
            consumed += 1
    
    if consumed == length:
        return [0, 0]
    else:
        max_val = get_from_queue(max_queue, 1, active_list)
        if consumed == length:
            return [max_val, max_val]
        min_val = get_from_queue(min_queue, -1, active_list)
        return [max_val, min_val]
