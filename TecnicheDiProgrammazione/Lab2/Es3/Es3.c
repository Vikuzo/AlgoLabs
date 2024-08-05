/*
Un file (sorgente.txt) contiene un testo composto da un numero indefinito di righe.
Notare che il testo NON contiene il carattere ‘$’.
Lo scopo del programma è di ricodificare il testo sostituendo sequenze di caratteri ripetuti da 2 a 9
volte (ATTENZIONE: il numero non comprende il primo carattere, cioè AA contiene una ripetizione,
BBB due ripetizioni, ecc.) con la terna di caratteri <carattere ripetuto>$<numero di ripetizioni>
(ATTENZIONE: per il <numero di ripetizioni> è sufficiente un carattere). Se un carattere fosse
ripetuto più di 9 volte, le ripetizioni sarebbero spezzate in più intervalli.
Ad esempio, la sequenza di caratteri “il numero 1000000 e’ grande”, viene compressa in “il numero
10$5 è grande”. La sequenza, “ci sono 15 = ripetuti: =============== e 4 punti….” viene
ricodificata in: “ci sono 15 = ripetuti: =$9=$4 e 4 punti.$3”
Il risultato della ricodifica sia salvato su un secondo file (compresso.txt).
Esempio:
Il contenuto del file sorgente.txt è:
 Partenza      Destinazione    Costo
   Parigi          New York     1000
     Roma            Londra      700
   Sidney       Los Angeles     2222
Il file di uscita ricodificato.txt conterrà:
    Partenza $5Destinazione $3Costo
    $2Parigi $9New York $410$2
    $4Roma $9 Londra $5700
    $2Sidney $6Los Angeles $42$3
Si scrivano due funzioni, in grado di effettuare, rispettivamente, la compressione e la decompressione. I
prototipi delle funzioni siano
    - int comprimi(FILE *fin, FILE *fout);
    - int decomprimi(FILE *fin, FILE *fout);
In caso di errore le funzioni ritornano come risultato 0, diversamente ritornano il numero di caratteri
scritto nel file in uscita. Il main permette all’utente di selezionare (in base a un opportuno input)
codifica oppure decodifica.
Si consiglia di usare un terzo file per il testo de-compresso (evitando così di sovrascrivere, perdendolo,
il file originale sorgente.txt)
*/

#include <stdio.h>

int comprimi(FILE *fin, FILE *fout);
int decomprimi(FILE *fin, FILE *fout);
int menu();

int main(int argc, char* argv[]){
    return menu();
}

int comprimi(FILE *fin, FILE *fout){
    char currChar, prevChar = '\0';
    int counter = 0, flag = 0, numChar = 0;

    while(!feof(fin)){
        currChar = getc(fin);

        if(currChar != EOF){
            if(currChar == prevChar){
                if(counter == 9)
                    flag = 1;
                else
                    counter += 1;
            }else if(counter > 0)
                flag = 1;
            else
                putc(currChar, fout);

            if(flag == 1){
                if(counter != 1){
                    putc('$', fout);
                    putc((counter + 48), fout);
                    putc(currChar, fout);
                }else{
                    putc(prevChar, fout);
                    putc(currChar, fout);
                }

                counter = 0;
                flag = 0;
            }

            numChar += 1;
        }
        
        prevChar = currChar;
    }

    return numChar;
}

int decomprimi(FILE *fin, FILE *fout){
    int currChar, prevChar, lastChar, flag = 0, numChar = 0;

    while(!feof(fin)){
        currChar = getc(fin);
        
        if(currChar != EOF && currChar != '$'){    
            if(prevChar == '$')
                flag = 1;
            else{
                putc(currChar, fout);
                lastChar = currChar;
            }

            numChar += 1;
        }

        if(flag == 1){
            for(int i = 0; i < (currChar - 48); i++)
                putc(lastChar, fout);
            flag = 0;
            numChar += (currChar - 48);
        }

        prevChar = currChar;
    }

    return numChar;
}

int menu(){
    FILE *fin, *fout;
    int choice = 0, n;

    while(choice == 0){
        printf("1) Per comprimere il file sorgente.txt;\n");
        printf("2) Per decomprimere il file compresso.txt;\n");
        printf("Inserire il valore associato all'azione che si vuole svolgere: ");
        scanf(" %d", &choice);

        switch(choice){
            case 1:
                if((fin = fopen("sorgente.txt", "r")) == NULL){
                    printf("Impossibile trovate il file \"sorgente.txt\"");
                    return -1;
                }

                fout = fopen("compresso.txt", "w");

                n = comprimi(fin, fout);

                if(n == 0)
                    printf("Qualcosa e' andato storto.\n\n");
                else
                    printf("I caratteri scritti sono: %d\n\n", n);

                fclose(fin);
                fclose(fout);
                
                choice = 0;
                break;
            case 2:
                if((fin = fopen("compresso.txt", "r")) == NULL){
                    printf("Impossibile trovate il file \"compresso.txt\"");
                    return -1;
                }

                fout = fopen("de-compresso.txt", "w");

                n = decomprimi(fin, fout);

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