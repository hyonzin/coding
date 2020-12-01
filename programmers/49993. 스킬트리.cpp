// https://programmers.co.kr/learn/courses/30/lessons/49993

#include <string>
#include <vector>

using namespace std;

int solution(string skill, vector<string> skill_trees) {
    int answer = 0;
    const char* order = skill.c_str();
    int failed, stop;
    
    for (int i=0; i<skill_trees.size(); ++i) {
        int j = 0, k = 0, pos = -1;
        const char* tree = skill_trees[i].c_str();
        failed = 0;
        stop = 0;
        
        while (order[j]) {
            int k = 0;
            while (tree[k]) {
                if (tree[k] == order[j]) break;
                k++;
            }
            if (tree[k]) {
                if (stop || k < pos) {
                    failed = 1;
                    break;
                }
                pos = k;
            } else {
                if (stop == 0) stop = 1;
            }
            j++;
        }
        
        if (!failed) answer++;
    }
    return answer;
}
