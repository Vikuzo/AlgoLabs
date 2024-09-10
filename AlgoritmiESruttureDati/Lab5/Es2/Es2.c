#include <stdio.h>
#include <stdlib.h>

#define TILES_FILENAME "tiles.txt"
#define BOARD_FILENAME "board.txt"

typedef struct Tube tube;
typedef struct Tile tile;
typedef struct Board board;

struct Tube{
    char color;
    int val;
};

struct Tile{
    tube or, vr;
    int rot;
};

struct Board{
    int *tiles, *rots;
};

int readTilesFile(FILE *fin, tile **tiles);
int readBoardFile(FILE *fin, board *b, int *nr, int *nc);
int perm(int pos, board *origConf, int *sol, int *mark, int n, int cnt);

int main(int argc, char *argv[]){
    FILE *fin = fopen(TILES_FILENAME, "r");
    tile *tiles;
    board b;
    int n, nc, nr, *sol, *mark;

    n = readTilesFile(fin, &tiles);
    if(n == -1){
        printf("Impossibile aprire il file \"%s\"", TILES_FILENAME);
        return -1;
    }
    fclose(fin);

    fin = fopen(BOARD_FILENAME, "r");
    if(readBoardFile(fin, &b, &nr, &nc) == -1){
        printf("Impossibile aprire il file \"%s\"", BOARD_FILENAME);
        return -1;
    }
    fclose(fin);

    sol = (int*)malloc((nr * nc) * sizeof(int));
    mark = (int*)malloc((nr * nc) * sizeof(int));
    for(int i = 0; i < (nr * nc); i++){
        mark[i] = 0;
    }

    // printf("%d", nr * nc);
    perm(0, &b, sol, mark, nr * nc, 0);

    free(sol);
    free(mark);
    free(tiles);
    free(b.tiles); free(b.rots);

    return 0;
}

int readTilesFile(FILE *fin, tile **tiles){
    int n = 0;

    if(fin == NULL)
        return -1;

    fscanf(fin, "%d", &n);
    *tiles = (tile*)malloc(n * sizeof(tile));

    for(int i = 0; i < n; i++)
        fscanf(fin, " %c %d %c %d", &((*tiles)[i].or.color), &((*tiles)[i].or.val), &((*tiles)[i].vr.color), &((*tiles)[i].vr.val));

    return n;
}

int readBoardFile(FILE *fin, board *b, int *nr, int *nc){
    if(fin == NULL)
        return -1;

    fscanf(fin, "%d %d", nr, nc);
    b->tiles = (int*)malloc((*nr) * (*nc) * sizeof(int));
    b->rots = (int*)malloc((*nr) * (*nc) * sizeof(int));

    for(int i = 0; i < *nr; i++){
        for(int j = 0; j < *nc; j++)
            fscanf(fin, "%d/%d", &(b->tiles[(i * (*nc))+j]), &(b->rots[(i * (*nc))+j]));
    }

    return (*nr) * (*nc);
}

int perm(int pos, board *origConf, int *sol, int *mark, int n, int cnt){
    int i;
    if(pos >= n){
        for(i = 0; i < n; i++)
            printf("%d ", sol[i]);
        printf("\n");
        return cnt + 1;
    }

    for(i = 0; i < n; i++){
        if(mark[i] == 0){
            mark[i] = 1;
            sol[pos] = i;
            cnt = perm(pos + 1, origConf, sol, mark, n, cnt);
            mark[i] = 0;
        }
    }

    return cnt;
}
