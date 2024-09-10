/*
Un file (sorgente.txt) contiene un testo composto da un numero indefinito di righe, di lunghezza
massima 200 caratteri ognuna. Un secondo file (dizionario.txt) contiene un elenco di coppie di
stringhe. Il file dizionario.txt è organizzato come segue:
• sulla prima riga è presente un numero intero e positivo S (≤ 30), che indica il numero di possibili
ricodifiche (sostituzioni) presenti nel dizionario
• seguono S coppie <ricodifica><originale> a rappresentare le sostituzioni possibili. Ogni
sostituzione <compresso> è nella forma $<intero>$
Lo scopo del programma è di ricodificare il primo file di testo andando a sostituire sequenze di caratteri
sulla base dei contenuti del secondo file. In caso di più sostituzioni possibili per una certa sottostringa,
il programma scelga la prima sostituzione trovata. Il risultato della ricodifica sia salvato su un terzo file
(ricodificato.txt).
*/

#include <stdio.h>
#include <string.h>

#define SOURCENAME "sorgente.txt"
#define DICTNAME "dizionario.txt"
#define OUTPUTNAME "ricodificato.txt"
#define MAXCHAR 200
#define MAXLENGTH 35
#define MAXDECODE 30

int main(int argc, char *argv[]){
    FILE *fin, *fout;
    char dict[MAXDECODE][MAXLENGTHFILENAME], word[MAXLENGTHFILENAME];
    int nVocab, decode[MAXDECODE];

    if((fin = fopen(DICTNAME, "r")) == NULL){
        printf("Impossibile aprire il file \"%s\"", DICTNAME);
        return -1;
    }

    fscanf(fin, "%d", &nVocab);
    for(int i = 0; i < nVocab && i < MAXDECODE; i++)
        fscanf(fin, " $%d$ %s ", &decode[i], &dict[i]);

    fclose(fin);

    if((fin = fopen(SOURCENAME, "r")) == NULL){
        printf("Impossibile aprire il file \"%s\"", SOURCENAME);
        return -1;
    }
    fout = fopen(OUTPUTNAME, "w");

    while(!feof(fin)){
        fscanf(fin, " %s ", &word);
        
    }

    fclose(fin);
    fclose(fout);

    return 0;
}
