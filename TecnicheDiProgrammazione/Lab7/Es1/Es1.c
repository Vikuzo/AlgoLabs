/*
Un file di testo contiene una matrice di interi (0 o 1) con il seguente formato:
• la prima riga del file specifica le dimensioni reali della matrice (numero di righe nr e numero di
colonne nc). Si assuma che entrambi i valori siano al più pari a 50
• ciascuna delle nr righe successive contiene gli nc valori corrispondenti a una riga della
matrice, separati da uno o più spazi
• ogni cella può contenere solamente il valore 0 (associato al colore bianco) o il valore 1
(associato al colore nero)
• le celle nere sono organizzate in modo da formare regioni rettangolari (ogni regione nera è
circondata da una cornice di celle bianche, oppure da bordo/i della matrice). A tal fine, si
consideri che l'adiacenza delle celle è considerata solo lungo i quattro punti cardinali principali
(Nord, Sud, Ovest, Est), non in diagonale.
Si scriva un programma C che:
• legga la matrice dal file di ingresso (il file non contiene errori, quindi ci sono solo rettangoli
neri che rispettano i vincoli)
• individui le regioni nere più grandi per altezza, larghezza e area totale
• in caso di parità, si riporti una tra le regioni individuate che soddisfano un certo criterio
*/

#include <stdio.h>

#define FILENAME "mappa.txt"
#define MAXR 50
#define MAXC 50

int readFile(FILE *fin, int datas[MAXR][MAXC], int nr, int nc);
void maxBase(int datas[MAXR][MAXC], int nr, int nc);
void maxArea(int datas[MAXR][MAXC], int nr, int nc);
void maxAltezza(int datas[MAXR][MAXC], int nr, int nc);

int main(int argc, char* argv[]){
    FILE *fin;
    int datas[MAXR][MAXC], nr, nc;

    if((fin = fopen(FILENAME, "r")) == NULL){
        printf("Impossibile aprire il file \"%s\".", FILENAME);
        return -1;
    }

    fscanf(fin, "%d %d", &nr, &nc);
    readFile(fin, datas, nr, nc);
    fclose(fin);

    maxBase(datas, nr, nc);
    maxArea(datas, nr, nc);
    maxAltezza(datas, nr, nc);

    return 0;
}

int readFile(FILE *fin, int datas[MAXR][MAXC], int nr, int nc){
    for(int i = 0; i < nr; i++){
        for(int j = 0; j < nc; j++)
            fscanf(fin, "%d", &datas[i][j]);
    }
}

void maxBase(int datas[MAXR][MAXC], int nr, int nc){
    int maxB = 0, maxH = 0, counter, r = 0, c = 0;

    for(int i = 0; i < nr; i++){
        counter = 0;
        for(int j = 0; j < nc; j++){
            if(datas[i][j] == 1)
                counter += 1;
            else if(datas[i][j] == 0 || j == nc - 1){
                if(counter > maxB){
                    maxB = counter;
                    r = i;

                    int g;
                    if(j == nc - 1){
                        c = j - counter + 1;
                        g = j;
                    }else{
                        g = j - 1;
                        c = j - counter;
                    }

                    counter = 0;
                    for(int l = i; l < nr && datas[l][g] != 0; l++){
                        counter += 1;
                    }
                    maxH = counter;
                    counter = 0;
                }else
                    counter = 0;
            }
        }
    }

    printf("Max Base: estr. sup. SX=<%d, %d> b=%d, h=%d, Area=%d\n", r, c, maxB, maxH, (maxB * maxH));
}

void maxArea(int datas[MAXR][MAXC], int nr, int nc){
    int maxB = 0, maxH = 0, maxA = 0, counter, r = 0, c = 0, finB, finH;

    for(int i = 0; i < nr; i++){
        counter = 0;
        for(int j = 0; j < nc; j++){
            if(datas[i][j] == 1)
                counter += 1;
            else if(datas[i][j] == 0 || j == nc - 1){
                maxB = counter;

                int g;
                if(j == nc - 1)
                    g = j;
                else
                    g = j - 1;

                counter = 0;
                for(int l = i; l < nr && datas[l][g] != 0; l++){
                    counter += 1;
                }
                maxH = counter;
                counter = 0;

                if(maxA < maxH * maxB){
                    maxA = maxH * maxB;
                    r = i;
                    if(j == nc - 1)
                        c = j - maxB + 1;
                    else
                        c = j - maxB;
                    finB = maxB;
                    finH = maxH;
                }
            }else
                counter = 0;    
        }
    }

    printf("Max Area: estr. sup. SX=<%d, %d> b=%d, h=%d, Area=%d\n", r, c, finB, finH, (finB * finH));
}

void maxAltezza(int datas[MAXR][MAXC], int nr, int nc){
    int maxB = 0, maxH = 0, counter, r = 0, c = 0;

    for(int i = 0; i < nc; i++){
        counter = 0;
        for(int j = 0; j < nr; j++){
            if(datas[j][i] == 1)
                counter += 1;

            if(datas[j][i] == 0 || j == nr - 1){
                if(counter > maxH){
                    maxH = counter;
                    c = i;

                    int g;
                    if(j == nr - 1){
                        r = j - counter + 1;
                        g = j;
                    }else{
                        g = j - 1;
                        r = j - counter; 
                    }

                    counter = 0;
                    for(int l = i; l < nc && datas[g][l] != 0; l++){
                        counter += 1;
                    }
                    maxB = counter;
                    counter = 0;
                }else
                    counter = 0;
            }
        }
    }

    printf("Max Altezza: estr. sup. SX=<%d, %d> b=%d, h=%d, Area=%d\n", r, c, maxB, maxH, (maxB * maxH));
}
