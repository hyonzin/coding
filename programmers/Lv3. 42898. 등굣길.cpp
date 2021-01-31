// https://programmers.co.kr/learn/courses/30/lessons/42898
#include <string>
#include <vector>

using namespace std;

int way[101][101] = {0, }; // x,y
char obt[101][101] = {0, }; // x,y

int solution(int m, int n, vector<vector<int>> puddles) {
    int x, y;
    
    for (int i=0; i<puddles.size(); ++i) {
        obt[puddles[i][0]][puddles[i][1]] = 1;
    }
    
    for (x=m; x>0; --x) {
        if (obt[x][n]) break;
        way[x][n] = 1;
    }
    for (y=n; y>0; --y) {
        if (obt[m][y]) break;
        way[m][y] = 1;
    }
    
    for (y=n-1; y>0; --y) {
        for (x=m-1; x>0; --x) {
            if (!obt[x][y]) {
                if (!obt[x+1][y]) way[x][y] += way[x+1][y];
                if (!obt[x][y+1]) way[x][y] += way[x][y+1];
                if (way[x][y] >= 1000000007) way[x][y] -= 1000000007;
            }
        }
    }
    
    return way[1][1];
}
