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
    
    // 모든 문자를 이동하는 경우로 초기값
    answer = n - 1;
    
    // 일단 두번째 글자 이후로 A를 찾기
    for (int i=1; i<n; ++i) {
        if (name[i] == 'A') {
            i--;
            // 연속된 A 확인
            int j;
            for (j=i+2; j<n; ++j) {
                if (name[j] != 'A')
                    break;
            }
            // i+1 부터 j-1 까지 A가 있음
            
            // 이제 i까지 갔다가 돌아와서 j까지 가거나,
            // j까지 갔다가 돌아와서 i까지 가는 것 중
            // 더 짧은 것을 찾으면 됨
            int res;
            
            // i까지 갔다가 돌아와서 j까지 가는 것
            res = i*2 + (n-j);
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
    for (int i=0; i<n; ++i)
        answer += dif_A(name[i]);
    
    return answer;
}
