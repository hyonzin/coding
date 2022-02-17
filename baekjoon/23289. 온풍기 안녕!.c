// https://www.acmicpc.net/problem/23289
#include <stdio.h>
#include <string.h>

int R, C, K;

int n_heater = 0;
int heaters_r[400];
int heaters_c[400];
int heaters_d[400];

int n_check = 0;
int checks_r[400];
int checks_c[400];

int W;
int walls[20][20] = {0, };

unsigned int heater[20][20] = {0, };
unsigned int heater_delta[20][20] = {0, };

unsigned int tem[20][20] = {0, };
int tem_delta[20][20] = {0, };

unsigned int n_chocolate = 0;


void heat(int d, int val, int r, int c) {
  if( heater_delta[r][c] > 0 ) {
    return;
  }

  heater_delta[r][c] = val;

  if( val == 1 ) {
    return;
  }

  heater_delta[r][c] = val;
  if( d == 1 ) {
    if( !(walls[r][c] & 1) ) {
      heat(d, val-1, r, c+1);
    }
    if( !(walls[r][c] & 4) && !(walls[r-1][c] & 1) ) {
      heat(d, val-1, r-1, c+1);
    }
    if( !(walls[r][c] & 8) && !(walls[r+1][c] & 1) ) {
      heat(d, val-1, r+1, c+1);
    }
  }
  else if( d == 2 ) {
    if( !(walls[r][c] & 2) ) {
      heat(d, val-1, r, c-1);
    }
    if( !(walls[r][c] & 4) && !(walls[r-1][c] & 2) ) {
      heat(d, val-1, r-1, c-1);
    }
    if( !(walls[r][c] & 8) && !(walls[r+1][c] & 2) ) {
      heat(d, val-1, r+1, c-1);
    }
  }
  else if( d == 3 ) {
    if( !(walls[r][c] & 4) ) {
      heat(d, val-1, r-1, c);
    }
    if( !(walls[r][c] & 2) && !(walls[r][c-1] & 4) ) {
      heat(d, val-1, r-1, c-1);
    }
    if( !(walls[r][c] & 1) && !(walls[r][c+1] & 4) ) {
      heat(d, val-1, r-1, c+1);
    }
  }
  else if( d == 4 ) {
    if( !(walls[r][c] & 8) ) {
      heat(d, val-1, r+1, c);
    }
    if( !(walls[r][c] & 2) && !(walls[r][c-1] & 8) ) {
      heat(d, val-1, r+1, c-1);
    }
    if( !(walls[r][c] & 1) && !(walls[r][c+1] & 8) ) {
      heat(d, val-1, r+1, c+1);
    }
  }
}

int main(int argc, char* argv[]) {
  int r, c;
  unsigned int h, d;
  int i, val;
  int is_done;

  // FILE* fp = fopen("input1.txt", "r");
  FILE* fp = stdin;

  // read heaters or point to check
  fscanf(fp, "%d %d %d", &R, &C, &K);
  for( r = 0; r < R; ++r ){
    for( c = 0; c < C; ++c ){
      fscanf(fp, "%d", &val);
      if ( val >= 1 && val <= 4 ) {
        heaters_r[n_heater] = r;
        heaters_c[n_heater] = c;
        heaters_d[n_heater] = val;
        n_heater++;
      }else if( val == 5 ){
        checks_r[n_check] = r;
        checks_c[n_check] = c;
        n_check++;
      }
    }
  }

  // read wall
  fscanf(fp, "%d", &W);
  for( i = 0; i < W; ++i ){
    fscanf(fp, "%d %d %d", &r, &c, &val);
    r--;
    c--;
    if( val == 0 ){
      walls[r][c] |= 4;
      walls[r-1][c] |= 8;
    } else if( val == 1 ){
      walls[r][c] |= 1;
      walls[r][c+1] |= 2;
    }
  }
  fclose(fp);

  // border's wall
  for( r = 0; r < R; ++r ){
    walls[r][0] |= 2;
    walls[r][C-1] |= 1;
  }
  for( c = 0; c < C; ++c ){
    walls[0][c] |= 4;
    walls[R-1][c] |= 8;
  }

  // set heaters
  for( h = 0; h < n_heater; ++h ) {
    d = heaters_d[h];
    r = heaters_r[h];
    c = heaters_c[h];

    memset(heater_delta, 0, 20*20*sizeof(unsigned int));
    if     ( d == 1 ) heat(d, 5, r, c+1);
    else if( d == 2 ) heat(d, 5, r, c-1);
    else if( d == 3 ) heat(d, 5, r-1, c);
    else if( d == 4 ) heat(d, 5, r+1, c);

    for( r = 0; r < R; ++r ){
      for( c = 0; c < C; ++c ){
        heater[r][c] += heater_delta[r][c];
      }
    }
  }

  //main loop
  while( 1 ){
    // 1
    for( r = 0; r < R; ++r ){
      for( c = 0; c < C; ++c ){
        tem[r][c] += heater[r][c];
      }
    }

    // 2
    memset(tem_delta, 0, 20*20*sizeof(unsigned int));
    for( r = 0; r < R; ++r ){
      for( c = 0; c < C; ++c ){
        if( !(walls[r][c] & 1) && (tem[r][c] > tem[r][c+1]) ) {
          d = (tem[r][c] - tem[r][c+1]) / 4;
          tem_delta[r][c] -= d;
          tem_delta[r][c+1] += d;

        }
        if( !(walls[r][c] & 2) && (tem[r][c] > tem[r][c-1]) ) {
          d = (tem[r][c] - tem[r][c-1]) / 4;
          tem_delta[r][c] -= d;
          tem_delta[r][c-1] += d;

        }
        if( !(walls[r][c] & 4) && (tem[r][c] > tem[r-1][c]) ) {
          d = (tem[r][c] - tem[r-1][c]) / 4;
          tem_delta[r][c] -= d;
          tem_delta[r-1][c] += d;

        }
        if( !(walls[r][c] & 8) && (tem[r][c] > tem[r+1][c]) ) {
          d = (tem[r][c] - tem[r+1][c]) / 4;
          tem_delta[r][c] -= d;
          tem_delta[r+1][c] += d;

        }
      }
    }
    for( r = 0; r < R; ++r ){
      for( c = 0; c < C; ++c ){
        tem[r][c] += tem_delta[r][c];
      }
    }

    // 3
    for( r = 0; r < R; ++r ){
      if( tem[r][0] > 0 ) tem[r][0]--;
      if( tem[r][C-1] > 0 ) tem[r][C-1]--;
    }
    for( c = 1; c < C-1; ++c ){
      if( tem[0][c] > 0 ) tem[0][c]--;
      if( tem[R-1][c] > 0 ) tem[R-1][c]--;
    }

    // 4
    n_chocolate++;
    if( n_chocolate == 101 ) break;

    // 5
    is_done = 1;
    for( i = 0; i < n_check; ++i) {
      if( tem[checks_r[i]][checks_c[i]] < K ){
        is_done = 0;
        break;
      }
    }
    if( is_done ) break;
  }

  //Result
  printf("%d", n_chocolate);
  return 0;
}
