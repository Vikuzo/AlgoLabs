#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME_MAX_LENGTH 30
#define MAX_LINE_LENGTH 200

typedef enum {r_new, r_stampa, r_date, r_code, r_stazPar, r_stazArr, r_ricerca, r_fine} comando_e;

// primarie
void menuParola(char ***datas, int *n, comando_e comm);
comando_e leggiComando();

// secondarie

// utilitarie
char *getFileName();
int readFile(char ***datas, char *filename, int oldn);
void tabAlloc(char ***datas, int n);
void freeTab(char **datas, int n);
void printTab(char **datas, int n);

int main(int argc, char * argv[]){
    comando_e choice = r_new;
    char **datas;
    int n = 0;
    
    while(choice != r_fine){
        menuParola(&datas, &n, choice);
        choice = leggiComando();
    }

    return 0;
}

// primarie
void menuParola(char ***datas, int *n, comando_e comm){

    switch(comm){
        case r_new:
            *n = readFile(datas, getFileName(), *n);
            return;
        case r_stampa:
            printTab(*datas, *n);
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

comando_e leggiComando(){
    char choice[FILENAME_MAX_LENGTH];

    printf("Fra [] e' indicato il comando correlato:\n");
    printf("1. Inserire un nuovo file [nuovo].\n");
    printf("2. Stampare tutte le corse presenti nei log [stampa].\n");
    printf("3. Ordinare le corse in base alla data [date].\n");
    printf("4. Ordinare le corse in base al codice delle tratte [codice].\n");
    printf("5. Ordinare le corse in base alle stazioni di partenza [partenze].\n");
    printf("6. Ordinare le corse in base alle stazioni di arrivo [arrivi].\n");
    printf("7. Ricercare una tratta per stazione di partenza [ricerca].\n");
    printf("8. Terminare il processo [fine].\n");
    printf("Inserire il  comando che su vuole eseguire: ");
    scanf("%s", &choice);

    if(strcmp(choice, "nuovo") == 0)
        return r_new;
    else if(strcmp(choice, "stampa") == 0)
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

// secondarie


// utilitarie
char *getFileName(){
    char *filename = (char*)malloc(FILENAME_MAX_LENGTH * sizeof(char));

    printf("Inserire il nome del file da leggere: ");
    scanf("%s", filename);

    return filename;
}

int readFile(char ***datas, char *filename, int oldn){
    FILE *fin = fopen(filename, "r");
    int n;

    if(fin == NULL)
        return -1;

    if(oldn != 0)
        freeTab(*datas, oldn); 
    fscanf(fin, " %d ", &n);
    tabAlloc(datas, n);

    for(int i = 0; i < n && !feof(fin); i++) 
        fgets((*datas)[i], MAX_LINE_LENGTH, fin);

    fclose(fin);
    free(filename);

    return n;
}

void tabAlloc(char ***datas, int n){
    char **m;

    m = (char**)malloc(n * sizeof(char*));
    for(int i = 0; i < n; i++) 
        m[i] = (char*)malloc(MAX_LINE_LENGTH * sizeof(char));
    *datas = m;
}

void freeTab(char **datas, int n){
    for(int i = 0; i < n; i++)
        free(datas[i]);
    free(datas);
}

void printTab(char **datas, int n){
    for(int i = 0; i < n; i++)
        printf("%s", datas[i]);
}