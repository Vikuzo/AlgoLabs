#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "Anag.txt"
#define FILENAME_W "Records.txt"
#define MAX_LINE_LEN 400
#define MAX_WORD_LEN 50

typedef struct Item item;
typedef struct Node node, *link;

typedef enum {r_stampa, r_ins, r_insM, r_ricerca, r_canc, r_cancD, r_fine} comando_e;

struct Item{
    char birthDate[MAX_WORD_LEN];
    char code[MAX_WORD_LEN], name[MAX_WORD_LEN], surname[MAX_WORD_LEN], address[MAX_WORD_LEN], city[MAX_WORD_LEN];
    int cap;
};

struct Node{
    item val;
    link next;
};

//funzioni di servizio
void printRecords(link h);
int compareDates(char start[MAX_WORD_LEN], char end[MAX_WORD_LEN]);

link newNode(item val, link next);
link sortLisIns(link h, item val);


void menu(link *h, comando_e comm);
comando_e getCommand();

// funzioni principali
item sortListSearch(link h, char *code);
item sortListDel(link *h, char *code);
void fprintRecords(link h);
int readFile(FILE *fin, link *h);


int main(int argc, char *argv[]){
    FILE *fin = fopen(FILENAME, "r");
    comando_e choice = r_stampa;
    link h = NULL;
    int n;

    n = readFile(fin, &h);
    if(n == -1){
        printf("Impossibile aprire il file \"%s\".", FILENAME);
        return -1;
    }

    fclose(fin);

    while(choice != r_fine){
        choice = getCommand();
        menu(&h, choice);
    }

    return 0;
}

// funzioni di servizio

int compareDates(char start[MAX_WORD_LEN], char end[MAX_WORD_LEN]){
    int start_g, start_m, start_a;
    int end_g, end_m, end_a;

    sscanf(start, "%d/%d/%d", &start_g, &start_m, &start_a);
    sscanf(end, "%d/%d/%d", &end_g, &end_m, &end_a);


    if((end_a - start_a) == 0){
        if((end_m - start_m) == 0){
            return end_g - start_g;
        }else
            return end_m - start_m;
    }else
        return end_a - start_a;
}

link newNode(item val, link next){
    link x = (link)malloc(sizeof(*x));
    if(x == NULL) return NULL;
    else{
        x -> val = val;
        x -> next = next;
    }

    return x;
}

link sortLisIns(link h, item val){
    link x, p;
    
    if(h == NULL || compareDates(val.birthDate, h->val.birthDate) > 0)
        return newNode(val, h);
    
    for(x = h -> next, p = h; x != NULL && compareDates(val.birthDate, x->val.birthDate) <= 0; p = x, x = x->next);
    p -> next = newNode(val, x);
    return h;
}

void menu(link *h, comando_e comm){
    FILE *fin;
    item val;
    link x;
    char filename[MAX_WORD_LEN], code[MAX_WORD_LEN], start[MAX_WORD_LEN], end[MAX_WORD_LEN];

    switch(comm){
        case r_stampa:
            fprintRecords(*h);
            return;
        case r_ins:
            printf("Inserire il nuovo record: ");
            scanf(" %s %s %s %s %s %s %d", &val.code, &val.name, &val.surname, &val.birthDate, &val.address, &val.city, &val.cap);
            *h = sortLisIns(*h, val);
            printRecords(*h);
            return;
        case r_insM:
            printf("Inserire il nome del file da cui prendere i nuovi record da inserire: ");
            scanf(" %s", &filename); fin = fopen(filename, "r");

            readFile(fin, h);
            fclose(fin);
            printRecords(*h);

            return;
        case r_ricerca:
            printf("Inserire il codice dell'elemento da cercare: ");
            scanf(" %s", &code);
            val = sortListSearch(*h, code);
            if(strcmp(val.code, "A0000") == 0) printf("Nessun elemento con codice %s trovato\n", code);
            else printf("%s %s %s %s %s %s %d\n", val.code, val.name, val.surname, val.birthDate, val.address, val.city, val.cap);
            return;
        case r_canc:
            printf("Inserire il codice dell'elemento da eliminare: ");
            scanf(" %s", &code);
            val = sortListDel(h, code);
            if(strcmp(val.code, "A0000") == 0) printf("Nessun elemento con codice %s trovato\n", code);
            else printf("%s %s %s %s %s %s %d e' stato eliminato\n", val.code, val.name, val.surname, val.birthDate, val.address, val.city, val.cap);
            return;
        case r_cancD:
            printf("Inserire le due date sulle quali basare l'eliminazione dei record: ");
            scanf(" %s %s", &start, &end);

            for(x = *h; x != NULL; x = x->next){
                if(compareDates(start, x->val.birthDate) >= 0 && compareDates(x->val.birthDate, end) >= 0){
                    val = sortListDel(h, x->val.code);
                    printf("%s %s %s %s %s %s %d e' stato eliminato\n", val.code, val.name, val.surname, val.birthDate, val.address, val.city, val.cap);
                }
            }

            return;
        case r_fine:
            printf("Chiusura del programma in corso...");
            return;
        default:
            printf("\n\nComando inserito invalido.\n\n");
            return;
    }
}

