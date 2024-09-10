/*
Scrivere un programma in C che visualizzi i primi N numeri della serie di Fibonacci con N acquisito
in input da tastiera.

Suggerimento: ecco i primi numeri appartenenti alla serie 0 1 1 2 3 5 8... . In modo formale la serie si
costruisce considerando la seguente relazione: Xi = Xi-1 + Xi-2, con X0 = 0 e X1 = 1;

Approfondimento (variante dell’esercizio): si modifichi la serie come segue:
Xi = Xi-1 * Xi-2, con X0 = 1 e X1 = 2;
Si determini sperimentalmente (osservando i risultati ottenuti) quanti sono gli elementi di questa serie
rappresentabili con variabili di tipo intero (int) e di tipo intero senza segno (unsigned int)
*/

#include <stdio.h>

void FibonacciVers1(int N);
void FibonacciVers2(int N);

int main(int argc, char* argv[]){
    int N;
    
    printf("Inserire il limite superiore della serie di Fibonacci che si vuole generare: ");
    scanf("%d", &N);

    FibonacciVers1(N);
    printf("\n");
    FibonacciVers2(N);

    return 0;
}

void FibonacciVers1(int N){
    unsigned int x0 = 0, x1 = 1, temp;

    for(int i = 0; i < N; i++){
        if(i == 0)
            printf("0 ");
        else if(i == 1)
            printf("1 ");
        else{
            printf("%d ", (x0 + x1));
            temp = x1;
            x1 = x0 + x1;
            x0 = temp;
        }
    }
}

void FibonacciVers2(int N){
    unsigned int x0 = 1, x1 = 2, temp;

    for(int i = 0; i < N; i++){
        if(i == 0)
            printf("0 ");
        else if(i == 1 || i == 2)
            printf("1 ");
        else{
            printf("%d ", (x0 * x1));
            temp = x1;
            x1 = x0 * x1;
            x0 = temp;
        }
    }
}