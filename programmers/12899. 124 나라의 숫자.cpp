// https://programmers.co.kr/learn/courses/30/lessons/12899

#include <string>
#include <vector>

using namespace std;
int digits[3] = {1, 2, 4};

string digit124(int n){
    int offset = 0;
    int k = 1;
    if (n < 3) return to_string(digits[n]);

    while(offset + k * 3 <= n){
        k *= 3;
        offset += k;
    }
    int digit = (n - offset) / k;
    return to_string(digits[digit]) + digit124(n - (digit + 1)*k);
}

string solution(int n) {
    n--;
    return digit124(n);
}
