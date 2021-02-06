// https://programmers.co.kr/learn/courses/30/lessons/60057

#include <string>
#include <vector>

using namespace std;

int solution(string s) {
    int n = s.size();
    int answer = n;
    
    // (block)개 단위로 따지기(2글자, 3글자, ...)
    for (int block=1; block<=n/2; ++block) {
        int length = 0;
        
        // i번째 block 기준으로 보기
        int i = 0;
        for (int i=0; i<n/block*block;) {
            int repeat = 1;
            // 다음 block이 같은건지 확인하기
            for (int j=i+block; j<n/block*block; j+=block) {
                int k;
                for (k=0; k<block; ++k) {
                    if (s[i+k] != s[j+k]) {
                        break;
                    }
                }
                
                // i번과 j번이 같다면, repeat++
                // 다르다면, i번째는 그만 따지기
                if (k==block) {
                    repeat++;
                } else {
                    break;
                }
            }
            
            // 반복된 수(1 제외)의 자리수만큼 length에 추가
            if (repeat > 1 and repeat < 10) length += 1;
            else if (repeat >= 10 and repeat < 100) length += 2;
            else if (repeat >= 100 and repeat < 1000) length += 3;
            
            // block 수만큼 length에 추가
            length += block;
                
            i += repeat*block;
        }
        
        // block단위가 아닌 남은 문자 수는 그대로 추가
        length += n % block;
        
        if (answer > length)
            answer = length;
    }
    
    return answer;
}
