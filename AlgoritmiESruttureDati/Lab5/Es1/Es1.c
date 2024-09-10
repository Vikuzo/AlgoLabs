#include <stdio.h>
#include <stdlib.h>

typedef struct Att att;
typedef struct Mark mark;

struct Att{
    int s, f;
};

struct Mark{
    int *sol;
    int n;
    int diff;
};

void attSel(int n, att *v);
int readFile(FILE *fin, att **v);
int powerset(int pos, att *val, int *sol, int n, int start, int cnt, mark *m);
void printAtt(att *v, int i);
int checkSol(att *v, int *sol, int n);
int calcDiff(att *v, int *sol, int n);

int main(int argc, char *argv[]){
    FILE *fin;
    att *v;
    int n;
    char filename[30];

    printf("Inserire il nome del file da cui prendere i dati delle attivita': ");
    scanf("%30s", &filename);
    fin = fopen(filename, "r");

    n = readFile(fin, &v);
    fclose(fin);
    if(n == -1){
        printf("Impossibile aprire il file \"%s\".", filename);
        return -1;
    }
    attSel(n, v);

    free(v);

    return 0;
}

void attSel(int n, att *v){
    mark m;
    int *sol;
    sol = (int*)malloc(n * sizeof(int));
    m.sol = (int *)malloc(n * sizeof(int));
    m.n = 0;
    m.diff = 0;

    powerset(0, v, sol, n, 0, 0, &m);

    printf("Il sottoinsieme che massimizza la somma delle durate e': ");
    for(int i = 0; i < m.n; i++)
        printAtt(v, m.sol[i]);
    printf("con durate: %d", m.diff);

    free(m.sol);
}

int readFile(FILE *fin, att **v){
    int n = 0, s, f;
    
    if(fin == NULL)
        return -1;

    fscanf(fin, "%d", &n);
    *v = (att*)malloc(n * sizeof(att));

    for(int i = 0; i < n; i++){
        fscanf(fin, "%d %d", &s, &f);
        (*v)[i].s = s;
        (*v)[i].f = f;
    }

    return n;
}

int powerset(int pos, att *val, int *sol, int n, int start, int cnt, mark *m){
    int i;
    if(start >= n){
        int diff = calcDiff(val, sol, pos);
        if(checkSol(val, sol, pos) == 0 && m->diff < diff){
            for(i = 0; i < pos; i++)
                m->sol[i] = sol[i];
            m->n = pos; m->diff = diff;
            return cnt + 1;
        }
        return cnt;
    }

    for(i = start; i < n; i++){
        sol[pos] = i;
        cnt = powerset(pos + 1, val, sol, n, i + 1, cnt, m);
    }
    cnt = powerset(pos, val, sol, n, n, cnt, m);
    return cnt;
}

void printAtt(att *v, int i){
    printf("(%d %d) ", v[i].s, v[i].f);
}

int checkSol(att *v, int *sol, int n){
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if(v[sol[i]].s < v[sol[j]].s){
                if(v[sol[j]].s >= v[sol[i]].f){}
                else return -1;
            }else{
                if(v[sol[i]].s >= v[sol[j]].f){}
                else return -1;
            }
        }
    }

    return 0;
}

int calcDiff(att *v, int *sol, int n){
    int diff = 0;
    
    for(int i = 0; i < n; i++)
        diff += v[i].f - v[i].s;

    return diff;
}

