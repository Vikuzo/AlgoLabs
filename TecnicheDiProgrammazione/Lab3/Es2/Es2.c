/*
E’ dato un file testo expr.txt in cui ogni riga contiene una espressione, composta unicamente da numeri
interi non negativi (quindi senza segno), simboli di operazioni aritmetiche (+, -, *, / e %) e parentesi
tonde aperte o chiuse.
Si scriva un programma che verifichi la correttezza sintattica delle espressioni scritte nel file, secondo
le regole seguenti:
1. Bilanciamento parentesi: le parentesi devono essere bilanciate, cioè il numero totale di parentesi
aperte deve coincidere con quello delle parentesi chiuse, e ogni parentesi chiusa deve corrispondere
a una precedente parentesi aperta.
2. Non ci possono essere spazi all’interno dei numeri, mentre sono ammessi spazi (da ignorare) in
qualunque altra posizione all’interno dell’espressione
3. Successione corretta tra operandi e operatori: ogni operazione è costituita da una sequenza di
almeno due operandi intercalati da operatori (simboli di operazione aritmetica) infissi. Un operando
può essere rappresentato da un numero oppure da una espressione (eventualmente un numero)
racchiusa tra parentesi.

In pratica, la regola 3 può essere verificata controllando che:
• Dopo una parentesi aperta può esserci solo un operando (una parentesi aperta oppure un
numero), quindi non può esserci un operatore.
• Dopo un operando (quindi dopo una parentesi chiusa o un numero) ci può essere solo un’altra
parentesi chiusa (se rispetta la regola 1), un operatore o la fine dell’espressione
• Dopo un operatore ci deve essere un operando (una parentesi aperta oppure un numero)

O in alternativa, la regola 3 può essere verificata controllando che:
• Prima di un operando (parentesi aperta o numero) può esserci solo una parentesi aperta, un
operatore, oppure l’inizio dell’espressione
• Prima di una parentesi chiusa ci può solo essere un operando (quindi una parentesi chiusa o un
numero)
• Prima di un operatore ci può solo essere un operando (una parentesi chiusa o un numero)

Quando incontra un errore in una espressione, il programma deve stampare un messaggio di errore (che
deve includere il numero di espressione contenente l’errore), ignorare il resto della riga e passare
all’espressione successiva. 
*/

#include <stdio.h>
#include <ctype.h>

#define FILENAME "expr.txt"

void checkExpressionCorrectness(FILE *fin);
int isOperator(char op);

int main(int argc, char* argv[]){
    FILE *fin;

    if((fin = fopen(FILENAME, "r")) == NULL){
        printf("Impossibile aprire il file \"%s\"", FILENAME);
        return -1;
    }

    checkExpressionCorrectness(fin);

    fclose(fin);

    return 0;
}

void checkExpressionCorrectness(FILE *fin){
    int l = 1, bracketBalance = 0;
    char currChar, prevChar;

    while(!feof(fin)){
        currChar = getc(fin);

        if(currChar != '\n' && currChar != EOF){

        }

        prevChar = currChar;
    }
}

int isOperator(char op){
    if(op == '+' || op == '-' || op == '*' || op == '/' || op == '%')
        return 0;

    return 1;
}