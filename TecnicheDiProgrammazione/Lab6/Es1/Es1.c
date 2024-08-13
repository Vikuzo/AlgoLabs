/*
Un'azienda di trasporti urbani, traccia i propri automezzi in un file di log (file testuale di nome corse.txt).
Il file è organizzato come segue:
• sulla prima riga, un intero positivo indica il numero di successive righe del file stesso (al più 1000)
• le righe successive riportano le informazioni sulle tratte, una per riga, con formato:

    <codice_tratta> <partenza> <destinazione> <data> <ora_partenza> <ora_arrivo> <ritardo>

Tutte le stringhe sono lunghe al massimo 30 caratteri. Il ritardo è un numero intero, eventualmente nullo, 
che rappresenta i minuti di ritardo accumulati dalla corsa.
Si scriva un programma C che, letto il file e acquisitone il contenuto in una oppurtuna struttura dati, 
risponda alle seguenti interrogazioni (presentate mediante un menu):
1. elencare tutte le corse partite in un certo intervallo di date
2. elencare tutti le corse partite da una certa fermata (partenza)
3. elencare tutti le corse aventi una data destinazione (capolinea)
4. elencare tutte le corse che hanno raggiunto la destinazione in ritardo, in un certo intervallo di date
5. elencare il ritardo complessivo accumulato dalle corse identificate da un certo codice di tratta

Le interrogazioni di cui sopra siano gestite mediante menu di comandi (si veda il paragrafo 4.4.1, Dal
problema al programma). Ogni comando consiste di una parola tra "date", "partenza", "capolinea", "ritardo", 
"ritardo_tot" e "fine", eventualmente seguita sulla stessa riga da altre informazioni, ad esempio due date per "date", 
una fermata di partenza per "partenza", etc.
Si utilizzi la strategia di codifica dei comandi mediante tipo enum comando_e, contenente i simboli
r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine, che consente
menu basati su switch-case.
Si consiglia di:
• realizzare una funzione leggiComando che, acquisito in modo opportuno il comando, ritorni il
corrispondente valore di tipo comando_e
• realizzare una funzione menuParola che, ricevuti tra i parametri la tabella, la dimensione (cioè il
numero effettivo di dati) della tabella e il tipo di comando, gestisca mediante menu l’acquisizione
delle informazioni aggiuntive necessarie per quel comando e la chiamata di un’opportuna funzione
di selezione e stampa dei dati selezionati.
Si noti che la data di una corsa non subisce variazioni a causa del ritardo.
*/

#include <stdio.h>
#include <string.h>

#define FILENAME "log.txt"
#define MAXLINES 1000
#define MAX_WD_CHAR 200
#define MAXCHAR 30

typedef enum {r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine} comando_e;

// funzioni principali

void menuParola(char datas[MAXLINES][MAX_WD_CHAR], int n, comando_e comm);
int readFile(char datas[MAXLINES][MAX_WD_CHAR], char filename[]);
comando_e leggiComando();

// funzioni secondarie

void date(char datas[MAXLINES][MAX_WD_CHAR], int n, char start_d[MAXCHAR], char end_d[MAXCHAR]);
void partenze(char datas[MAXLINES][MAX_WD_CHAR], int n, char stop[MAXCHAR]);
void capolinea(char datas[MAXLINES][MAX_WD_CHAR], int n, char stop[MAXCHAR]);
void rit(char datas[MAXLINES][MAX_WD_CHAR], int n, char start_d[MAXCHAR], char end_d[MAXCHAR]);
void rit_tot(char datas[MAXLINES][MAX_WD_CHAR], int n, char codec[MAXCHAR]);
int compareDates(char start[MAXCHAR], char end[MAXCHAR]);

