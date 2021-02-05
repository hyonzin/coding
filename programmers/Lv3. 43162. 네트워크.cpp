# https://programmers.co.kr/learn/courses/30/lessons/43162

#include <string>
#include <vector>

using namespace std;

int solution(int n, vector<vector<int>> computers) {
    // 각 컴퓨터의 네트워크 id를 저장할 리스트
    vector<int> nets;
    nets.resize(n);
    int net_cnt = 0;
    int merge_cnt = 0;
    
    for (int i=0; i<n; ++i) {
        // i번째 컴퓨터의 네트워크 id를 매긴적 없다면 net_cnt += 1
        // i번째의 id = 현재의 net_cnt 값
        if (nets[i] == 0) {
            net_cnt += 1;
            nets[i] = net_cnt;
        }
        
        // i번째 컴퓨터의 네트워크 id = net_id
        int net_id = nets[i];
        
        // i번째와 연결된 컴퓨터들도 같은 네트워크 id를 줌
        for (int j=i+1; j<n; ++j) {
            // 연결돼있는지 확인
            if (computers[i][j] == 1) {
                // 아직 id를 준 적 없다면, net_id로 바로 설정
                if (nets[j] == 0) {
                    nets[j] = net_id;
                }
                // 만약, i번째와 연결돼있는 j번째가,
                // 이미 다른 네트워크 id(old_id)를 받은 상태라면,
                // 모든 네트워크 중 old_id를 가진 컴퓨터들을 net_id로 업데이트
                // 그리고 이렇게 합쳐진(merge) 횟수를 기억 (merge_cnt+=1)
                else if (nets[j] != net_id) {
                    int old_id = nets[j];
                    for (int k=0; k<n; ++k) {
                        if (nets[k] == old_id)
                            nets[k] = net_id;
                    }
                    merge_cnt+=1;
                }
            }
        }
    }
    
    // 네트워크를 새로 매긴 수(net_cnt)에서 네트워크를 합한 횟수(merge_cnt)를 뺌
    int answer = net_cnt - merge_cnt;
    
    return answer;
}
