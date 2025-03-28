// https://school.programmers.co.kr/learn/courses/30/lessons/389629

#include <stdio.h>

#define K_TOP 0
#define K_BOTTOM 1
#define FROM_NONE 0
#define FROM_UP 1
#define FROM_RIGHT 2
#define FROM_DOWN 3
#define FROM_LEFT 4

#define get_k(i,j,f) (((grid[i][j]==1)==0)?((f==FROM_UP||f==FROM_RIGHT)?K_TOP:K_BOTTOM):((f==FROM_UP||f==FROM_LEFT)?K_TOP:K_BOTTOM))

// N*M <= 200000. 각 칸의 대각선 기준 위/아래 체크여부 기록
int mem[200000][2];

int solution(int** grid, size_t grid_rows, size_t grid_cols) {
    int max_size = 0;
    int session = 1; // 한 칸에서 대각선 기준 위 또는 아래 중 1개만 색칠 가능하므로, 같은 삼각형 덩어리인지 구분하기 위한 변수
    for (int i = 0; i < grid_rows; ++i) {
        for (int j = 0; j < grid_cols; ++j) {
            for (int k = K_TOP; k <= K_BOTTOM; ++k) { // k: 대각선 기준 위(0) 또는 아래(1) 구분
                int size = calc_size(grid, grid_rows, grid_cols, session, i, j, k, FROM_NONE, 0);
                if (size > max_size) {
                    max_size = size;
                }
                session += 1;
            }
        }
    }
    return max_size;
}

int calc_size(int** grid, size_t grid_rows, size_t grid_cols, int session, int i, int j, int k_in, int from, int neighbor) {
    int cur_size = 0;
    int d = grid[i][j] == 1;
    int k = (from == FROM_NONE)?k_in:get_k(i,j,from);
    // 대각선 건너편과 이어진 경우, 해당 칸은 칠하지 못함
    if (mem[i*grid_cols + j][1 - k] == session) {
        return 0;
    }
    // 이미 온 적 있는 칸이면 칠하지 않음
    if (mem[i*grid_cols + j][k] != 0) {
        // 단, 대각선 건너편과 이어진 것 때문에 칠하지 못했던 칸이라면, 이번엔 건너편은 칠하지 않고 이번 칸을 칠함
        if (mem[i*grid_cols + j][k] == neighbor) {
            // pass
        } else {
            return 0;
        }
    }
    // 이번 칸을 칠함
    mem[i*grid_cols + j][k] = session;
    cur_size = 1;
    // 상하좌우로 이어진 다음 칸 체크
    if (d == 0) { // 대각선: \.
        if (k == K_TOP) {
            // 위, 오른쪽
            if (i > 0 && (from != FROM_UP)) {
                // 이번칸의 대각선 건너편 색 == 다음칸 색이라면, 그 색은 덧칠해서 연결함
                if (mem[(i-1)*grid_cols + j][get_k(i-1,j,FROM_DOWN)] == mem[i*grid_cols + j][1 - k]) {
                    neighbor = mem[i*grid_cols + j][1 - k];
                }
                cur_size += calc_size(grid, grid_rows, grid_cols, session, i-1, j, NULL, FROM_DOWN, neighbor);
            }
            if (j < grid_cols - 1 && (from != FROM_RIGHT)) {
                // 이번칸의 대각선 건너편 색 == 다음칸 색이라면, 그 색은 덧칠해서 연결함
                if (mem[i*grid_cols + (j+1)][get_k(i,j+1,FROM_LEFT)] == mem[i*grid_cols + j][1 - k]) {
                    neighbor = mem[i*grid_cols + j][1 - k];
                }
                cur_size += calc_size(grid, grid_rows, grid_cols, session, i, j+1, NULL, FROM_LEFT, neighbor);
            }
            
        } else {
            // 아래, 왼쪽
            if (i < grid_rows - 1 && (from != FROM_DOWN)) {
                // 이번칸의 대각선 건너편 색 == 다음칸 색이라면, 그 색은 덧칠해서 연결함
                if (mem[(i+1)*grid_cols + j][get_k(i+1,j,FROM_UP)] == mem[i*grid_cols + j][1 - k]) {
                    neighbor = mem[i*grid_cols + j][1 - k];
                }
                cur_size += calc_size(grid, grid_rows, grid_cols, session, i+1, j, NULL, FROM_UP, neighbor);
            }
            if (j > 0 && (from != FROM_LEFT)) {
                // 이번칸의 대각선 건너편 색 == 다음칸 색이라면, 그 색은 덧칠해서 연결함
                if (mem[i*grid_cols + (j-1)][get_k(i,j-1,FROM_RIGHT)] == mem[i*grid_cols + j][1 - k]) {
                    neighbor = mem[i*grid_cols + j][1 - k];
                }
                cur_size += calc_size(grid, grid_rows, grid_cols, session, i, j-1, NULL, FROM_RIGHT, neighbor);
            }
        }
    } else { // 대각선: /
        if (k == K_TOP) {
            // 위, 왼쪽
            if (i > 0 && (from != FROM_UP)) {
                // 이번칸의 대각선 건너편 색 == 다음칸 색이라면, 그 색은 덧칠해서 연결함
                if (mem[(i-1)*grid_cols + j][get_k(i-1,j,FROM_DOWN)] == mem[i*grid_cols + j][1 - k]) {
                    neighbor = mem[i*grid_cols + j][1 - k];
                }
                cur_size += calc_size(grid, grid_rows, grid_cols, session, i-1, j, NULL, FROM_DOWN, neighbor);
            }
            if (j > 0 && (from != FROM_LEFT)) {
                // 이번칸의 대각선 건너편 색 == 다음칸 색이라면, 그 색은 덧칠해서 연결함
                if (mem[i*grid_cols + (j-1)][get_k(i,j-1,FROM_RIGHT)] == mem[i*grid_cols + j][1 - k]) {
                    neighbor = mem[i*grid_cols + j][1 - k];
                }
                cur_size += calc_size(grid, grid_rows, grid_cols, session, i, j-1, NULL, FROM_RIGHT, neighbor);
            }
        }
        else {
            // 아래, 오른쪽
            if (i < grid_rows - 1 && (from != FROM_DOWN)) {
                // 이번칸의 대각선 건너편 색 == 다음칸 색이라면, 그 색은 덧칠해서 연결함
                if (mem[(i+1)*grid_cols + j][get_k(i+1,j,FROM_UP)] == mem[i*grid_cols + j][1 - k]) {
                    neighbor = mem[i*grid_cols + j][1 - k];
                }
                cur_size += calc_size(grid, grid_rows, grid_cols, session, i+1, j, NULL, FROM_UP, neighbor);
            }
            if (j < grid_cols - 1 && (from != FROM_RIGHT)) {
                // 이번칸의 대각선 건너편 색 == 다음칸 색이라면, 그 색은 덧칠해서 연결함
                if (mem[i*grid_cols + (j+1)][get_k(i,j+1,FROM_LEFT)] == mem[i*grid_cols + j][1 - k]) {
                    neighbor = mem[i*grid_cols + j][1 - k];
                }
                cur_size += calc_size(grid, grid_rows, grid_cols, session, i, j+1, NULL, FROM_LEFT, neighbor);
            }
        }
    }
    return cur_size;
}
