/*
Scrivere un programma calcolatrice che esegua le 4 operazioni aritmetiche di base (addizione, sottrazione, 
divisione, moltiplicazione) tra due valori op1 e op2. Il programma deve:
a) Acquistare da tastiera utilizzando getchar() l'operazione da eseguire (+, -, /, *);
b) Acquistare da tastiera utilizzando scanf() i due operandi di tipo float;
c) Stampare a schermo il carattere dell'operazione seguito dal risultato.
*/

#include <stdio.h>

float add(float a, float b);
float sub(float a, float b);
float mul(float a, float b);
float div(float a, float b);

int main(int argc, char* argv[]){
    char choice;
    float op1, op2, result;

    printf("Inserire l'operazione che si vuole eseguire (+, -, /, *): ");
    scanf(" %c", &choice);
    printf("Inserire il valore del primo operando: ");
    scanf("%f", &op1);
    printf("Inserire il valore del secondo operando: ");
    scanf("%f", &op2);

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

    printf("Il risultato dell'operazione %c e': %0.2f", choice, result);

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