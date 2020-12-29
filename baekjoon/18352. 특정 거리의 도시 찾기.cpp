#include <stdio.h>

typedef struct _Neighbor {
    int id;
    struct _Neighbor* next = NULL;
} Neighbor;

typedef struct _Node {
    int dist = 333333;
    struct _Neighbor* neighbor = NULL;
} Node;

Node node[300001];
Neighbor neighbor[1000000];
int queue_step[300000];
int queue_from[300000];
int queue_cnt = 0;
int N, M, K, X;

void search(int step, int from) {
    if (step > K) return;

    Neighbor* nb = node[from].neighbor;
    while(nb) {
        if (node[nb->id].dist > step) {
            node[nb->id].dist = step;
            
            queue_step[queue_cnt] = step + 1;
            queue_from[queue_cnt] = nb->id;
            queue_cnt++;
        }
        nb = nb->next;
    }
}

int main(int argc, char* argv[]) {

    scanf("%d %d %d %d", &N, &M, &K, &X);
    for (int i=0; i<M; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);

        neighbor[i].id = b;

        if (node[a].neighbor) {
            Neighbor* p = node[a].neighbor;
            while (p->next) p = p->next;
            p->next = &neighbor[i];
        } else {
            node[a].neighbor = &neighbor[i];
        }
    }

    node[X].dist = 0;
    search(1, X);
    for (int i=0; i<queue_cnt; ++i) {
        search(queue_step[i], queue_from[i]);
    }

    bool exist = false;
    for (int i=1; i<=N; ++i) {
        if (node[i].dist == K) {
            printf("%d\n", i);
            exist = true;
        }
    }
    if (!exist) printf("-1\n");

    return 0;
}
