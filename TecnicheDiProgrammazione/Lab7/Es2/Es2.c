/*
Si considerino i seguenti algoritmi di ordinamento per ordinare in maniera ascendente vettori di interi:
• Selection Sort
• Insertion Sort
• Shell Sort
Si scriva un programma in C che per ogni sequenza numerica acquisita da file (sort.txt) invochi
tutti gli algoritmi di ordinamento sopra indicati e stampi a video:
• il numero di scambi
• il numero di iterazioni del ciclo esterno
• per ogni passo del ciclo esterno il numero di iterazioni del ciclo interno
• il numero totale di iterazioni.
Il file sort.txt è caratterizzato dal seguente formato:
• sulla prima riga appare il numero S di sequenze numeriche
• seguono S righe nella forma <lunghezza><sequenza> dove <lunghezza> è un intero non
negativo (al massimo 100) a rappresentare la lunghezza della sequenza riportata su tale riga, e
<sequenza> sono <lunghezza> numeri separati da uno spazio.
*/

#include <stdio.h>

#define MAX_NVALUE 100
#define FILE_NAME_MAX_LENGTH 30

void selectionSort(int A[], int N);
void insertionSort(int A[], int N);
void shellSort(int A[], int N);

int main(int argc, char *argv[]){
    FILE *fin;
    char filename[FILE_NAME_MAX_LENGTH];
    int nSeq, nVal, values[MAX_NVALUE];

    printf("Inserire il nome del file da cui estrapolare i dati: ");
    scanf("%s", &filename);

    if((fin = fopen(filename, "r")) == NULL){
        printf("Impossibile aprire il file \"%s\".", filename);
        return -1;
    }

    fscanf(fin, "%d", &nSeq);

    for(int i = 0; i < nSeq; i++){
        fscanf(fin, "%d", &nVal);
        for(int j = 0; j < nVal && j < MAX_NVALUE; j++)
            fscanf(fin, "%d", &values[j]);
        // selectionSort(values, nVal);
        insertionSort(values, nVal);
        shellSort(values, nVal);
    }

    return 0;
}

void selectionSort(int A[], int N){
	int i, j, l = 0, r = N - 1, min;
	int temp, switches = 0, extFor = 0, intFor, totIter = 0;

    printf("Selection Sort:\n");

	for(i = l; i < r; i++){
		min = i;
        intFor = 0;
		for(j = i + 1; j <= r; j++){
			if(A[j] < A[min]){
				min = j;
			}
            intFor += 1;
		}
		if(min != i){
			temp = A[i];
			A[i] = A[min];
			A[min] = temp;
            switches += 1;
		}
        extFor += 1;
        printf("%d -> %d\n", extFor, intFor);
        totIter += intFor;
	}

    printf("Scambi: %d, iterazioni totali: %d\n\n", switches, (totIter + extFor));

	return;
}

void insertionSort(int A[], int N){
	int i, j, l = 0, r = N - 1, x;
    int switches = 0, extFor = 0, intFor, totIter = 0;

    printf("Insertion Sort:\n");

	for(i = l; i <= r; i++){
		x = A[i];
		j = i - 1;
        extFor += 1;
        intFor = 0;
		while(j >= l && x < A[j]){
			A[j + 1] = A[j];
			j--;
            switches += 1;
            intFor += 1;
		}
		A[j + 1] = x;
        switches += 1;
        totIter += intFor;

        printf("%d -> %d\n", extFor, intFor);
	} 

    printf("Scambi: %d, iterazioni totali: %d\n\n", switches, (totIter + extFor));
}

// con sequenza di Knuth
void shellSort(int A[], int N){
	int i, j, x, l = 0, r = N - 1, h = 1;
	while(h <= N/3){
		h = 3*h + 1;
	}
	
	while(h >= 1){
		for(i = l + h; i <= r; i++){
			j = i;
			x = A[i];
			while(j >= l + h && x < A[j - h]){
				A[j] = A[j - h];
				j -= h;
			}
			A[j] = x;
		}
		h = h/3;
	}
}
