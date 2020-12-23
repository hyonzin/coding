// https://programmers.co.kr/learn/courses/30/lessons/42891

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> food_times, long long k) {
    int N = food_times.size();
    
    // food_times를 정렬한 sorted
    vector<int> sorted;
    sorted.assign(food_times.begin(), food_times.end());
    sort(sorted.begin(), sorted.end());
    
    // 정렬된 sorted를 하나씩 보며,
    // sorted[i] 걸리는 음식을 다 먹을 때 까지도 안 끝나는지 확인하기
    int i = 0;
    int eaten = 0;
    while (i < N) {
        if (sorted[i] <= eaten) {
            i++;
        } else {
            long eat = (long)(sorted[i] - eaten) * (N-i);
            if (eat <= k) {
                k -= eat;
                eaten = sorted[i];
                i++;
            } else {
                break;
            }
        }
    }
    
    // k 안에 다 먹는 경우
    if (i == N) return -1;
    
    // 이하, 먹는 도중에 반드시 멈추는 경우
    // (target) 이상만큼 걸리는 음식을 다 먹기 전에 반드시 멈춘다.
    int target = sorted[i];
    
    // (target) 이상인 음식을 하나씩 먹는다.
    // 그 음식의 개수는 (N-i)
    while (k >= (N-i)) {
        k -= (N-i);
    }
    
    // (target) 이상인 음식 중 k번째를 먹을 차례일 때 멈춘다.
    i = 0;
    while (1) {
        if (food_times[i] >= target) {
            if (k == 0) return i+1;
            else k--;
        }
        i++;
    }
    
    // 여기까진 도달하지 않음
    return -2;
}
