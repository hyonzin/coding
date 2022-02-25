// https://www.acmicpc.net/problem/21925
#include <stdio.h>
#include <stdlib.h>

int N = 0;
unsigned short* A;
int NT = 0;
int t_start = 0;

int main(int argc, char* argv[]) {
  // FILE* fp = fopen("input.txt", "r");
  FILE* fp = stdin;

  int answer = 0;
  int i, a, t;

  fscanf(fp, "%d", &N);
  A = (unsigned short*) malloc(N * sizeof(unsigned short));
  for( i=0; i<N; ++i ){
    fscanf(fp, "%hu", &A[i]);
  }

  for( i=0; i<N; ++i ){
    if( NT > 0 && A[i-1] == A[i] ){
      char valid = 0;
      // compare
      for( a = i, t = i-1; a < N && t >= t_start ; a++, t-- ){
        if( A[t] != A[a] ){
          valid = 1;
          break;
        }
      }

      // valid?
      if( t < t_start && valid == 0 ){
        answer++;
        i = a - 1;
        t_start = a;
        NT = 0;
      }else{
        // add
        NT++;
      }
    }else{
      // add
      NT++;
    }
  }

  if( NT==0 ){
    printf("%d", answer);
  }
  else{
    printf("-1");
  }

  free(A);

  return 0;
}