comando_e getCommand(){
    char choice[10];

    printf("Fra [] e' indicato il comando correlato:\n");
    printf("1. Stampare tutti i record su file \"%s\" [print].\n", FILENAME_W);
    printf("2. Inserire un nuovo elemento da tastiera [insert].\n");
    printf("3. Inserire molteplici elementi da tastiera [insertM].\n");
    printf("4. Ricercare un elemento attraverso il codice [search].\n");
    printf("5. Eliminare un elemento attraverso il codice [delete].\n");
    printf("6. Eliminare molteplici elementi compresi fra due date [deleteM].\n");
    printf("7. Terminare il processo [stop].\n");
    printf("Inserire il numero corrispondente al comando che su vuole eseguire: ");
    scanf("%10s", &choice);

    if(strcmp(choice, "print") == 0)
        return r_stampa;
    else if(strcmp(choice, "insert") == 0)
        return r_ins;
    else if(strcmp(choice, "insertM") == 0)
        return r_insM;
    else if(strcmp(choice, "search") == 0)
        return r_ricerca;
    else if(strcmp(choice, "delete") == 0)
        return r_canc;
    else if(strcmp(choice, "deleteM") == 0)
        return r_cancD;
    else if(strcmp(choice, "stop") == 0)
        return r_fine;

    return -1;
}

void printRecords(link h){
    link x = h;
    
    // printf("%s %s %s %s %s %s %d\n\n", h->val.code, h->val.name, h->val.surname, h->val.birthDate, h->val.address, h->val.city, h->val.cap);

    for(; x != NULL; x = x -> next)
        printf("%s %s %s %s %s %s %d\n", x->val.code, x->val.name, x->val.surname, x->val.birthDate, x->val.address, x->val.city, x->val.cap);
}


// funzioni principali

item sortListSearch(link h, char *code){
    link x;
    item voidItem; strcpy(voidItem.code, "A0000");

    for(x = h; x != NULL && strcmp(x->val.code, code) != 0; x = x -> next);

    if(x == NULL)
        return voidItem;
    return x->val; 
}

item sortListDel(link *h, char *code){
    link x, p;
    item i; strcpy(i.code, "A0000");

    if(*h == NULL) return i;
    for(x = *h, p = NULL; x != NULL && strcmp(x->val.code, code) != 0; p = x, x = x->next);
    
    if(x == *h) *h = x->next;
    else p -> next = x -> next;

    if(x != NULL)
        i = x->val;
    free(x);

    return i;
}

void fprintRecords(link h){
    FILE *fout = fopen(FILENAME_W, "w");
    link x = h;

    for(; x != NULL; x = x -> next)
        fprintf(fout, "%s %s %s %s %s %s %d\n", x->val.code, x->val.name, x->val.surname, x->val.birthDate, x->val.address, x->val.city, x->val.cap);
    fclose(fout);
}

int readFile(FILE *fin, link *h){
    item it;
    char line[MAX_LINE_LEN];
    int n = 0;

    if(fin == NULL)
        return -1;

    while(!feof(fin)){
        fgets(line, MAX_LINE_LEN, fin);
        sscanf(line, "%s %s %s %s %s %s %d ", &it.code, &it.name, &it.surname, &it.birthDate, &it.address, &it.city, &it.cap);
        // printf("%s %s %s %s %s %s %d \n", it.code, it.name, it.surname, it.birthDate, it.address, it.city, it.cap);
        *h = sortLisIns(*h, it);
        n++;
    }

    return n;
}

