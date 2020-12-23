// https://programmers.co.kr/learn/courses/30/lessons/42586

#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    int cnt = 0;
    int passed = 0;
    for (int i=0; i<progresses.size(); ++i) {
        int days = ((100 - progresses[i]) % speeds[i])?
            (100 - progresses[i]) / speeds[i] + 1:
            (100 - progresses[i]) / speeds[i];
        if (days > passed) {
            if (passed > 0) {
                answer.push_back(cnt);
                cnt = 0;
            }
            passed = days;
        }
        cnt++;
    }
    if (cnt > 0) {
        answer.push_back(cnt);
    }
    return answer;
}
