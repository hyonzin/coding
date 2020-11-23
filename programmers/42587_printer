// https://programmers.co.kr/learn/courses/30/lessons/42587

#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(vector<int> priorities, int location) {
    int answer = 0;
    
    int cnt[10] = {0, };
    
    for (int i=0; i<priorities.size(); ++i) {
        cnt[priorities[i]]++;
    }
    
    int n = 9, p = 0, printed = 0;
    
    while (1) {
        while (cnt[n] <= 0) n--;
    
        while (cnt[n] > 0) {
            if (priorities[p] == n) {
                cnt[n]--;
                printed++;
                if (location == p) return printed;
            }
            p++;
            if (p >= priorities.size()) p = 0;
        }
    }
}
