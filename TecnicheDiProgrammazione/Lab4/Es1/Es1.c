/*
Sia V un vettore di N interi (con N <= 30). Si scriva un programma in C che, una volta acquisito da tastiera 
(o da file, la scelta è libera) il contenuto del vettore, chiami una funzione avente prototipo
    sottoSequenze(int V[], int N);
La funzione visualizzi tutti i sottovettori di dimensione massima formati da celle contigue, contenenti
dati non nulli. 
*/

#include <stdio.h>

#define N 30

void sottoSequenza(int V[], int n);
void stampa(int V[], int start, int end);

int main(int argc, char* argv[]){
    int V[N], flag = 0, n = 0;
    char choice;

    for(int i = 0; i < N && flag == 0; i++){
        printf("Inserisci (c) per inserire un nuovo numero all'interno del vettore (%d di %d), altro per chiudere la fase di inserimento: ", i, N);
        scanf(" %c", &choice);

        if(choice == 'c'){
            printf("Inserisci il nuovo numero: "),
            scanf("%d", &V[i]);
            n += 1;
        }else
            flag = 1;

    }

    sottoSequenza(V, n);

    return 0;
}

void sottoSequenza(int V[], int n){
    int counter = 0, max = 0, start = 0;

    for(int i = 0; i < n; i++){
        if(V[i] != 0)
            counter += 1;

        if(V[i] == 0 || i == (n - 1)){
            if(counter > max)
                max = counter;
            counter = 0;
        }
    }

    counter = 0;

    for(int i = 0; i < n; i++){
        if(V[i] != 0)
            counter += 1;
        
        if(V[i] == 0 || i == (n - 1)){
            if(counter == max){
                if(i == (n-1) && V[i] != 0)
                    stampa(V, start, i + 1);
                else
                    stampa(V, start, i);
            }
            counter = 0;
            start = i + 1;
        }
    }
}

void stampa(int V[], int start, int end){
    printf("[");
    for(int i = start; i < end; i++)
        printf(" %d ", V[i]);
    printf("] ");
}