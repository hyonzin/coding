// https://programmers.co.kr/learn/courses/30/lessons/12953

#include <string>
#include <vector>

using namespace std;

int table[101][101] = {0,};

int solution(vector<int> arr) {
    int answer = 1;
    
    // 각 수의 모든 약수의 개수 구하기
    for (int i=0; i<arr.size(); ++i) {
        // 이미 구한 숫자면 스킵
        if (table[arr[i]][0] != 0) continue;
        
        // table[입력값][0] = 이미 구한 숫자인가(1 또는 0);
        table[arr[i]][0] = 1;
        
        // table[입력값][약수] = 개수;
        int num = arr[i];
        for (int j=2; j<=arr[i]/2+1; ++j) {
            if (num % j == 0) {
                table[arr[i]][j]++;
                num /= j;
                j—;
            }
        }
        
        // 더이상 나누어 떨어지는 수가 없으면 table[입력값][num]++;
        if (num > 1) {
            table[arr[i]][num]++;
        }
    }
    
    // 각 약수의 최대값 만큼 answer *= 약수
    for (int j=2; j<101; ++j) {
        int max = 0;
        for (int i=0; i<arr.size(); ++i) {
            if (table[arr[i]][j] > max)
                max = table[arr[i]][j];
        }
        for (int i=0; i<max; ++i)
            answer *= j;
    }
    
    return answer;
}
