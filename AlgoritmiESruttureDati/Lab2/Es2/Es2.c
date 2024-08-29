#include <stdio.h>
#include <stdlib.h>

#define FILENAME "mat.txt"

void print(int **datas, int nr, int nc);
int malloc2dP(FILE *fin, int ***datas, int *nr, int *nc);
void free2d(int **m, int nr);

void separa(int **mat, int nr, int nc, int **vw, int **vb, int *wTile, int *bTile);
void printVector(int *v, int n);

int main(int argc, char * argv[]){
    FILE *fin = fopen(FILENAME, "r");
    int **datas, *vw, *vb, nr, nc, wTile, bTile;

    if(malloc2dP(fin, &datas, &nr, &nc) == -1){
        printf("Impossibile aprire il file \"%s\"", FILENAME);
        return -1;
    }
    fclose(fin);

    print(datas, nr, nc);

    separa(datas, nr, nc, &vw, &vb, &wTile, &bTile);
    printf("Celle bianche: \n");
    printVector(vw, wTile);
    printf("\n\nCelle nere: \n");
    printVector(vb, bTile);

    free2d(datas, nr);

    return 0;
}

void print(int **datas, int nr, int nc){
    for(int i = 0; i < nr; i++){
        for(int j = 0; j < nc; j++)
            printf("%d ", datas[i][j]);
        printf("\n");
    }
}

int malloc2dP(FILE *fin, int ***datas, int *nr, int *nc){
    int **m;

    if(fin == NULL)
        return -1;

    fscanf(fin, "%d %d", nr, nc);
    
    printf("%d %d\n", *nr, *nc);

    m = (int**)malloc((*nr) * sizeof(int*));
    if(m == NULL) return -1;

    for(int i = 0; i < *nr; i++){
        m[i] = (int*)malloc((*nc) * sizeof(int)); 
        if(m[i] == NULL) return -1;
        for(int j = 0; j < *nc; j++)
            fscanf(fin, "%d", &m[i][j]);
    }

    *datas = m;
    return (*nr)*(*nc);
}

void free2d(int **m, int nr){
    for(int i = 0; i < nr; i++){
        free(m[i]);
    }
    free(m);
}

void separa(int **mat, int nr, int nc, int **vw, int **vb, int *wTile, int *bTile){
    int  wCounter, bCounter,*v1, *v2;
    
    if((nr * nc) % 2 == 0){
        *wTile = (nr*nc)/2; *bTile = (nr*nc)/2;
    }else{
        *wTile = ((nr*nc)/2) + 1; *bTile = (nr*nc)/2;
    }

    v1 = (int*)malloc((*wTile) * sizeof(int));
    v2 = (int*)malloc((*bTile) * sizeof(int));

    wCounter = 0; bCounter = 0;
    for(int i = 0; i < nr; i++){
        for(int j = 0; j < nc; j++){
            if((i + j) % 2 == 0){
                v1[wCounter] = mat[i][j];
                wCounter++;
            }else{
                v2[bCounter] = mat[i][j];
                bCounter++;
            }
        }
    }

    *vw = v1;
    *vb = v2;
}

void printVector(int *v, int n){
    for(int i = 0; i < n; i++)
        printf("%d ", v[i]);
}
