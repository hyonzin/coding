// https://programmers.co.kr/learn/courses/30/lessons/12912

#include <stdio.h>
#include <stdlib.h>

#define ANSWER(a,b) (((long)b*(b+1)-(long)a*(a-1))/2)

long long solution(int a, int b) {
    if (a > b) return ANSWER(b, a);
    return ANSWER(a, b);
}
