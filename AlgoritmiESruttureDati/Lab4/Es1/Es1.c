#include <stdio.h>
#include <stdlib.h>

#define FILENAME "grafo.txt"

typedef struct Arch arch;
typedef struct Graph graph;

struct Arch{
    int u, v;
};

struct Graph{
    int n, e;
    arch *a;
};

int readFile(FILE *fin, graph *g);
int powerset(int pos, graph *val, int *sol, int n, int start, int cnt);
int checkSol(graph *val, int*sol, int n);
int checkIsInArch(arch e, int i);

int main(int argc, char *argv[]){
    FILE *fin = fopen(FILENAME, "r");
    graph g;
    int *sol;

    readFile(fin, &g);
    sol = (int*)malloc(g.n * sizeof(int));
    powerset(0, &g, sol, g.n, 0, 0);

    free(sol);
    free(g.a);

    return 0;
}

int readFile(FILE *fin, graph *g){
    int n, e, u, v;
    
    if(fin == NULL)
        return -1;

    fscanf(fin, "%d %d", &n, &e);
    g -> n = n;
    g -> e = e;
    g -> a = (arch*)malloc(e * sizeof(arch));

    for(int i = 0; i < e; i++){
        fscanf(fin, "%d %d", &u, &v);
        g -> a[i].u = u;
        g -> a[i].v = v;
    }

    return 0;
}

int powerset(int pos, graph *val, int *sol, int n, int start, int cnt){
    int i;

    if(start >= n){
        if(checkSol(val, sol, pos) == 0){
            for(i = 0; i < pos; i++)
                printf("%d ", sol[i]);
            printf("\n");
            return cnt + 1;
        }
        return cnt;
    }

    for(i = start; i < n; i++){
        sol[pos] = i;
        cnt = powerset(pos + 1, val, sol, n, i + 1, cnt);
    }
    cnt = powerset(pos, val, sol, n, n, cnt);
    return cnt;
}

int checkSol(graph *val, int*sol, int n){
    int i = 0, j = 0;

    while(j < val->e && i < n){
        if(checkIsInArch(val->a[j], sol[i]) == 0){
            j++;
            i = 0;
        }else
            i++;
    }

    if(i == n)
        return -1;
    return 0;
}

int checkIsInArch(arch e, int i){
    if(e.v == i || e.u == i)
        return 0;
    return -1;
}
