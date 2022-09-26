# https://school.programmers.co.kr/learn/courses/30/lessons/42579

from queue import PriorityQueue
from collections import defaultdict

def solution(genres, plays):
    # 장르별 재생 횟수 합
    dict_sum = defaultdict(int)
    # 장르별, 노래별 (재생 횟수, 고유번호) 내림차순 우선순위큐
    dict_queue = defaultdict(PriorityQueue)
    
    for i, (genre, play) in enumerate(zip(genres, plays)):
        # 장르별 재생 횟수 합산
        dict_sum[genre] += play
        # 장르별, 노래별 (재생 횟수, 고유번호) 내림차순 우선순위큐 push
        dict_queue[genre].put((-play, i))
    
    # (재생 횟수 합, 장르) 내림차순 우선순위큐
    sum_queue = PriorityQueue()
    for genre, n_sum in dict_sum.items():
        sum_queue.put((-n_sum, genre))
    
    answer = []
    while not sum_queue.empty():
        # 재생 횟수 합이 가장 많은 장르 pop
        _, genre = sum_queue.get()
        n = 0
        while not dict_queue[genre].empty():
            # 해당 장르 내에서 재생 횟수가 가장 많은 노래 pop
            _, idx = dict_queue[genre].get()
            answer.append(idx)
            # 장르별 최대 2개만 pop
            n += 1
            if n == 2:
                break
    
    return answer
