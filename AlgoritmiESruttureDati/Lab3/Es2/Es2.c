#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "brani.txt"
#define MAX_SONG_NAME_LENGTH 256
#define MAX_SONGS 5

typedef struct Song song;
typedef struct Person person;

struct Song{
    char name[MAX_SONG_NAME_LENGTH];
};

struct Person{
    song *songs;
    int songN;
};

int readFile(FILE *fin, person **p);
void freePerson(person *p, int n);
int princ_molt(int pos, person *p, int *sol, int n, int cnt);

int main(int argc, char *argv[]){
    FILE *fin = fopen(FILENAME, "r");
    person *p;
    int n, *sol, cnt = 0;

    n = readFile(fin, &p);

    if(n == -1){
        printf("Impossibile aprire il file \"%s\".", FILENAME);
        return -1;
    }

    sol = (int*)malloc(n * sizeof(int));

    cnt = princ_molt(0, p, sol, n, cnt);
    printf("Soluzioni totali: %d", cnt);

    free(sol);
    freePerson(p, n);

    return 0;
}

int readFile(FILE *fin, person **p){
    char songName[MAX_SONG_NAME_LENGTH];
    int n, sn;

    if(fin == NULL)
        return -1;

    fscanf(fin, "%d", &n);
    *p = (person*)malloc(n * sizeof(person));

    for(int i = 0; i < n; i++){
        fscanf(fin, "%d", &sn);
        (*p)[i].songN = sn;
        if(sn > MAX_SONG_NAME_LENGTH) sn = MAX_SONG_NAME_LENGTH;
        (*p)[i].songs = (song*)malloc(sn * sizeof(song));

        for(int j = 0; j < sn; j++){
            fscanf(fin, " %s ", &songName);
            strcpy((*p)[i].songs[j].name, songName);
        }
    }

    return n;
}

void freePerson(person *p, int n){
    for(int i = 0; i < n; i++)
        free(p[i].songs);
    
    free(p);
}

int princ_molt(int pos, person *p, int *sol, int n, int cnt){
    int i;
    if(pos >= n){
        for(i = 0; i < n; i++)
            printf("%d -> %s ", sol[i] + 1, p[i].songs[sol[i]].name);
        printf("\n\n");
        return cnt + 1;
    }

    for(i = 0; i < p[pos].songN; i++){
        sol[pos] = i;
        cnt = princ_molt(pos + 1, p, sol, n, cnt);
    }

    return cnt;
}
