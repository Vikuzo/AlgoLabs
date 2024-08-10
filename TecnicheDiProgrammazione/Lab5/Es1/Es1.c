/*
In un campionato n (max 20) squadre giocano per m (max 20) giornate. Sia data una matrice di n×m
numeri interi, ognuno dei quali può valere soltanto 0, 1 o 3. Ogni riga della matrice rappresenta i punti
acquisiti dalle n squadre nelle partite disputate nelle m giornate del campionato: 3 punti per le partite
vinte, 1 punto per quelle pareggiate e 0 punti per le sconfitte. I risultati della giornata k-esima sono
contenuti nelle righe della colonna di indice k. Si scriva un programma C che acquisisca i contenuti di
tale matrice da file e che, per ogni giornata del campionato, stampi l'indice (il numero di riga
corrispondente) della squadra capolista. Si definisca un opportuno formato per il file (si fornisce un
esempio di file, il cui formato tuttavia non è obbligatorio).
*/

#include <stdio.h>
#include <limits.h>

#define FILENAME "mat.txt"
#define N 20

void stampa(int matrix[N][N], int nr, int nc);

int main(int argc, char* argv[]){
    FILE *fin = fopen(FILENAME, "r");
    int nr, nc, matrix[N][N], sumPunt[N] = {0}, max;

    if(fin == NULL){
        printf("Impossibile aprire il file \"%s\"");
        return -1;
    }

    fscanf(fin, "%d %d", &nr, &nc);

    while(!feof(fin)){
        for(int i = 0; i < nr && i < N; i++){
            for(int j = 0; j < nc && j < N; j++)
                fscanf(fin, "%d", &matrix[i][j]);
        }
    }

    stampa(matrix, nr, nc);

    for(int j = 0; j < nc; j++){
        max = 0;
        for(int i = 0; i < nr; i++)
            sumPunt[i] += matrix[i][j];
        for(int i = 0; i < nr; i++){
            if(max < sumPunt[i])
                max = i;        
        }

        printf("La squadra con piu' punti alla giornata %d e': %d\n", j, max);
    }

    fclose(fin);
    
    return 0;
}

void stampa(int matrix[N][N], int nr, int nc){
    printf("PUNTEGGI: \n");
    for(int i = 0; i < nr; i++){
        printf("%d -> ", i);
        for(int j = 0; j < nc; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}
