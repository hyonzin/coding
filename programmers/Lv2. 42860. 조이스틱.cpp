// https://programmers.co.kr/learn/courses/30/lessons/42860

#include <string>
#include <vector>
#include <cmath>

using namespace std;

int dif_A(char w) {
    if (w <= 'N')
        return w-'A';
    else
        return 'Z'+1-w;
}

int solution(string name) {
    int answer = 0;
    int n = name.size();
    
    int i, j;
    // 왼쪽으로 출발할지 오른쪽으로 출발할지
    // 정하기 위해, 두번째 글자 이후 또는 끝글자 이전 중
    // 어느 쪽에 'A'가 연속으로 많이 들어가는지 보기
    for (i=1; i<n; i++) {
        if (name[i]!='A')
            break;
    }
    for (j=1; j<n; j++) {
        if (name[n-j]!='A')
            break;
    }
    
    // 오른쪽으로 출발하는 경우와
    // 왼쪽으로 출발하는 경우 중
    // 이동 횟수가 적은 값을 저장
    answer = n - max(i, j);
    
    // 그런데 위의 경우는, 한쪽으로 출발하고
    // 다시 돌아오지 않는 경우임.
    // 한쪽으로 갔다가 돌아서 반대쪽으로 가는게
    // 최소일 수 있음
    // (예: "ABABAAAAAAAAAZ"의 경우
    //  끝으로 한번 갔다가 돌아와서(2) 오른쪽으로 3번
    //  가는게 최소임. 이 경우 답은 8
    
    // 일단 두번째 글자 이후로 A를 찾기
    for (i=1; i<n; ++i) {
        if (name[i] == 'A') {
            i--;
            // 연속된 A 확인
            for (j=i+2; j<n; ++j) {
                if (name[j] != 'A')
                    break;
            }
            // i+1 부터 j-1 까지 A가 있음
            
            // 이제 i까지 갔다가 돌아와서 j까지 가거나,
            // j까지 갔다가 돌아와서 i까지 가는 것 중
            // 더 짧은 것을 찾으면 됨
            
            int res;
            res = i*2 + (n-j);
            // i까지 갔다가 돌아와서 j까지 가는 것 
            answer = min(answer, res);
            // j까지 갔다가 돌아와서 i까지 가는 것 
            res = i + (n-j)*2;
            answer = min(answer, res);
            
            // 이제 j부터 A를 찾아서, 다시 반복함
            i = j;
        }
    }
    
    // 이동 횟수의 최소값은 이제 찾았고,
    // 알파벳들을 이동하는 횟수를 더함
    for (i=0; i<n; ++i)
        answer += dif_A(name[i]);
    
    return answer;
}
