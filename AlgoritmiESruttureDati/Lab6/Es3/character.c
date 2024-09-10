#include <stdio.h>
#include <string.h>
#include "character.h"

typedef struct Character character, *link;
typedef struct Statistics stats;
typedef struct Key key;
typedef struct Item item;

struct Key{
    char code[MAX_CODE_LENGTH];
};

struct Statistics{
    unsigned int hp, mp, atk, def, mag, spr;
};

struct Item{
    char code[MAX_CODE_LENGTH], name[MAX_NAME_LENGTH], class[MAX_NAME_LENGTH];
    stats s;
};

struct Character{
    item val;
    link next;
};

static key KEYget(item val){
    key k;
    strcpy(k.code, val.code);
    return k;
}

static int KEYgrater(key k1, key k2){
    return strcmp(k1.code, k2.code);
}

static stats newStats(int hp, int mp, int atk, int def, int mag, int spr){
    stats s; 
    s.atk = atk;
    s.def = def;
    s.hp = hp;
    s.mag = mag;
    s.mp = mp;
    s.spr = spr;
    return s;
}

static item newItem(char *code, char *name, char *class, stats s){
    item i;
    strcpy(i.code, code);
    strcpy(i.name, name);
    strcpy(i.class, class);
    i.s = s;
    return i;
}

static void ITEMdisplay(item i){
    printf("%s %s %s %d %d %d %d %d %d\n", i.code, i.name, i.class, i.s.hp, i.s.mp, i.s.atk, i.s.def, i.s.mag, i.s.spr);
}

static link newNode(item val, link next){
	link x = malloc(sizeof *x);
	if(x == NULL) 
        return NULL;
	else{
		x -> val = val;
		x -> next = next;
	}
	
	return x;
}

static link sortListIns(link h, item val){
    link x, p;
	key k = KEYget(val);
	if(h == NULL || KEYgreater(KEYget(h -> val), k)) 
        return newNode(val, h);

	for(x = h -> next, p = h; x != NULL && KEYgreater(k, KEYget(x -> val)); p = x, x = x -> next);
	p -> next = newNode(val, x);
	return h;
}

link insertANewCharacter(link h, char *code, char *name, char *class, int hp, int mp, int atk, int def, int mag, int spr){
    stats s = newStats(hp, mp, atk, def, mag, spr);
    item i = newItem(code, name, class, s);
    return sortListIns(h, i);
}

link insertFromFile(link h, char *filename){
    FILE *fin = fopen(filename, "r");
    char s[MAX_LINE_LENGTH], code[MAX_CODE_LENGTH], name[MAX_NAME_LENGTH], class[MAX_NAME_LENGTH];
    int hp, mp, atk, def, mag, spr;

    if(fin == NULL){
        printf("Impossibile aprire il file \"%s\"", filename);
        return NULL;
    }

    while(!feof(fin)){
        fgets(s, MAX_LINE_LENGTH, fin);
        sscanf(s, "%s %s %s %d %d %d %d %d %d", &code, &name, &class, &hp, &mp, &atk, &def, &mag, &spr);
        insertANewCharacter(h, code, name, class, hp, mp, atk, def, mag, spr);
    }

    return h;
}

void listTravR(link h){
	if(h == NULL) return;
	ITEMdisplay(h -> val);
	listTravR(h -> next);
}