int main(int argc, char *argv[]){
    comando_e choice = r_date;
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
    char stop[MAXCHAR], code[MAXCHAR], start[MAXCHAR], end[MAXCHAR];

    switch(comm){
        case r_date:
            printf("Inserire la data iniziale nel formato aa/mm/gg: ");
            scanf("%s", &start);
            printf("Inserire la data finale nel formato aa/mm/gg: ");
            scanf("%s", &end);
            date(datas, n, start, end);
            return;
        case r_partenza:
            printf("Inserire la fermata di partenza di cui si vogliono vedere tutte le tratte: ");
            scanf("%s", &stop);
            partenze(datas, n, stop);
            return;
        case r_capolinea:
            printf("Inserire la fermata di arrivo di cui si vogliono vedere tutte le tratte: ");
            scanf("%s", &stop);
            capolinea(datas, n, stop);
            return;
        case r_ritardo:
            printf("Inserire la data iniziale nel formato aa/mm/gg: ");
            scanf("%s", &start);
            printf("Inserire la data finale nel formato aa/mm/gg: ");
            scanf("%s", &end);
            rit(datas, n, start, end);
            return;
        case r_ritardo_tot:
            printf("Inserire il codice della tratta di cui si vuole vedere il ritardo cumulato: ");
            scanf("%s", &code);
            rit_tot(datas, n, code);
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
    printf("1. Elencare tutte le corse partite in un certo intervallo di date [date].\n");
    printf("2. Elencare tutte le corse partite da una certa fermata di partenza [partenza].\n");
    printf("3. Elencare tutte le corse aventi una certa fermata di destinazione [capolinea].\n");
    printf("4. Elencare tutte le corse che hanno raggiunto la destinazione in ritardo in un certo intervallo di date [ritardo].\n");
    printf("5. Elencare il ritardo complessivo accumulato dalle corse identificate da un certo codice di tratta [ritardo_tot].\n");
    printf("6. Terminare il processo [fine].\n");
    printf("Inserire il numero corrispondente al comando che su vuole eseguire: ");
    scanf("%s", &choice);

    if(strcmp(choice, "date") == 0)
        return r_date;
    else if(strcmp(choice, "partenza") == 0)
        return r_partenza;
    else if(strcmp(choice, "capolinea") == 0)
        return r_capolinea;
    else if(strcmp(choice, "ritardo") == 0)
        return r_ritardo;
    else if(strcmp(choice, "ritardo_tot") == 0)
        return r_ritardo_tot;
    else if(strcmp(choice, "fine") == 0)
        return r_fine;

    return -1;
}

// secondarie

void date(char datas[MAXLINES][MAX_WD_CHAR], int n, char start_d[MAXCHAR], char end_d[MAXCHAR]){
    char code[MAXCHAR], start[MAXCHAR], end[MAXCHAR], data[MAXCHAR], start_h[MAXCHAR], end_h[MAXCHAR];
    int rit;

    printf("Le tratte con arrivo dal %s al %s sono:\n", start_d, end_d);
    
    for(int i = 0; i < n; i++){
        sscanf(datas[i], " %s %s %s %s %s %s %d", &code, &start, &end, &data, &start_h, &end_h, &rit);
        if(compareDates(start_d, data) >= 0 && compareDates(data, end_d) >= 0)
            printf("%s", datas[i]);
    }
}

void partenze(char datas[MAXLINES][MAX_WD_CHAR], int n, char stop[MAXCHAR]){
    char code[MAXCHAR], start[MAXCHAR], end[MAXCHAR], data[MAXCHAR], start_h[MAXCHAR], end_h[MAXCHAR];
    int rit;

    printf("Le tratte con partenza %s sono:\n", stop);
    
    for(int i = 0; i < n; i++){
        sscanf(datas[i], " %s %s %s %s %s %s %d", &code, &start, &end, &data, &start_h, &end_h, &rit);
        if(strcmp(start, stop) == 0)
            printf("%s", datas[i]);
    }
}

void capolinea(char datas[MAXLINES][MAX_WD_CHAR], int n, char stop[MAXCHAR]){
    char code[MAXCHAR], start[MAXCHAR], end[MAXCHAR], data[MAXCHAR], start_h[MAXCHAR], end_h[MAXCHAR];
    int rit;

    printf("Le tratte con arrivo a %s sono:\n", stop);
    
    for(int i = 0; i < n; i++){
        sscanf(datas[i], " %s %s %s %s %s %s %d", &code, &start, &end, &data, &start_h, &end_h, &rit);
        if(strcmp(end, stop) == 0)
            printf("%s", datas[i]);
    }
}

void rit(char datas[MAXLINES][MAX_WD_CHAR], int n, char start_d[MAXCHAR], char end_d[MAXCHAR]){
    char code[MAXCHAR], start[MAXCHAR], end[MAXCHAR], data[MAXCHAR], start_h[MAXCHAR], end_h[MAXCHAR];
    int rit;

    printf("Le tratte con ritardo dal %s al %s sono:\n", start_d, end_d);
    
    for(int i = 0; i < n; i++){
        sscanf(datas[i], " %s %s %s %s %s %s %d", &code, &start, &end, &data, &start_h, &end_h, &rit);
        if(compareDates(start_d, data) >= 0 && compareDates(data, end_d) >= 0 && rit != 0)
            printf("%s", datas[i]);
    }
}

void rit_tot(char datas[MAXLINES][MAX_WD_CHAR], int n, char codec[MAXCHAR]){
    char code[MAXCHAR], start[MAXCHAR], end[MAXCHAR], data[MAXCHAR], start_h[MAXCHAR], end_h[MAXCHAR];
    int rit, rit_tot = 0;
    
    for(int i = 0; i < n; i++){
        sscanf(datas[i], " %s %s %s %s %s %s %d", &code, &start, &end, &data, &start_h, &end_h, &rit);
        if(strcmp(codec, code) == 0)
            rit_tot += rit;
    }

    printf("Il ritardo cumulato della tratta %s e': %d\n", codec, rit_tot);
}

int compareDates(char start[MAXCHAR], char end[MAXCHAR]){
    int start_g, start_m, start_a;
    int end_g, end_m, end_a;

    sscanf(start, "%d/%d/%d", &start_a, &start_m, &start_g);
    sscanf(end, "%d/%d/%d", &end_a, &end_m, &end_g);


    if((end_a - start_a) == 0){
        if((end_m - start_m) == 0){
            return end_g - start_g;
        }else
            return end_m - start_m;
    }else
        return end_a - start_a;
}
