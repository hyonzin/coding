// https://programmers.co.kr/learn/courses/30/lessons/17676

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> start_time;
vector<int> end_time;

int solution(vector<string> lines) {
    int size = lines.size();
    for (int i=0; i<size; ++i) {
        int h, m;
        int s, ms;
        float duration;
        const char* line = lines[i].c_str()+11;

        sscanf(line, "%d:%d:%d.%d %fs", &h, &m, &s, &ms, &duration);
        // ms 단위로 시작시간, 종료시간 저장
        end_time.push_back(h*3600000 + m*60000 + s*1000 + ms);
        start_time.push_back(end_time.back() - (int)(duration*1000) + 1);
    }
    
    // 시작시간 오름차순 정렬 (종료시간은 입력될 때 정렬돼서 들어옴)
    sort(start_time.begin(), start_time.end());

    int answer = 0, cur = 0;
    int i=0, j=0;
    // 시작시간, 종료시간 따지면서 cur을 +1, -1 카운트
    while (i < size || j < size) {
        if (i < size && start_time[i] <= end_time[j]) {
            cur++;
            i++;
        } else {
            int c = 0;
            // 끝나는 시점에서, 1초 내에 새로 시작하는 작업들도 같이 세고(c), cur+c와 answer 비교
            for (int ii = i; ii < size && start_time[ii] - end_time[j] < 1000; ++ii) {
                c++;
            }
            if (cur + c > answer) answer = cur + c;
            cur--;
            j++;
        }
    }
    return answer;
}
