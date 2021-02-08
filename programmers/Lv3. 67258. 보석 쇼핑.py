# https://programmers.co.kr/learn/courses/30/lessons/67258

def solution(gems):
    # 모든 종류의 보석
    types = set(gems)
    # 보석의 종류의 수
    Ntypes = len(types)
    if Ntypes == 1:
        return [1, 1]
    
    # 보석 수
    N = len(gems)
    # 보석의 인덱스 기억
    idx = dict()
    # 구매한 보석 갯수 기억
    buy = dict()
    for k, v in enumerate(types):
        idx[v] = k
        buy[v] = 0
    
    # 전체를 사는 경우로 초기화
    answer_len = N
    answer_start = 1
    answer_end = N

    i = 0
    j = 0
    # 0이 아닌 보석의 개수 (number of non zero)
    nnz = 0
    while i<N:
        # i부터, 모든 종류의 보석을 사는 범위인 j까지 찾기
        while nnz<Ntypes and j<N:
            if buy[gems[j]] == 0:
                nnz += 1
            buy[gems[j]] += 1
            j += 1
        
        # 모든 보석을 순회한 시점에, 0개인 종류가 있다면 그만 보기
        if nnz<Ntypes:
            break;
        
        # i번째부터 j-1번째까지, 모든 보석이 1개 이상 있다
        # 맨앞에서부터 2개 이상인 보석들을 하나씩 제외시킴
        x = i
        y = j-1
        while buy[gems[x]] > 1:
            buy[gems[x]] -= 1
            x += 1
            
        # 이제 x번째, y번째 종류는 1개씩만 있고,
        # 그 사이에 있는 나머지 종류는 1개 이상 있음
        if y-x+1 < answer_len:
            answer_len = y-x+1
            answer_start = x+1
            answer_end = y+1
        
        # 다 따졌으니, 1개 뿐인 x번째는 제외시킴
        buy[gems[x]] -= 1
        nnz -= 1
        x += 1
        
        # 그 뒤로, 2개 이상인 보석들은 제외시킴
        while buy[gems[x]] > 1:
            buy[gems[x]] -= 1
            x += 1
            
        # 이제 x번째는 1개 뿐인 보석이거나,
        # 아까 제외한 1개뿐인 보석이어서 0개인 보석임
        i = x
        # j는 아까 봐둔 곳부터 이어서 보면 됨
    
    answer = [answer_start, answer_end]
    return answer
