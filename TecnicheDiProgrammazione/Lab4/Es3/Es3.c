/*
Un file di testo contiene una matrice di interi con il seguente formato:
• la prima riga del file specifica le dimensioni della matrice (numero di righe nr e numero di colonne
nc). Si assuma che entrambi i valori siano comunque al più pari a 20.
• ciascuna delle nr righe successive contiene gli nc valori corrispondenti a una riga della matrice,
separati da uno o più spazi.
Si scriva un programma C che:
• legga tale matrice dal file di ingresso, il cui nome (massimo 20 caratteri) sia letto da tastiera
• chieda ripetutamente all’utente un valore dim compreso tra 1 e il minimo tra nr e nc e stampi
tutte le sottomatrici quadrate di tale dimensione contenute nella matrice
• termini l’iterazione se l’utente inserisce un valore non coerente con le dimensioni della matrice
• determini e stampi al termine la sottomatrice quadrata, tra quelle precedentemente individuate, la
somma dei cui elementi è massima. 
*/

#include <stdio.h>
#include <limits.h>

#define MAX_LENGTH 20

void stampa(int matrix[], int nr, int nc);

int main(int argc, char* argv[]){
    FILE *fin;
    char filename[MAX_LENGTH];
    int nr, nc, dim = 0;

    printf("Inserire il nome del file da cui ottenere i dati della matrice: ");
    scanf("%s", filename);

    fin = fopen(filename, "r");

    if(fin == NULL){
        printf("Impossibile aprire il file \"%s\"", filename);
        return -1;
    }

    fscanf(fin, "%d %d", &nr, &nc);
    int matrix[nr][nc];

    for(int i = 0; i < nr; i++){
        for(int j = 0; j < nc; j++){
            fscanf(fin, "%d", &matrix[i][j]);
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    while(dim <= nr && dim <= nc){
        int startR = 0, startC = 0, i, j, max_sum = INT_MIN, sum = 0, r = 0, c = 0;

        printf("Inserire la dimensione che si vuole avere per le sottomatrici quadrate da visualizzare, un valore non valido per uscire: ");
        scanf("%d", &dim);

        int maxM[dim][dim], temp[dim][dim];

        if(dim <= nr && dim <= nc){
            printf("Le sottomatrici di dimensione %d sono: \n\n", dim);
            for(i = 0; i < nr; i++){
                for(j = startC; j < (startC + dim) && j < nc; j++){
                    printf("%d ", matrix[i][j]);
                    sum += matrix[i][j];
                    temp[r][c] = matrix[i][j];
                    c += 1;
                }
                printf("\n");
                r += 1;
                c = 0;

                if(i == (startR + dim - 1) && (startR + dim - 1) < nr){
                    if(j < nc){
                        i = startR - 1;
                        startC += 1;
                        j = startC;
                    }else if(startR + dim < nr){
                        i = startR;
                        startR += 1;
                        startC = 0;
                    }

                    printf("\n");
                    r = 0;

                    if(sum > max_sum){
                        for(int l = 0; l < dim; l++){
                            for(int g = 0; g < dim; g++)
                                maxM[l][g] = temp[l][g];
                        }
                        max_sum = sum;
                    }
                    sum = 0;
                }
            }

            printf("\n");
            
            printf("\nLa matrice con somma massima %d e': \n", max_sum);
            for(int l = 0; l < dim; l++){
                for(int g = 0; g < dim; g++)
                    printf("%d ", maxM[l][g]);
                printf("\n");
            }
        }
    }

    fclose(fin);

    return 0;
}
