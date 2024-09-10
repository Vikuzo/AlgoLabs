/*
A partire dalle specifiche dell’esercizio precedente, estendere le funzionalità del programma per
mantenere in contemporanea più ordinamenti della base dati
Suggerimento: si legga il vettore originale una sola volta, mantenendolo nell'esatto ordine di lettura per
tutta la durata dell'esecuzione. Si affianchino al vettore originale tanti vettori di puntatori a struttura quanti
sono gli ordinamenti richiesti, con i quali sono gestiti gli ordinamenti.
*/

#include <stdio.h>
#include <string.h>

#define FILENAME "log.txt"
#define MAXLINES 1000
#define MAX_WD_CHAR 200
#define MAXCHAR 30

typedef enum {r_stampa, r_date, r_code, r_stazPar, r_stazArr, r_ricerca, r_fine} comando_e;

// funzioni principali

void menuParola(char datas[MAXLINES][MAX_WD_CHAR], int n, comando_e comm);
int readFile(char datas[MAXLINES][MAX_WD_CHAR], char filename[]);
comando_e leggiComando();

// funzioni secondarie

void stampa(char *datas[], int n);

int main(int argc, char *argv[]){
    comando_e choice = r_stampa;
    char datas[MAXLINES][MAX_WD_CHAR], n;

    if((n = readFile(datas, FILENAME)) == -1){
        printf("Impossibile aprire il file \"%s\"", FILENAME);
        return -1;
    }

    while(choice != r_fine){
        choice = leggiComando();
        menuParola(datas, n, choice);
    }

    return 0;
}

// principali

void menuParola(char datas[MAXLINES][MAX_WD_CHAR], int n, comando_e comm){
    char start[MAXCHAR];

    switch(comm){
        case r_stampa:
            stampa(datas, n);
            return;
        case r_date:
            return;
        case r_code:
            return;
        case r_stazPar:
            return;
        case r_stazArr:
            return;
        case r_ricerca:
            return;
        case r_fine:
            printf("Chiusura del programma in corso...");
            return;
        default:
            printf("\n\nComando inserito invalido.\n\n");
            return;
    }
}

int readFile(char datas[MAXLINES][MAX_WD_CHAR], char filename[]){
    FILE *fin = fopen(filename, "r");
    int n;

    if(fin == NULL)
        return -1;

    fscanf(fin, " %d ", &n);

    for(int i = 0; i < n && !feof(fin); i++)   
        fgets(datas[i], MAX_WD_CHAR, fin);

    fclose(fin);

    return n;
}

comando_e leggiComando(){
    char choice[MAXCHAR];

    printf("Fra [] e' indicato il comando correlato:\n");
    printf("1. Stampare tutte le corse presenti nei log [stampa].\n");
    printf("2. Ordinare le corse in base alla data [date].\n");
    printf("3. Ordinare le corse in base al codice delle tratte [codice].\n");
    printf("4. Ordinare le corse in base alle stazioni di partenza [partenze].\n");
    printf("5. Ordinare le corse in base alle stazioni di arrivo [arrivi].\n");
    printf("6. Ricercare una tratta per stazione di partenza [ricerca].\n");
    printf("7. Terminare il processo [fine].\n");
    printf("Inserire il numero corrispondente al comando che su vuole eseguire: ");
    scanf("%s", &choice);

    if(strcmp(choice, "stampa") == 0)
        return r_stampa;
    else if(strcmp(choice, "date") == 0)
        return r_date;
    else if(strcmp(choice, "codice") == 0)
        return r_code;
    else if(strcmp(choice, "partenze") == 0)
        return r_stazPar;
    else if(strcmp(choice, "arrivi") == 0)
        return r_stazArr;
    else if(strcmp(choice, "ricerca") == 0)
        return r_ricerca;
    else if(strcmp(choice, "fine") == 0)
        return r_fine;

    return -1;
}

// utilitarie

void stampa(char *datas[], int n){
    for(int i = 0; i < n; i++)
        printf("%s", datas[i]);
}

// secondarie
