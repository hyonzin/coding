// https://programmers.co.kr/learn/courses/30/lessons/64064

#include <string>
#include <cstring>
#include <vector>

using namespace std;

bool table[8][8];
bool ban_table[64][8];
bool cur_banned[8];
int b_count = 0;

int Nu, Nb;

int check(int u) {
    int res = 0;
    
    if (u == Nu) {
        for (int b=0; b<Nb; ++b) {
            if (!cur_banned[b]) return 0;
        }

        for (int bc=0; bc<b_count; ++bc) {
            for (u=0; u<Nu; ++u) {
                if (ban_table[b_count][u] != ban_table[bc][u]) {
                    break;
                }
            }
            if (u==Nu) {
                return 0;
            }
        }

        memcpy(ban_table[b_count+1], ban_table[b_count], Nu*sizeof(bool));
        b_count++;
        return 1;
    }
    
    res += check(u+1);
    for (int b=0; b<Nb; ++b) {
        if (table[u][b] && !cur_banned[b]) {
            ban_table[b_count][u] = true;
            cur_banned[b] = true;
            res += check(u+1);
            ban_table[b_count][u] = false;
            cur_banned[b] = false;
        }
    }
    
    return res;
}

int solution(vector<string> user_id, vector<string> banned_id) {
    int answer = 0;
    Nu = user_id.size();
    Nb = banned_id.size();
    
    for (int b=0; b<Nb; ++b) {
        for (int u=0; u<Nu; ++u) {
            if (user_id[u].size() == banned_id[b].size()) {
                int c;
                for (c=0; c<user_id[u].size(); ++c) {
                    if (banned_id[b][c] != '*' &&
                        banned_id[b][c] != user_id[u][c]) {
                        break;
                    }
                }
                if (c == user_id[u].size()) {
                    table[u][b] = true;
                }
            }
        }
    }
    answer = check(0);
    return answer;
}
