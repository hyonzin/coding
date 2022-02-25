#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEATER_RIGHT 1
#define HEATER_LEFT  2
#define HEATER_UP    3
#define HEATER_DOWN  4

#define WALL_RIGHT 1
#define WALL_LEFT  2
#define WALL_UP    4
#define WALL_DOWN  8

#define IDX(r, c) ((r)*C + (c))

int R, C, K;

int n_heater = 0;
unsigned char* heaters_r;
unsigned char* heaters_c;
unsigned char* heaters_d;

int n_check = 0;
unsigned char* checks_r;
unsigned char* checks_c;

int W;
unsigned char* walls;

unsigned char* heater;
unsigned char* heater_updated;

unsigned short* tem;
int* tem_delta;

int n_chocolate = 0;


void heat(int d, int val, int r, int c) {
  heater[IDX(r, c)] += val;
  heater_updated[IDX(r, c)] = 1;

  if( val == 1 ) {
    return;
  }

  if( d == HEATER_RIGHT ) {
    if( !(walls[IDX(r, c)] & WALL_RIGHT) && !heater_updated[IDX(r, c+1)] ) {
      heat(d, val-1, r, c+1);
    }
    if( !(walls[IDX(r, c)] & WALL_UP) && !(walls[IDX(r-1, c)] & WALL_RIGHT) && !heater_updated[IDX(r-1, c+1)] ) {
      heat(d, val-1, r-1, c+1);
    }
    if( !(walls[IDX(r, c)] & WALL_DOWN) && !(walls[IDX(r+1, c)] & WALL_RIGHT) && !heater_updated[IDX(r+1, c+1)] ) {
      heat(d, val-1, r+1, c+1);
    }
  }
  else if( d == HEATER_LEFT ) {
    if( !(walls[IDX(r, c)] & WALL_LEFT) && !heater_updated[IDX(r, c-1)]) {
      heat(d, val-1, r, c-1);
    }
    if( !(walls[IDX(r, c)] & WALL_UP) && !(walls[IDX(r-1, c)] & WALL_LEFT) && !heater_updated[IDX(r-1, c-1)] ) {
      heat(d, val-1, r-1, c-1);
    }
    if( !(walls[IDX(r, c)] & WALL_DOWN) && !(walls[IDX(r+1, c)] & WALL_LEFT) && !heater_updated[IDX(r+1, c-1)] ) {
      heat(d, val-1, r+1, c-1);
    }
  }
  else if( d == HEATER_UP ) {
    if( !(walls[IDX(r, c)] & WALL_UP) && !heater_updated[IDX(r-1, c)] ) {
      heat(d, val-1, r-1, c);
    }
    if( !(walls[IDX(r, c)] & WALL_LEFT) && !(walls[IDX(r, c-1)] & WALL_UP) && !heater_updated[IDX(r-1, c-1)] ) {
      heat(d, val-1, r-1, c-1);
    }
    if( !(walls[IDX(r, c)] & WALL_RIGHT) && !(walls[IDX(r, c+1)] & WALL_UP) && !heater_updated[IDX(r-1, c+1)] ) {
      heat(d, val-1, r-1, c+1);
    }
  }
  else if( d == HEATER_DOWN ) {
    if( !(walls[IDX(r, c)] & WALL_DOWN) && !heater_updated[IDX(r+1, c)] ) {
      heat(d, val-1, r+1, c);
    }
    if( !(walls[IDX(r, c)] & WALL_LEFT) && !(walls[IDX(r, c-1)] & WALL_DOWN) && !heater_updated[IDX(r+1, c-1)] ) {
      heat(d, val-1, r+1, c-1);
    }
    if( !(walls[IDX(r, c)] & WALL_RIGHT) && !(walls[IDX(r, c+1)] & WALL_DOWN) && !heater_updated[IDX(r+1, c+1)] ) {
      heat(d, val-1, r+1, c+1);
    }
  }
}

