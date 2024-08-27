/*
Si consideri lo scenario introdotto nell’esercizio precedente. Si realizzi un programma in C che, una volta
acquisite le informazioni in una opportuna struttura dati, renda disponibili le seguenti operazioni:
• stampa, a scelta se a video o su file, dei contenuti del log
• ordinamento del vettore per data, e a parità di date per ora
• ordinamento del vettore per codice di tratta
• ordinamento del vettore per stazione di partenza
• ordinamento del vettore per stazione di arrivo
• ricerca di una tratta per stazione di partenza (anche parziale come prefisso della stringa, quindi
dal primo carattere). Nel caso di più risultati, elencarli tutti.

Per quanto riguarda le ricerche, si richiede che siano implementate sia una funzione di ricerca dicotomica
sia una funzione di ricerca lineare. Per quanto riguarda l’ordinamento, si presti attenzione alla stabilità
dell’algoritmo prescelto nel caso di ordinamento per più chiavi successive. 
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

void stampa(char datas[MAXLINES][MAX_WD_CHAR], int n);
int compareDates(char start[MAXCHAR], char end[MAXCHAR]);
int compareTimes(char start[MAXCHAR], char end[MAXCHAR]);
void ricercaPerPartenza(char datas[MAXLINES][MAX_WD_CHAR], int n, char start[MAXCHAR]);
void oridnamentoPerData(char datas[MAXLINES][MAX_WD_CHAR], int n);
void ordinamentoPerCodice(char datas[MAXLINES][MAX_WD_CHAR], int n);
void ordinamentoPerPartenza(char datas[MAXLINES][MAX_WD_CHAR], int n);
void ordinamentoPerArrivi(char datas[MAXLINES][MAX_WD_CHAR], int n);

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
            oridnamentoPerData(datas, n);
            stampa(datas, n);
            return;
        case r_code:
            ordinamentoPerCodice(datas, n);
            stampa(datas, n);
            return;
        case r_stazPar:
            ordinamentoPerPartenza(datas, n);
            stampa(datas, n);
            return;
        case r_stazArr:
            ordinamentoPerArrivi(datas, n);
            stampa(datas, n);
            return;
        case r_ricerca:
            printf("Inserire il nome della fermata di partenza che si vuole cercare: ");
            scanf(" %s", &start);
            ricercaPerPartenza(datas, n, start);
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

void stampa(char datas[MAXLINES][MAX_WD_CHAR], int n){
    for(int i = 0; i < n; i++)
        printf("%s", datas[i]);
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

int compareTimes(char start[MAXCHAR], char end[MAXCHAR]){
    int start_h, start_m, start_s;
    int end_h, end_m, end_s;

    sscanf(start, "%d:%d:%d", &start_h, &start_m, &start_s);
    sscanf(end, "%d:%d:%d", &end_h, &end_m, &end_s);

    if((end_h - start_h) == 0){
        if((end_m - start_m) == 0){
            return end_s - start_s;
        }else
            return end_m - start_s;
    }else
        return end_h - start_h;
}

void ricercaPerPartenza(char datas[MAXLINES][MAX_WD_CHAR], int n, char start[MAXCHAR]){
	int i = 0, index = -1;
    char code[MAXCHAR], startS[MAXCHAR], end[MAXCHAR], data[MAXCHAR], start_h[MAXCHAR], end_h[MAXCHAR];
    int rit;
	
	for(i = 0; i < n; i++){
        sscanf(datas[i], " %s %s %s %s %s %s %d", &code, &startS, &end, &data, &start_h, &end_h, &rit);
		if(strcmp(startS, start) == 0)
			printf("%s", datas[i]);
	}
}

// secondarie

void oridnamentoPerData(char datas[MAXLINES][MAX_WD_CHAR], int n){
    int i, j, l = 0, r = n - 1, flag = 1;
	char temp[MAX_WD_CHAR];

    char code[MAXCHAR], start[MAXCHAR], end[MAXCHAR], data1[MAXCHAR], data2[MAXCHAR], start_h1[MAXCHAR], start_h2[MAXCHAR], end_h[MAXCHAR];
    int rit;
	
	for(i = l; i < r && flag == 1; j++){
		flag = 0;
		for(j = l; j < r - i + l; j++){
            sscanf(datas[j], " %s %s %s %s %s %s %d", &code, &start, &end, &data1, &start_h1, &end_h, &rit);
            sscanf(datas[j+1], " %s %s %s %s %s %s %d", &code, &start, &end, &data2, &start_h2, &end_h, &rit);

			if(compareDates(data2, data1) > 0){
				flag = 1;
				strcpy(temp, datas[j]);
                strcpy(datas[j], datas[j+1]);
                strcpy(datas[j + 1], temp);
			}else if(compareDates(data2, data1) == 0 && compareTimes(start_h2, start_h1) > 0){
                flag = 1;
				strcpy(temp, datas[j]);
                strcpy(datas[j], datas[j+1]);
                strcpy(datas[j + 1], temp);
            }
		}
	} 
	return;
}

void ordinamentoPerCodice(char datas[MAXLINES][MAX_WD_CHAR], int n){
    int i, j, l = 0, r = n - 1, flag = 1;
	char temp[MAX_WD_CHAR];

    char code1[MAXCHAR], code2[MAXCHAR], start[MAXCHAR], end[MAXCHAR], data[MAXCHAR], start_h[MAXCHAR], end_h[MAXCHAR];
    int rit;
	
	for(i = l; i < r && flag == 1; j++){
		flag = 0;
		for(j = l; j < r - i + l; j++){
            sscanf(datas[j], " %s %s %s %s %s %s %d", &code1, &start, &end, &data, &start_h, &end_h, &rit);
            sscanf(datas[j+1], " %s %s %s %s %s %s %d", &code2, &start, &end, &data, &start_h, &end_h, &rit);

			if(strcmp(code1, code2) > 0){
				flag = 1;
				strcpy(temp, datas[j]);
                strcpy(datas[j], datas[j+1]);
                strcpy(datas[j + 1], temp);
			}
		}
	} 
	return;
}

void ordinamentoPerPartenza(char datas[MAXLINES][MAX_WD_CHAR], int n){
    int i, j, l = 0, r = n - 1, flag = 1;
	char temp[MAX_WD_CHAR];

    char code[MAXCHAR], start1[MAXCHAR], start2[MAXCHAR], end[MAXCHAR], data[MAXCHAR], start_h[MAXCHAR], end_h[MAXCHAR];
    int rit;
	
	for(i = l; i < r && flag == 1; j++){
		flag = 0;
		for(j = l; j < r - i + l; j++){
            sscanf(datas[j], " %s %s %s %s %s %s %d", &code, &start1, &end, &data, &start_h, &end_h, &rit);
            sscanf(datas[j+1], " %s %s %s %s %s %s %d", &code, &start2, &end, &data, &start_h, &end_h, &rit);

			if(strcmp(start1, start2) > 0){
				flag = 1;
				strcpy(temp, datas[j]);
                strcpy(datas[j], datas[j+1]);
                strcpy(datas[j + 1], temp);
			}
		}
	} 
	return;    
}

void ordinamentoPerArrivi(char datas[MAXLINES][MAX_WD_CHAR], int n){
    int i, j, l = 0, r = n - 1, flag = 1;
	char temp[MAX_WD_CHAR];

    char code[MAXCHAR], start[MAXCHAR], end1[MAXCHAR], end2[MAXCHAR], data[MAXCHAR], start_h[MAXCHAR], end_h[MAXCHAR];
    int rit;
	
	for(i = l; i < r && flag == 1; j++){
		flag = 0;
		for(j = l; j < r - i + l; j++){
            sscanf(datas[j], " %s %s %s %s %s %s %d", &code, &start, &end1, &data, &start_h, &end_h, &rit);
            sscanf(datas[j+1], " %s %s %s %s %s %s %d", &code, &start, &end2, &data, &start_h, &end_h, &rit);

			if(strcmp(end1, end2) > 0){
				flag = 1;
				strcpy(temp, datas[j]);
                strcpy(datas[j], datas[j+1]);
                strcpy(datas[j + 1], temp);
			}
		}
	} 
	return;      
}
