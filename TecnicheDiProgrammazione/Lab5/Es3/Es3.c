/*
Si scriva un programma C che permetta all’utente di eseguire in sequenza operazioni di rotazione di P
posizioni su righe e/o colonne specificate di una matrice di interi. Le rotazioni sono da intendersi come 
circolari sia sulle righe, sia sulle colonne.
Il programma:
• legge da file, il cui nome di al massimo 20 caratteri è acquisito da tastiera, la matrice (max 30 x 30).
Il formato del file prevede sulla prima riga 2 interi che indicano il numero di righe nr e di colonne
nc, seguita da nr righe contenenti ciascuna nc interi
• acquisisce ripetutamente da tastiera una stringa (al massimo di 100 caratteri, contenente eventuali
spazi), nella forma
<selettore> <indice> <direzione> <posizioni>
Il selettore indica se si vuole operare su una riga (“riga”), su una colonna (“colonna”), o
terminare (“fine”). Seguono l’indice della riga (colonna) selezionata, la direzione (“destra”
o “sinistra”, oppure “su” o “giu”) e il numero di posizioni. Dopo ogni comando la matrice
va visualizzata.
*/

#include <stdio.h>
#include <string.h>

#define MAXLENGTHCOMMAND 100
#define MAXN 30
#define MAXLENGTHFILENAME 20

void ruota(int matrix[MAXN][MAXN], int fixed, int N, int P, int dir);
void stampa(int matrix[MAXN][MAXN], int nr, int nc);

int main(int argc, char* argv[]){
    FILE *fin;
    char filename[MAXLENGTHFILENAME], command[MAXLENGTHCOMMAND];
    int nr, nc, matrix[MAXN][MAXN], status = 0;

    printf("Legenda per i comandi di questo programma: \n");
    printf("selettore -> riga (per operare sulle righe), colonna (per operare sulle colonne), fine (per terminare il programma).\n");
    printf("indice -> indice della riga o della colonna su cui si vuole operare.\n");
    printf("direzione -> sinistra o destra (per le righe), su o giu (per le colonne).\n");
    printf("posizioni -> il numero di posizioni su cui effettuare la rotazione.\n\n");

    printf("Inserire il nome del file da cui leggere la matrice: ");
    scanf(" %s", &filename);
    if((fin = fopen(filename, "r")) == NULL){
        printf("Impossibile aprire il file \"%s\".", filename);
        return -1;
    }

    fscanf(fin, "%d %d", &nr, &nc);
    for(int i = 0; i < nr && i < MAXN; i++){
        for(int j = 0; j < nc && j < MAXN; j++)
            fscanf(fin, "%d", &matrix[i][j]);
    }

    fclose(fin);

    stampa(matrix, nr, nc);

    while(status == 0){
        int index, pos;
        char dir[MAXLENGTHFILENAME], sel[MAXLENGTHFILENAME];

        printf("Inserire il comando (nel formato <selettore> <indice> <direzione> <posizioni>): ");
        scanf(" "); gets(command);
        sscanf(command, " %s %d %s %d", &sel, &index, &dir, &pos); // comando che funziona come scanf() ma leggendo da una stringa invece che da un file

        if((strcmp(sel, "riga") == 0 && (strcmp(dir, "sinistra") == 0 || strcmp(dir, "destra") == 0)) || (strcmp(sel, "colonna") == 0 && (strcmp(dir, "su") == 0 || strcmp(dir, "giu") == 0))){
            if(strcmp(dir, "sinistra") == 0){
                ruota(matrix, index - 1, nc, pos, 1);
            }else if(strcmp(dir, "destra") == 0){
                ruota(matrix, index - 1, nc, pos, 2);
            }else if(strcmp(dir, "su") == 0){
                ruota(matrix, index - 1, nr, pos, 3);
            }else if(strcmp(dir, "giu") == 0){
                ruota(matrix, index - 1, nr, pos, 4);
            }

            stampa(matrix, nr, nc);
        }else if(strcmp(sel, "fine") == 0)
            status = -1;
        else
            printf("Comando non valido.");
    }

    return 0;
}

void stampa(int matrix[MAXN][MAXN], int nr, int nc){
    printf("La matrice e': \n");
    for(int i = 0; i < nr && i < MAXN; i++){
        for(int j = 0; j < nc && j < MAXN; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

void ruota(int matrix[MAXN][MAXN], int fixed, int N, int P, int dir){
    int rem, temp;

    switch(dir){
        case 1:
            for(int i = 0; i < P; i++){
                rem = matrix[fixed][N - 1];
                for(int j = N - 1; j > -1; j--){
                    if(j != 0){
                        temp = matrix[fixed][j - 1];
                        matrix[fixed][j - 1] = rem;
                        rem = temp;
                    }else
                        matrix[fixed][N - 1] = rem;
                }
            }
            break;
        case 2:
            for(int i = 0; i < P; i++){
                rem = matrix[fixed][0];
                for(int j = 0; j < N; j++){
                    if(j != N - 1){
                        temp = matrix[fixed][j + 1];
                        matrix[fixed][j + 1] = rem;
                        rem = temp;
                    }else
                        matrix[fixed][0] = rem;
                }
            }
            break;
        case 3:
            for(int i = 0; i < P; i++){
                rem = matrix[N - 1][fixed];
                for(int j = N - 1; j > -1; j--){
                    if(j != 0){
                        temp = matrix[j - 1][fixed];
                        matrix[j - 1][fixed] = rem;
                        rem = temp;
                    }else
                        matrix[N - 1][fixed] = rem;
                }
            }
            break;
        case 4:
            for(int i = 0; i < P; i++){
                rem = matrix[0][fixed];
                for(int j = 0; j < N; j++){
                    if(j != N - 1){
                        temp = matrix[j + 1][fixed];
                        matrix[j + 1][fixed] = rem;
                        rem = temp;
                    }else
                        matrix[0][fixed] = rem;
                }
            }
            break;
        default:
            printf("Modalità di rotazione non prevista.");
    }
}
