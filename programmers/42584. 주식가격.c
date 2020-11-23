// https://programmers.co.kr/learn/courses/30/lessons/42584

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int* solution(int prices[], size_t prices_len) {
    int* answer = (int*)malloc(prices_len*sizeof(int));
    int i, j;
    
    memset(answer, 0, prices_len*sizeof(int));
    
    for (i=0; i<prices_len; ++i) {
        int cnt = 0;
        for (j=i+1; j<prices_len; ++j) {
            ++cnt;
            if (prices[i] > prices[j]) break;
        }
        answer[i] = cnt;
    }
    
    return answer;
}
