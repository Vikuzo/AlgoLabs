/*
Partendo dal codice dell'esercizio precedente, scrivere un programma C che legga da file una serie di 
operazioni da eseguire e scriva su un altro file l'operazione eseguita ed il risultato dell'operazione 
con due cifre decimali.
*/

#include <stdio.h>

float add(float a, float b);
float sub(float a, float b);
float mul(float a, float b);
float div(float a, float b);
int menu(char choice, float op1, float op2, FILE *fout);

int main(int argc, char* argv[]){
    char choice;
    float op1, op2;
    FILE *fin = fopen("Operations.txt", "r");
    FILE *fout = fopen("Result.txt", "w");

    if (fin == NULL) {
        printf("Error opening file\n");
        return -1;
    }

    while(!feof(fin)){
        fscanf(fin, " %c %f %f", &choice, &op1, &op2);
        int flag = menu(choice, op1, op2, fout);
        if(flag == -1)
            return -1;
    }

    fclose(fin);
    fclose(fout);
    return 0;
}

float add(float a, float b){
    return a + b;
}

float sub(float a, float b){
    return a - b;
}

float mul(float a, float b){
    return a * b;
}

float div(float a, float b){
    return a / b;
}

int menu(char choice, float op1, float op2, FILE *fout){
    float result;

    switch(choice){
        case '+':
            result = add(op1, op2);
            break;
        case '-':
            result = sub(op1, op2);
            break;
        case '*':
            result = mul(op1, op2);
            break;
        case '/':
            if(op2 == 0){
                printf("Non si può effettuare una divisione per zero.");
                return -1;
            }else
                result = div(op1, op2);
            break;
        default:
            printf("Richiesta non valida.");
            return -1;
    }

    fprintf(fout, "%c %.2f\n", choice, result);

    return 0;
}