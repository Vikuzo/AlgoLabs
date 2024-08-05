/*
Scrivere un programma in C che, acquisiti due numeri interi positivi, ne calcoli il massimo comune divisore
utilizzando la formula di Eulero.
*/
#include <stdio.h>

// int formulaEulero(int a, int b);

int main(int argc, char* argv[]){
    int a, b;

    printf("Inserire il primo numero intero: ");
    scanf("%d", &a);
    printf("Inserire il secondo numero intero: ");
    scanf("%d", &b);

    /*int r = formulaEulero(a, b);
    printf("Il massimo comune divisore e': %d", r);*/

    int c = 1;

    while(c != 0){
        if(a >= b){
            c = a % b;
            a = b;
            b = c;
        }else{
            c = b % a;
            b = a;
            a = c;
        }
    }

    if(a != 0)
        c = a;
    else
        c = b;

    printf("Il massimo comune divisore e': %d", c);

    return 0;
}

// versione con ricorsione, tecnica avanzata
/*int formulaEulero(int a, int b){
    int c;

    if(a >= b){
        c = a % b;
        if(c == 0)
            return b;
        else
            return formulaEulero(b, c);
    }else{
        c = b % a;
        if(c == 0)
            return a;
        else
            return formulaEulero(c, a);
    }
}*/