int main(int argc, char* argv[]) {
  int r, c;
  unsigned int h, d;
  int i, val;
  int is_done;

  // FILE* fp = fopen("input.txt", "r");
  FILE* fp = stdin;

  // read heaters or point to check
  fscanf(fp, "%d %d %d", &R, &C, &K);

  heaters_r = (unsigned char*) malloc(R * C * sizeof(unsigned char));
  heaters_c = (unsigned char*) malloc(R * C * sizeof(unsigned char));
  heaters_d = (unsigned char*) malloc(R * C * sizeof(unsigned char));

  checks_r = (unsigned char*) malloc(R * C * sizeof(unsigned char));
  checks_c = (unsigned char*) malloc(R * C * sizeof(unsigned char));

  walls = (unsigned char*) calloc(R * C, sizeof(unsigned char));
  heater = (unsigned char*) calloc(R * C, sizeof(unsigned char));
  heater_updated = (unsigned char*) malloc(R * C * sizeof(unsigned char));

  tem = (unsigned short*) calloc(R * C, sizeof(unsigned short));
  tem_delta = (int*) malloc(R * C * sizeof(int));

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
      walls[IDX(r,   c)] |= 4;
      walls[IDX(r-1, c)] |= 8;
    } else if( val == 1 ){
      walls[IDX(r, c  )] |= 1;
      walls[IDX(r, c+1)] |= 2;
    }
  }

  // border's wall
  for( r = 0; r < R; ++r ){
    walls[IDX(r, 0  )] |= 2;
    walls[IDX(r, C-1)] |= 1;
  }
  for( c = 0; c < C; ++c ){
    walls[IDX(0,   c)] |= 4;
    walls[IDX(R-1, c)] |= 8;
  }

  // set heaters
  for( h = 0; h < n_heater; ++h ) {
    d = heaters_d[h];
    r = heaters_r[h];
    c = heaters_c[h];

    memset(heater_updated, 0, R * C * sizeof(unsigned char));
    if     ( d == 1 ) heat(d, 5, r,   c+1);
    else if( d == 2 ) heat(d, 5, r,   c-1);
    else if( d == 3 ) heat(d, 5, r-1, c  );
    else if( d == 4 ) heat(d, 5, r+1, c  );
  }

  //main loop
  while( 1 ){
    // 1
    for( r = 0; r < R; ++r ){
      for( c = 0; c < C; ++c ){
        tem[IDX(r, c)] += heater[IDX(r, c)];
      }
    }

    // 2
    memset(tem_delta, 0, R * C * sizeof(unsigned int));
    for( r = 0; r < R; ++r ){
      for( c = 0; c < C; ++c ){
        if( !(walls[IDX(r, c)] & 1) && (tem[IDX(r, c)] > tem[IDX(r, c+1)]) ) {
          d = (tem[IDX(r, c)] - tem[IDX(r, c+1)]) / 4;
          tem_delta[IDX(r, c)] -= d;
          tem_delta[IDX(r, c+1)] += d;

        }
        if( !(walls[IDX(r, c)] & 2) && (tem[IDX(r, c)] > tem[IDX(r, c-1)]) ) {
          d = (tem[IDX(r, c)] - tem[IDX(r, c-1)]) / 4;
          tem_delta[IDX(r, c)] -= d;
          tem_delta[IDX(r, c-1)] += d;

        }
        if( !(walls[IDX(r, c)] & 4) && (tem[IDX(r, c)] > tem[IDX(r-1, c)]) ) {
          d = (tem[IDX(r, c)] - tem[IDX(r-1, c)]) / 4;
          tem_delta[IDX(r, c)] -= d;
          tem_delta[IDX(r-1, c)] += d;

        }
        if( !(walls[IDX(r, c)] & 8) && (tem[IDX(r, c)] > tem[IDX(r+1, c)]) ) {
          d = (tem[IDX(r, c)] - tem[IDX(r+1, c)]) / 4;
          tem_delta[IDX(r, c)] -= d;
          tem_delta[IDX(r+1, c)] += d;

        }
      }
    }
    for( r = 0; r < R; ++r ){
      for( c = 0; c < C; ++c ){
        tem[IDX(r, c)] += tem_delta[IDX(r, c)];
      }
    }

    // 3
    for( r = 0; r < R; ++r ){
      if( tem[IDX(r, 0  )] > 0 ) tem[IDX(r, 0  )]--;
      if( tem[IDX(r, C-1)] > 0 ) tem[IDX(r, C-1)]--;
    }
    for( c = 1; c < C-1; ++c ){
      if( tem[IDX(0,   c)] > 0 ) tem[IDX(0,   c)]--;
      if( tem[IDX(R-1, c)] > 0 ) tem[IDX(R-1, c)]--;
    }

    // 4
    n_chocolate++;
    if( n_chocolate == 101 ) break;

    // 5
    is_done = 1;
    for( i = 0; i < n_check; ++i) {
      if( tem[IDX(checks_r[i], checks_c[i])] < K ){
        is_done = 0;
        break;
      }
    }
    if( is_done ) break;
  }

  //Result
  printf("%d", n_chocolate);

  //Free
  free(heaters_r);
  free(heaters_c);
  free(heaters_d);

  free(checks_r);
  free(checks_c);

  free(walls);
  free(heater);
  free(heater_updated);

  free(tem);
  free(tem_delta);

  fclose(fp);

  return 0;
}
