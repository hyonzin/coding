// https://programmers.co.kr/learn/courses/30/lessons/43162

#include <string>
#include <vector>

using namespace std;
// 각 컴퓨터의 네트워크 id를 저장할 리스트
vector<int> nets;

// 네트워크 개수
int net_cnt = 0;

int N;
vector<vector<int>> computers;

void dfs(int computer, int net_id) {
    // id 매긴적 없는지 확인
    if (nets[computer] > 0)
        return;
    
    // 새 네트워크를 만들어야되는지 확인
    if (net_id == 0)
        net_id = ++net_cnt;
    
    // 이 컴퓨터의 id는 net_id
    nets[computer] = net_id;
    
    // 이 컴퓨터와 연결된 모든 컴퓨터도 net_id
    for (int i=0; i<N; ++i) {
        if (computers[computer][i]) {
            dfs(i, net_id);
        }
    }
}

int solution(int n, vector<vector<int>> _computers) {
    nets.resize(n);
    N = n;
    computers = _computers;
    
    for (int i=0; i<n; ++i) {
        dfs(i, nets[i]);
    }
    
    return net_cnt;
}
