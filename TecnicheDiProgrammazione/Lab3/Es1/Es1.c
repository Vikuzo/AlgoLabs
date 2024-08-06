/*
E’ dato un file testo, contenente solo caratteri alfabetici, numerici, segni di punteggiatura (. , ; : ! ?),
spazi e a-capo. Si vuole generare un secondo file contenente il testo, letto dal primo file e trasformato
nel modo seguente:
- Sostituire le cifre numeriche con il carattere '*'.
- Inserire uno spazio dopo ogni segno di punteggiatura, a meno che questo non sia già seguito da uno
spazio o un a-capo.
- Il primo carattere alfabetico successivo a un punto, punto esclamativo o interrogativo deve essere
maiuscolo; se non lo è, trasformarlo in maiuscolo (anche se tra la punteggiatura e il carattere
alfabetico ci sono uno o più spazi o a capo).
- Le righe del testo devono essere al massimo di 25 caratteri (a-capo escluso). Se sono più lunghe
vanno troncate (anche a metà di una parola) aggiungendo un a-capo esattamente dopo il
venticinquesimo carattere.
- Al termine di ogni riga vanno aggiunti, prima dell’a-capo, eventuali spazi per raggiungere i 25
caratteri.
- Ogni riga deve terminare con il numero di caratteri del file originale trascritti nella riga, nel
formato: " | c:%d \n".
I nomi dei file sono costanti (il primo file è input.txt, il secondo testo.txt) e definiti con #define (es.
#define filein "input.txt"). 
*/

#include <stdio.h>
#include <ctype.h>

#define FIN_NAME "input.txt"
#define FOUT_NAME "testo.txt"

void writeChar(FILE *fin, FILE *fout);
int ispuncttoupper(char punct);

int main(int argc, char* argv[]){
    FILE *fin, *fout;

    if((fin = fopen(FIN_NAME, "r")) == NULL){
        printf("Impossibile aprire il file \"%s\"", FIN_NAME);
        return -1;
    }

    fout = fopen(FOUT_NAME, "w");

    writeChar(fin, fout);

    fclose(fin);
    fclose(fout);

    return 0;
}

void writeChar(FILE *fin, FILE *fout){
    char currChar, prevChar = '\0', lastPunct;
    int n = 0, readChar = 0;

    while(!feof(fin)){
        currChar = getc(fin);

        if(ispunct(prevChar) && prevChar != '\n' && !ispunct(currChar)){
            if(!isspace(currChar)){
                putc(' ', fout);
                n += 1;
            }
            
            if(n == 25){
                fprintf(fout, "| c:%d \n", readChar);
                n = 0;
                readChar = 0;
            }

            lastPunct = prevChar;
        }

        if(currChar == '\n' || currChar == EOF){
            n += 1;
            if(currChar != EOF)
                readChar += 1;
            for(int i = 25 - n; i > -1; i--)
                putc(' ', fout);
            fprintf(fout, "| c:%d \n", readChar);
            n = 0;
            readChar = 0;
        }else if(isdigit(currChar)){
            putc('*', fout);
            n += 1;
            readChar += 1;
        }else if(ispuncttoupper(lastPunct) == 0 && islower(currChar)){
            putc((currChar - 32), fout);
            lastPunct = ' ';    
            n += 1;
            readChar += 1;
        }else{
            putc(currChar, fout);
            n += 1;
            readChar += 1;
        }

        if(n == 25){
            fprintf(fout, "| c:%d \n", readChar);
            n = 0;
            readChar = 0;
        }

        prevChar = currChar;
    }
}

int ispuncttoupper(char punct){
    if(punct == '.' || punct == '?' || punct == '!')
        return 0;
    
    return 1;
}