// 

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20
#define STATE 0
#define UP    1
#define DOWN  2
#define LEFT  3
#define RIGHT 4

#define SHARK_X        0
#define SHARK_Y        1
#define SHARK_DIRECT   2
#define SHARK_IS_ALIVE 3

#define ALIVE_Y 0
#define ALIVE_N 1

#define MOVED_X(d, x) ( ((d) == LEFT)? ((x)-1) : ((d) == RIGHT)? ((x)+1) : (x) )
#define MOVED_Y(d, y) ( ((d) == UP  )? ((y)-1) : ((d) == DOWN )? ((y)+1) : (y) )

// 맵 크기, 상어 수, 냄새유지시간
int N, M, k;
// 현재 시간
int cur_time = 0;
// 남은 상어 수
int n_alive;

// 어느 상어의 냄새가 남았는지
short smell_who[MAX_N][MAX_N] = {0, };
// 냄새가 얼마나 세게 남았는지 (냄새를 남긴 시간)
short smell_power[MAX_N][MAX_N] = {0, };
// 상어 정보 (좌표, 방향, 살아남았나 여부, 방향별 우선순위)
short shark[MAX_N * MAX_N + 1][5][4] = {0, }; // [1부터 시작하는 상어 인덱스][[x, y, dir, alive=0], 4개방향 우선순위 4개씩]

int main(int argc, char* argv[]) {
  int m, d, i;
  int x, y;
  FILE* fp = stdin;
  // FILE* fp = fopen("input1.txt", "r");

  // N, M, k 입력
  fscanf(fp, "%d %d %d", &N, &M, &k);
  // 상어들의 초기 위치 입력
  for (y = 0; y < N; ++y) {
    for (x = 0; x < N; ++x) {
      fscanf(fp, "%d", &m);
      if (m > 0) {
        // 상어 기준, 상어의 위치
        shark[m][STATE][SHARK_X] = x;
        shark[m][STATE][SHARK_Y] = y;
      }
    }
  }
  // 상어들의 초기 방향 입력
  for (m = 1; m <= M; ++m) {
    fscanf(fp, "%hd", &shark[m][STATE][SHARK_DIRECT]);
  }
  // 상어들의 방향별 우선순위 입력
  for (m = 1; m <= M; ++m) {
    // m상어의 d방향
    for (d = 1; d <= 4; ++d) {
      // d방향의 4개 우선순위
      for (i = 0; i < 4; ++i) {
        fscanf(fp, "%hd", &shark[m][d][i]);
      }
    }
  }

  // 남은 상어 수
  n_alive = M;

  // Main Loop
  while (cur_time <= 1000) {
    // 1. 상어가 겹칠때 쫓겨나는 단계
    // 각 상어에 대해,
    for (m = 1; m <= M; ++m) {
      // 쫓겨난 상어는 스킵
      if (shark[m][STATE][SHARK_IS_ALIVE] == ALIVE_N) continue;
      // 상어의 현재 위치
      x = shark[m][STATE][SHARK_X];
      y = shark[m][STATE][SHARK_Y];
      // 현재위치에 자기보다 센 상어가 있다면,
      if (smell_who[x][y] > 0 && smell_who[x][y] < m && smell_power[x][y] == cur_time) {
        // 상어가 쫓겨남
        shark[m][STATE][SHARK_IS_ALIVE] = ALIVE_N;
        // 남은 상어 수 -1
        n_alive--;
      }
      // 현재위치에서 자기가 가장 센 상어라면,
      else {
        // 현재 위치에 냄새를 남김.
        smell_who[x][y] = m;
        // 냄새 값 = cur_time(지난 초).
        smell_power[x][y] = cur_time;
      }
    }
    // 한 마리만 남았으면 종료
    if (n_alive == 1) break;

    // 2. 이동하는 단계
    // 각 상어에 대해,
    for (m = 1; m <= M; ++m) {
      // 쫓겨난 상어는 스킵
      if (shark[m][STATE][SHARK_IS_ALIVE] == ALIVE_N) continue;
      // 상어의 방향과 위치
      short d = shark[m][STATE][SHARK_DIRECT];
      short x = shark[m][STATE][SHARK_X];
      short y = shark[m][STATE][SHARK_Y];
      // 현재 방향에 따른 우선순위 방향
      short* dirs = shark[m][d];
      // 이동 가능한지 체크할 좌표와 방향
      short mov_x, mov_y, mov_d;
      // 이동하기로 결정된 좌표와 방향
      short sel_x, sel_y, sel_d = -1;
      // 자신의 방향의 우선순위 각각에 대해서
      for (i = 0; sel_d < 0 && i < 4; ++i) {
        // 우선순위에 따라, 바라볼 방향과 그 좌표
        mov_d = dirs[i];
        mov_x = MOVED_X(mov_d, x);
        mov_y = MOVED_Y(mov_d, y);
        // 변두리가 아니고, 냄새가 없거나, 있지만 차이가 k 이상인 경우
        if (mov_x >= 0 && mov_x < N &&
            mov_y >= 0 && mov_y < N &&
            (smell_who[mov_x][mov_y] == 0 ||
             (cur_time - smell_power[mov_x][mov_y]) >= k)) {
          // 이동 예정 좌표기록 (x,y)
          sel_x = mov_x;
          sel_y = mov_y;
          sel_d = mov_d;
        }
      }
      // 위 이동 실패시, 다시 자신의 방향의 우선순위 각각에 대해서
      for (i = 0; sel_d < 0 && i < 4; ++i) {
        // 우선순위에 따라, 바라볼 방향과 그 좌표
        mov_d = dirs[i];
        mov_x = MOVED_X(mov_d, x);
        mov_y = MOVED_Y(mov_d, y);
        // 변두리가 아니고, 자신의 냄새인 경우
        if (mov_x >= 0 && mov_x < N &&
            mov_y >= 0 && mov_y < N &&
            smell_who[mov_x][mov_y] == m) {
          // 이동 예정 좌표기록 (x,y)
          sel_x = mov_x;
          sel_y = mov_y;
          sel_d = mov_d;
        }
      }
      // 이동할 좌표로 이동
      shark[m][STATE][SHARK_X] = sel_x;
      shark[m][STATE][SHARK_Y] = sel_y;
      shark[m][STATE][SHARK_DIRECT] = sel_d;
    }

    // 3. 시간 지남
    cur_time++;
  }

  // 정답 출력
  if (cur_time > 1000) cur_time = -1;
  printf("%d", cur_time);
  return 0;
}
