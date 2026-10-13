// FIXME: flytta struct
typedef struct merch merch_t;

struct merch
{
    char *name;
    char *desc;
    int price; // FIXME: size_t istället? 
};


merch_t add_merch(char *name, char *desc, int price)
{
    (void) name;
    (void) desc;
    (void) price;
}

void list_merch()