/*
Si scriva una funzione C in grado di permettere all'utente di far ruotare verso destra o verso sinistra i
contenuti di un vettore di N interi, di un numero a scelta di posizioni P. Il vettore è da intendersi come
circolare, nel senso che l’elemento a destra della cella di indice N-1 è la cella di indice 0 e l’elemento
a sinistra della cella di indice 0 è la cella di indice N-1.
La funzione abbia il seguente prototipo:
void ruota(int v[maxN], int N, int P, int dir);
Il main:
1. acquisisca da tastiera N (N  maxN con maxN pari a 30)
2. acquisisca da tastiera il vettore V
3. effettui ripetutamente delle rotazioni, acquisendo ciascuna volta P (P < N, P=0 per terminare) e la
direzione (dir =-1 per rotazione a destra, dir = 1 per rotazione a sinistra) e stampi il vettore risultante.
*/

#include <stdio.h>

#define MAX_N 30

void ruota(int v[MAX_N], int N, int P, int dir);

int main(int argc, char* argv[]){
    int N, P, dir, v[MAX_N];
    char choice = 'y';

    do{
        printf("Inserisci la grandezza del vettore (massimo %d): ", MAX_N);
        scanf("%d", &N);
    }while(N > 30);

    for(int i = 0; i < N; i++){
        printf("Inserire un nuovo numero (%d di %d): ", (i + 1), N);
        scanf("%d", &v[i]);
    }

    while(choice == 'y'){
        printf("Inserire (y) per ruotare il vettore, qualsiasi altro valore per uscire dal programma: ");
        scanf(" %c", &choice);

        if(choice == 'y'){
            printf("Inserire il numero di posizioni di cui si vuole far ruotare il vettore: ");
            scanf("%d", &P);
            printf("Inserire la direzione in cui si vuole ruotare il vettore (-1 -> destra, 1 -> sinistra): ");
            scanf("%d", &dir);
            if(dir == 1 || dir == -1)
                ruota(v, N, P, dir);
            else
                printf("Direzione invalida");
                
        }
    }

    return 0;
}

void ruota(int v[MAX_N], int N, int P, int dir){
    int temp, rem;

    printf("da -> [");
    for(int i = 0; i < N; i++)
        printf(" %d ", v[i]);
    printf("] a -> [");

    if(dir == 1){
        for(int i = 0; i < P; i++){
            rem = v[N - 1];
            for(int j = N - 1; j > -1; j--){
                if(j != 0){
                    temp = v[j - 1];
                    v[j - 1] = rem;
                    rem = temp;
                }else
                    v[N - 1] = rem;
            }
        }
    }else{
        for(int i = 0; i < P; i++){
            rem = v[0];
            for(int j = 0; j < N; j++){
                if(j != N - 1){
                    temp = v[j + 1];
                    v[j + 1] = rem;
                    rem = temp;
                }else
                    v[0] = rem;
            }
        }
    }

    for(int i = 0; i < N; i++)
        printf(" %d ", v[i]);
    printf("]\n");
}