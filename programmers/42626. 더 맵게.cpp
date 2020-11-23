// https://programmers.co.kr/learn/courses/30/lessons/42626

#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> scoville, int K) {
    int num1, num2;
    int answer = 0;
    int newnum;

    std::make_heap(scoville.begin(), scoville.end(), std::greater<>{});
    
    while (1) {
        if (scoville.front() >= K) return answer;
        if (scoville.size() < 2) return -1;

        pop_heap(scoville.begin(), scoville.end(), std::greater<>{});
        num1 = scoville.back();
        scoville.pop_back();
        pop_heap(scoville.begin(), scoville.end(), std::greater<>{});
        num2 = scoville.back();
        scoville.pop_back();
        newnum = num1 + (2 * num2);
        answer++;
        
        scoville.push_back(newnum);
        push_heap(scoville.begin(), scoville.end(), std::greater<>{});
    }
    return -2;
}
