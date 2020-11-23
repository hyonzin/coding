// https://programmers.co.kr/learn/courses/30/lessons/42747

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> citations) {
    int size = citations.size();
    int i, cnt = 0, num = 0;
    sort(citations.begin(), citations.end());

    // 제일 큰 값이 0이면 바로 0 리턴
    if (citations[size-1] == 0) return 0;
    
    // 제일 큰 값을 num에 넣고, cnt 1부터 시작, 큰 값부터 하나씩 보기
    for (i = size-2, cnt = 1, num = citations[size-1]; i>=0; --i) {
        // num과 같다면 cnt만 +1
        if (citations[i] == num) {
            cnt++;
        // 더 작은 값이라면, num 갱신하고, cnt +1
        } else {
            num = citations[i];
            cnt++;
        }
        
        // num 갱신하기 전까지의 cnt가 num 이상이면, 갱신하기 전의 cnt를 리턴
        // 아니라면, num회 인용한 논문이 cnt개 이상이므로, num을 리턴
        if (cnt-1 >= num) return (cnt-1>num? cnt-1:num);
    }
    
    // 위 for문을 빠져나왔다면,
    // 모든 논문의 인용 수가 전체 논문 수(= n = cnt)보다 많다는 의미이므로
    // cnt를 리턴
    return cnt;
}
