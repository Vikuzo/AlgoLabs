#define MAX_LINE_LENGTH 250
#define MAX_NAME_LENGTH 50
#define MAX_CODE_LENGTH 6

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

static key KEYget(item val);
static int KEYgrater(key k1, key k2);
static stats newStats(int hp, int mp, int atk, int def, int mag, int spr);
static item newItem(char *code, char *name, char *class, stats s);
static void ITEMdisplay(item i);

static link newNode(item val, link next);

static link sortListIns(link h, item val);

link insertANewCharacter(link h, char *code, char *name, char *class, int hp, int mp, int atk, int def, int mag, int spr);

link insertFromFile(link h, char *filename);

void listTravR(link h);
