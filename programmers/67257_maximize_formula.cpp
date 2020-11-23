// https://programmers.co.kr/learn/courses/30/lessons/67257

#include <string>
#include <vector>
#include <string.h>

#define Lprintf(...) ;

using namespace std;

long long list[100];
int list_cnt = 0;
long long li[2][100];
int li_cnt[2];
int sel = 0;

long long cal(long long a, char op, long long b) {
    if (op=='+') return a+b;
    if (op=='-') return a-b;
    if (op=='*') return a*b;
    return -999999;
}

long long check(char* op) {
    long long res = 0;
    memcpy(li[sel], list, list_cnt*sizeof(long long));
    li_cnt[sel] = list_cnt;

    for (int o=0; o<3; ++o) {
        li_cnt[1-sel] = 0;
        for (int i=1; i<li_cnt[sel]; i+=2) {
            if (li[sel][i] == op[o]) {
                li[sel][i] = 0;
                Lprintf("  %lld %c %lld\n", li[sel][i-1], (char)li[sel][i], li[sel][i+1]);
                li[sel][i+1] = cal(
                    li[sel][i-1],
                    op[o],
                    li[sel][i+1]
                );
                Lprintf("    > %lld\n", li[sel][i+1]);
            } else if (li[sel][i] == 0) {
                continue;
            } else {
                li[1-sel][li_cnt[1-sel]  ] = li[sel][i-1];
                li[1-sel][li_cnt[1-sel]+1] = li[sel][i];
                li_cnt[1-sel] += 2;
            }
        }
        li[1-sel][li_cnt[1-sel]++] = li[sel][li_cnt[sel]-1];
        sel = 1 - sel;
    }

    res = li[sel][0];

    return (res<0)? -res : res;
}

long long solution(string expression) {
    long long answer = 0;
    int n = 0;

    for (int i=0; i<expression.length(); ++i) {
        char c = expression[i];
        if (c == '+') {
            list[list_cnt++] = n;
            list[list_cnt++] = (int)'+';
            n = 0;
        }
        else if (c == '-') {
            list[list_cnt++] = n;
            list[list_cnt++] = (int)'-';
            n = 0;
        }
        else if (c == '*') {
            list[list_cnt++] = n;
            list[list_cnt++] = (int)'*';
            n = 0;
        }
        else {
            n = 10*n + (int)(c-'0');
        }
    }
    list[list_cnt++] = n;

    long long res;
    res = check("+-*"); if (res > answer) answer = res; Lprintf("%lld\n", res);
    res = check("+*-"); if (res > answer) answer = res; Lprintf("%lld\n", res);
    res = check("-+*"); if (res > answer) answer = res; Lprintf("%lld\n", res);
    res = check("-*+"); if (res > answer) answer = res; Lprintf("%lld\n", res);
    res = check("*+-"); if (res > answer) answer = res; Lprintf("%lld\n", res);
    res = check("*-+"); if (res > answer) answer = res; Lprintf("%lld\n", res);

    return answer;
}
