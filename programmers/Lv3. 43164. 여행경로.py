# https://programmers.co.kr/learn/courses/30/lessons/43164?language=python3

ways = dict()
answer = []
N = 0

def check(frm, n):
    global N
    if n >= N+1:
        return 1
    
    if frm not in ways:
        return 0
    
    for visit in ways[frm]:
        to = visit[0]
        if visit[1] == 1:
            continue
        answer[n] = to
        visit[1] = 1
        if check(to, n+1) == 1: 
            return 1
        visit[1] = 0
        
    return 0

def solution(tickets):
    global N
    N = len(tickets)
    answer.append("ICN")
    
    for i in range(N):
        frm = tickets[i][0]
        to = tickets[i][1]
        
        if frm not in ways:
            ways[frm] = [[to, 0]]
        else:
            for j in range(len(ways[frm])):
                if ways[frm][j][0] > to:
                    swp = to
                    to = ways[frm][j][0]
                    ways[frm][j][0] = swp
            ways[frm].append([to, 0])
        answer.append("")
    
    check("ICN", 1)
    return answer
