/*
Si scriva un programma in grado di localizzare, all’interno di un generico testo, le occorrenze di ogni
parola che contiene una certa sequenza di caratteri. Le “parole” (nel testo) contengono unicamente
caratteri alfanumerici (identificati dalla funzione isalnum di ctype.h), più parole sono separate
da spazi o segni di punteggiatura (identificati dalle funzioni isspace e ispunct).
Il programma riceve in input:
• il file sequenze.txt: sulla prima riga contiene il numero totale di sequenze, al più 20, sulle
righe successive, una per riga, le sequenze da ricercare. La lunghezza delle singole sequenze è
limitata a massimo 5 caratteri. Si trascuri la differenza tra maiuscole e minuscole
• il file testo.txt: contiene il testo. Il numero di righe non è noto a priori. Si assuma che la
lunghezza di ogni riga sia al più pari a 200 caratteri. Si assuma inoltre che nessuna parola del
testo sia più lunga di 25 caratteri.
Il programma deve visualizzare, per ognuna delle “sequenze”, quali parole la contengono e dove si
trovano nel file. La posizione delle parole viene data contando le parole stesse a partire dall'inizio
del testo (si usi 1 per la prima parole, 2 per la seconda e così via). Ai fini dell'esercizio ci si limiti a
identificare e visualizzare solamente le prime 10 occorrenze per ogni sequenza.
*/

#include <stdio.h>
#include <string.h>

#define INPUTFILE "testo.txt"
#define SEQFILE "sequenze.txt"
#define MAXSEQNUMBER 20
#define MAXSEQCHAR 6

int readFile(char datas[MAXSEQNUMBER][MAXSEQCHAR], char filename[]);

int main(int argc, char *argv[]){
    FILE *fin;
    char seqs[MAXSEQNUMBER][MAXSEQCHAR];
    int n;

    n = readFile(seqs, SEQFILE);

    return 0;
}

int readFile(char datas[MAXSEQNUMBER][MAXSEQCHAR], char filename[]){
    FILE *fin = fopen(filename, "r");
    int n;

    if(fin == NULL)
        return -1;

    fscanf(fin, " %d ", &n);

    for(int i = 0; i < n && !feof(fin); i++)   
        fscanf(fin, "%s", &datas[i]);

    fclose(fin);

    return n;
}
