// https://www.acmicpc.net/problem/2579

#include <cstdio>

#define max(a,b) ((a)>(b)?(a):(b))

int N;
int score[301];
int memory[301][2];

int main(int argc, char* argv[]) {
    
    scanf("%d", &N);
    for (int i=0; i<N; ++i) {
        scanf("%d", &score[i+1]);
    }
	// score[i]: i번째 계단의 점수

	// memory[i]: i번째 계단을 밟는 시점에서,
	//   memory[i][0]: 앞으로 1칸 또는 2칸 갈 수 있는 경우, i부터 끝까지 얻을 수 있는 최대값
	//   memory[i][1]: 앞으로 반드시 2칸을 가는 경우, i부터 끝까지 얻을 수 있는 최대값

	// 마지막 계단은 무조건 그 점수로 설정
	memory[N][0] = score[N];
	memory[N][1] = score[N];
	if (N>1) {
		// 끝에서 2번째 계단은, 앞으로 1칸도 갈 수 있는 경우에만, 끝에서 2개 점수의 합이고
		memory[N-1][0] = score[N-1] + score[N];
		// 반드시 2칸 가는 경우는 불가능
		memory[N-1][1] = -10000000;
	}

	// 끝에서 3번째 계단부터, 반대 방향으로 보기
	for (int i=N-2; i>0; --i) {
		// 1칸 또는 2칸 갈 수 있으면,
		//   현재 점수 + MAX(1칸 가는 경우인 [i+1][1], 2칸 가는 경우인 [i+2][0])
		memory[i][0] = score[i] + max(memory[i+1][1], memory[i+2][0]);
		// 앞으로 무조건 2칸 가야하는 경우,
		//   현재 점수 + (2칸 가는 경우인 [i+2][0])
		memory[i][1] = score[i] + memory[i+2][0];
	}
    
	// 처음 시작점에서 1칸 가는 경우([1][0]) 또는 2칸 가는 경우[2][0]의 최대값
	// 단, 처음에는 1칸만 가도 또 1칸만 갈 수 있으므로, [1][1]이 아닌 [1][0]
	int answer = max(memory[1][0], memory[2][0]);
	printf("%d", answer);

  return 0;
}
