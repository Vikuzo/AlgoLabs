/*
Un file contiene un testo composto da un numero non noto di caratteri.
Lo scopo del programma è di ricodificare il testo, generando un secondo file, nel quale i caratteri sono
stati ricodificati secondo le regole seguenti:
I caratteri numerici sono ricodificati in questo modo:
    • I caratteri numerici (‘0’..’9’) sono ricodificati nel carattere numerico posto k posizioni più
    avanti, con k che, partendo da 0, viene incrementato ad ogni carattere numerico ricodificato
    (ATTENZIONE: gli incrementi sono effettuati in MODULO 10, cioè, arrivati a 9 si riparte da 0).
    Se ad esempio il file iniziasse con la riga: “Il numero 248 è pari”, il ‘2’ verrebbe ricodificato (k
    parte da 0) in ‘2’+0 = ‘2’ (k diventa 1), il ‘4’ in ‘4’+1 = ‘5’ (k diventa 2) e ‘8’ viene ricodificato
    in ‘8’+2 = ‘0’ (perché arrivati a ‘9’ si riparte da ‘0’).
I caratteri alfabetici sono invece ricodificati in questo modo:
    • Se un carattere alfabetico è preceduto da un carattere non alfabetico, resta inalterato
    • Se è preceduto da un carattere alfabetico (sia c0 il carattere precedente), il suo codice si sposta
    di h posizioni in avanti, nell’insieme dei caratteri alfabetici (con h = c0-‘A’, se c0 è maiuscolo,
    h=c0-‘a’, se c0 è minuscolo. L’incremento di h è modulo 26, cioè arrivati alla ‘z’ o ‘Z’
    (a seconda che il carattere ricodificato sia maiuscolo o minuscolo) si riparte da ‘a’ o ‘A’.
Il risultato della ricodifica sia salvato su un secondo file (I nomi dei file siano opportunamente acquisiti
da tastiera).

Si scrivano due funzioni, in grado di effettuare, rispettivamente, la codifica e la decodifica.
I prototipi delle funzioni siano:
    int codifica(FILE *fin, FILE *fout);
    int decodifica(FILE *fin, FILE *fout);
In caso di errore le funzioni ritornano come risultato 0, diversamente ritornano il numero di caratteri
scritto nel file in uscita. Il main permette all’utente di selezionare (in base a un opportuno input)
codifica oppure decodifica, apre i file quello in input e quello in output. chiama la funzione selezionata.
*/

#include <stdio.h>
#include <ctype.h>

int codifica(FILE *fin, FILE *fout);
int decodifica(FILE *fin, FILE *fout);
int menu();

int main(int argc, char* argv[]){
    return menu();
}

int codifica(FILE *fin, FILE *fout){
    char currChar, prevChar = '\0';
    int k = 0, h = 0, limit, numChar = 0; 

    if(fin == NULL || fout == NULL)
        return 0;
    
    while(!feof(fin)){
        currChar = getc(fin);
        
        if(currChar != EOF){
            if(isdigit(currChar)){
                if(currChar + k > 57)
                    putc((currChar + k - 10), fout);
                else
                    putc((currChar + k), fout);
                
                k++;
                if(k == 10)
                    k = 0;
            }else if(isalpha(currChar)){
                if(!isalpha(prevChar))
                    putc(currChar, fout);
                else{
                    if(islower(prevChar))
                        h += prevChar - 'a';
                    else
                        h += prevChar - 'A';

                    if(h > 25)
                        h -= 26;

                    if(islower(currChar))
                        limit = 122;
                    else
                        limit = 90;

                    if(currChar + h > limit)
                        putc((currChar + h - 26), fout);
                    else
                        putc((currChar + h), fout);
                }
            }else{
                putc(currChar, fout);
                h = 0; k = 0;    
            }
        }

        numChar += 1;
        prevChar = currChar;
    }

    return numChar;
}

int decodifica(FILE *fin, FILE *fout){
    char currChar, prevChar = '\0', originalChar;
    int k = 0, h = 0, limit, numChar = 0; 

    if(fin == NULL || fout == NULL)
        return 0;
    
    while(!feof(fin)){
        currChar = getc(fin);
        
        if(currChar != EOF){
            if(isdigit(currChar)){
                if(currChar - k < 48)
                    putc((currChar - k + 10), fout);
                else
                    putc((currChar - k), fout);
                
                k++;
                if(k == 10)
                    k = 0;
            }else if(isalpha(currChar)){
                if(!isalpha(prevChar)){
                    putc(currChar, fout);
                    originalChar = currChar;
                }else{
                    if(islower(prevChar))
                        h += originalChar - 'a';
                    else
                        h += originalChar - 'A';

                    if(h > 25)
                        h -= 26;

                    if(islower(currChar))
                        limit = 97;
                    else
                        limit = 65;

                    if(currChar - h < limit)
                        originalChar = currChar - h + 26;
                    else
                        originalChar = currChar - h;

                    putc(originalChar, fout);
                }
            }else{
                putc(currChar, fout);
                k = 0;
                h = 0;
            }
        }

        numChar += 1;
        prevChar = currChar;
    }

    return numChar;
}

int menu(){
    FILE *fin, *fout;
    int choice = 0, n;
    char name[100];

    while(choice == 0){
        printf("1) Per codificare un file;\n");
        printf("2) Per decodificare un file;\n");
        printf("Inserire il valore associato all'azione che si vuole svolgere: ");
        scanf(" %d", &choice);

        switch(choice){
            case 1:
                printf("Inserire il nome del file sorgente: ");
                scanf(" %s", &name);
                fin = fopen(name, "r");

                printf("Inserire il nome del file di destinazione: ");
                scanf(" %s", &name);
                fout = fopen(name, "w");

                n = codifica(fin, fout);

                if(n == 0)
                    printf("Qualcosa e' andato storto.\n\n");
                else
                    printf("I caratteri scritti sono: %d\n\n", n);

                fclose(fin);
                fclose(fout);
                
                choice = 0;
                break;
            case 2:
                printf("Inserire il nome del file sorgente: ");
                scanf(" %s", &name);
                fin = fopen(name, "r");

                printf("Inserire il nome del file di destinazione: ");
                scanf(" %s", &name);
                fout = fopen(name, "w");

                n = decodifica(fin, fout);

                if(n == 0)
                    printf("Qualcosa e' andato storto.\n\n");
                else
                    printf("I caratteri scritti sono: %d\n\n", n);

                fclose(fin);
                fclose(fout);
                
                choice = 0;
                break;
            default:
                printf("Chiusura del programma in corso...");
                choice = 1;
                break;
            }
    }

    return 0;
}