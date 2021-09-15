# https://programmers.co.kr/learn/courses/30/lessons/42583

def solution(bridge_length, weight, truck_weights):
    # 흐른 시간
    step = 0
    # 현재 다리 위에 있는 트럭들의 무게
    cur_w = 0
    # 대기 트럭 중 가장 앞의 트럭
    head = 0
    # 트럭 총 대수
    Ntruck = len(truck_weights)
    # 다리 위에 있는 트럭들 [[무게, 끝나는 step], ...]
    on_bridge = []
    # 다리 위에 있는 트럭 중 가장 앞 트럭
    on_bridge_head = 0
    
    # 모든 트럭이 다리를 건널 때까지 반복
    while head < Ntruck or cur_w != 0:
        # 다리 위에 트럭이 있다면,
        if on_bridge_head < len(on_bridge):
            # 가장 앞 트럭이 끝날 시간이 됐는지 확인
            if on_bridge[on_bridge_head][1] == step:
                # 시간이 됐다면 현재 다리 무게에서 빼고
                cur_w -= on_bridge[on_bridge_head][0]
                # 다리 위의 다음 트럭을 봄
                on_bridge_head += 1
                
        # 아직 대기 트럭이 남아있다면
        if head < Ntruck:
            # 다리에 오를 수 있는지 무게 확인
            if truck_weights[head] + cur_w <= weight:
                # 다리의 현재 무게에 추가하고
                cur_w += truck_weights[head]
                # 다리 위 트럭 목록에 [무게, 끝나는 step 수] 추가
                on_bridge.append([truck_weights[head], step+bridge_length])
                # 대기 트럭 중 다음 트럭을 봄
                head += 1
        # 시간 1 경과
        step += 1
    
    # 대기 트럭도 없고 다리 위 무게도 0이면 종료
    return step
