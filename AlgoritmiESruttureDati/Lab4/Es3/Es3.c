#include <stdio.h>
#include <stdlib.h>

typedef struct Necklace necklace;
typedef struct Item item;

struct Necklace{
    int z, r, t, s;
};

struct Item{
    necklace n;
    int max;
};

char convStone(int val);
int checkSol(int *sol, int i);

int disp_rip(int pos, item *val, int *sol, int n, int k, int cnt);

int main(int argc, char *argv[]){
    necklace n;
    item i;
    int *sol;

    printf("Inserire il numero totale di gemme di cui e' composta la collana: ");
    scanf("%d",  &i.max);

    sol = (int*)malloc((i.max) * sizeof(int));
    i.n = n;

    disp_rip(0, &i, sol, 4, i.max, 0);

    free(sol);

    return 0;
}

char convStone(int val){
    switch (val){
    case 0:
        return 'z';
    case 1:
        return 'r';
    case 2:
        return 't';
    case 3:
        return 's';
    default:
        return '!';
    }
}

int checkSol(int *sol, int i){
    if(i < 1)
        return 0;

    if(sol[i-1] == 0 && (sol[i] == 0 || sol[i] == 1))
        return 0;
    if(sol[i-1] == 1 && (sol[i] == 3 || sol[i] == 2))
        return 0;
    if(sol[i-1] == 2 && (sol[i] == 0 || sol[i] == 1))
        return 0;
    if(sol[i-1] == 3 && (sol[i] == 3 || sol[i] == 2))
        return 0;

    return -1;
}

int disp_rip(int pos, item *val, int *sol, int n, int k, int cnt){
    int i;
    if(pos >= k){
        for(i = 0; i < k; i++)
            printf("%c ", convStone(sol[i]));
        printf("\n");
        return cnt + 1;
    }

    for(i = 0; i < n; i++){
        sol[pos] = i;
        if(checkSol(sol, pos) == 0)
            cnt = disp_rip(pos + 1, val, sol, n, k, cnt);
    }
    return cnt;
}
