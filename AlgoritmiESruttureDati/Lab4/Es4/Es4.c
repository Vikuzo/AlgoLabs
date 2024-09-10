#include <stdio.h>
#include <stdlib.h>

typedef struct Necklace necklace;
typedef struct Item item;

struct Necklace{
    int val[4];
    int worth[4];
};

struct Item{
    necklace n;
    int max;
};

char convStone(int val);
int checkSol(int *sol, int i, int *counter, item *val);

int disp_rip(int pos, item *val, int *sol, int n, int k, int cnt, int *counter);

int main(int argc, char *argv[]){
    necklace n;
    item i;
    int *sol, counter[4];

    printf("Inserire il numero totale di gemme di cui e' composta la collana: ");
    scanf("%d",  &i.max);
    printf("Inserire il numero massimo di gemme di ogni tipo: ");
    scanf("%d %d %d %d", &n.val[0], &n.val[1], &n.val[2], &n.val[3]);
    printf("Inserire il costo per le singole pietre: ");
    scanf("%d %d %d %d", &n.worth[0], &n.worth[1], &n.worth[2], &n.worth[3]);

    sol = (int*)malloc((i.max) * sizeof(int));
    i.n = n;
    for(int j = 0; j < 4; counter[j] = 0, j++);

    disp_rip(0, &i, sol, 4, i.max, 0, counter);

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

int checkSol(int *sol, int i, int *counter, item *val){
    int flag = -1;

    if(i < 1)
        return 0;

    if(sol[i-1] == 0 && (sol[i] == 0 || sol[i] == 1))
        flag = 0;
    else if(sol[i-1] == 1 && (sol[i] == 3 || sol[i] == 2))
        flag = 0;
    else if(sol[i-1] == 2 && (sol[i] == 0 || sol[i] == 1))
        flag = 0;
    else if(sol[i-1] == 3 && (sol[i] == 3 || sol[i] == 2))
        flag = 0;

    if(counter[sol[i]] > val->n.val[sol[i]])
        flag = -1;

    return flag;
}

int disp_rip(int pos, item *val, int *sol, int n, int k, int cnt, int *counter){
    int i;
    if(pos >= k){
        if(counter[0] <= counter[3]){
            for(i = 0; i < k; i++)
                printf("%c ", convStone(sol[i]));
            printf("\n");
            return cnt + 1;
        }

        return cnt;
    }

    for(i = 0; i < n; i++){
        sol[pos] = i;
        counter[i]++;

        if(checkSol(sol, pos, counter, val) == 0){
            cnt = disp_rip(pos + 1, val, sol, n, k, cnt, counter);
            counter[i]--;
        }else counter[i]--;
    }
    return cnt;
}