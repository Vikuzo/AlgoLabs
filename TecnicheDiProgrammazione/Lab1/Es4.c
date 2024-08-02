/*
Si scriva un programma che calcoli l'area di un cerchio o di un quadrato in base alla scelta dell'utente.
L'utente può specificare se calcolare l'area del quadrato (Q) tramite la lunghezza della diagonale (D) o
del lato (L), mentre l'area del cerchio (C) specificando se tramite il diametro (D) o il raggio (R).
In particolare:
a) Si definisca una costante P tramite #define e gli si assegni il valore 3.14.
b) Si acquisiscano da tastiera i caratteri.
c) Si calcoli il valore in base alla scelta dell'utente.
d) Si stampi il risultato a video.
*/

#include <stdio.h>

#define P 3.14

float circleArea(char choice);
float squareArea(char choice);

int main(int argc, char* argv[]){
    char choice;
    float area;

    printf("Inserire (Q) per calcolare l'area di un quadrato o (C) per calcolare l'area di un cerchio: ");
    scanf(" %c", &choice);

    switch(choice){
        case 'Q':
            printf("Inserire (D) per calcolare l'area attraverso la diagonale o (L) per utilizzare il lato: ");
            scanf(" %c", &choice);
            area = squareArea(choice);
            break;
        case 'C':
            printf("Inserire (D) per calcolare l'area attraverso il diametro o (R) per utilizzare il raggio: ");
            scanf(" %c", &choice);
            area = circleArea(choice);
            break;
        default:
            area = -1;
            printf("Opzione inserita non valida.");
    }

    if(area != -1)
        printf("L'area e': %.2f", area);
    else
        return -1;

    return 0;
}

float circleArea(char choice){
    float value;

    switch(choice){
        case 'D':
            printf("Inserire il valore del diametro: ");
            scanf("%f", &value);
            return (P * value * value)/4;
        case 'R':
            printf("Inserire il valore del raggio: ");
            scanf("%f", &value);
            return (P * value * value);
        default:
            printf("Opzione inserita non valida");
            return -1;
    }
}

float squareArea(char choice){
    float value;
    switch(choice){
        case 'D':
            printf("Inserire il valore della diagonale: ");
            scanf("%f", &value);
            return (value * value)/2;
        case 'L':
            printf("Inserire il valore del lato: ");
            scanf("%f", &value);
            return value*value;
        default:
            printf("Opzione inserita non valida");
            return -1;
    }
}