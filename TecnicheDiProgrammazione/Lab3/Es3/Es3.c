/*
E’ data una sequenza di numeri interi, contenuta in un file testo (numeri.txt, definito con #define), nel
quale gli interi sono separati da spazio o a-capo. Occorre verificare che l’i-esimo numero xi (con i ≥2)
sia, rispetto ai due numeri precedenti (xi-1 e xi-2), pari alla loro somma (xi-2 + xi-1), differenza (xi-2 - xi-1),
prodotto (xi-2 * xi-1) o quoziente (xi-2 / xi-1) (attenzione a evitare le divisioni per 0!). Se un dato non è
corretto, va scartato e si passa a verificare il successivo (ignorando il dato scartato). Occorre inoltre
individuare il massimo e il minimo tra i dati della sequenza (ignorando i dati eventualmente scartati).
Al termine stampare a video:
1. il risultato della verifica, cioè se tutti i dati rispettano la regola o se qualcuno (indicare quanti) sia
stato scartato
2. I valori massimo e minimo tra i numeri in sequenza, escludendo quelli eventualmente scartati.
*/

#include <stdio.h>
#include <limits.h>

#define FILENAME "numeri.txt"

int check(int op1, int op2, int res);
int isMax(int oldMax, int newMax);
int isMin(int oldMin, int newMin);

int main(int argc, char* argv[]){
    FILE *fin = fopen(FILENAME, "r");
    int op1, op2, res, max = INT_MIN, min = INT_MAX, s = 0;

    if(fin == NULL){
        printf("Impossibile trovate il file \"%s\"", FILENAME);
        return -1;
    }

    fscanf(fin, " %d %d", &op1, &op2);
    if(isMax(max, op1) == 0)
        max = op1;
    if(isMin(min, op1) == 0)
        min = op1;

    if(isMax(max, op2) == 0)
        max = op2;
    if(isMin(min, op2) == 0)
        min = op2;

    while(!feof(fin)){
        fscanf(fin, " %d ", &res);

        if(check(op1, op2, res) == 0){
            if(isMax(max, res) == 0)
                max = res;
            if(isMin(min, res) == 0)
                min = res;
            op1 = op2;
            op2 = res;
        }else
            s += 1;
    }

    printf("Numero massimo: %d\nNumero minimo: %d\nNumeri scartati: %d", max, min, s);

    return 0;
}

int check(int op1, int op2, int res){
    if((op1 + op2) == res)
        return 0;
    if((op1 - op2) == res)
        return 0;
    if((op1 * op2) == res)
        return 0;
    if(op2 != 0 && (op1 / op2) == res)
        return 0;

    return 1;
}

int isMax(int oldMax, int newMax){
    if(newMax > oldMax)
        return 0;
    return 1;
}

int isMin(int oldMin, int newMin){
    if(newMin < oldMin)
        return 0;
    return 1;
}