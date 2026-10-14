#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "utils.h"
#include <time.h>

void print_item(item_t *item)
{
    printf("Name: %s\n", item->namn);
    printf("Desc: %s\n", item->beskrivning);
    // check for price
    int krona = (item->pris / 100);
    int ore = item->pris % 100;
    printf("Price: %d.%d\n", krona, ore);
    printf("Shelf: %s\n", item->id);
}

item_t make_item(char *namn, char *beskrivning, int pris, char *id) {

        item_t item = {
            .namn = namn,
            .beskrivning = beskrivning,
            .pris = pris,
            .id = id};
        return item;
}

item_t input_item(void)
{
    char *a = ask_question_string("Varunamn:");
    char *b = ask_question_string("Beskrivning:");
    int c = ask_question_int("Pris:");
    char *d = ask_question_shelf("ID:");

    return make_item(a, b, c, d);
}

char *magick(char *array1[], char *array2[], char *array3[], int size)
{

    char buf[255];
    int randint1 = random() % size;
    int randint2 = random() % size;
    int randint3 = random() % size;
    int pos = 0;

    size_t lenarr1 = strlen(array1[randint1]);
    size_t lenarr2 = strlen(array2[randint2]);
    size_t lenarr3 = strlen(array3[randint3]);

    for (int i = 0; i < lenarr1; i++)
    {
        buf[i] = array1[randint1][i];
        pos++;
    }

    buf[pos] = '-';
    pos++;

    for (int j = 0; j < lenarr2; j++)
    {
        buf[pos] = array2[randint2][j];
        pos++;
    }

    buf[pos] = ' ';
    pos++;

    for (int k = 0; k < lenarr3; k++)
    {
        buf[pos] = array3[randint3][k];
        pos++;
    }
    buf[pos] = '\0';

    return strdup(buf);
}

void list_db(item_t *items, int *no_items)
{
    int counter = 1;
    for (int i = 0; i < *no_items; i++)
    {
        printf("%d. %s\n", counter, items[i].namn);
        counter++;
    }
}

void edit_db(item_t *items, int *size)
{

    bool result = false;
    int replace = -1;

    while (result != true)
    {

        list_db(items, size);
        replace = ask_question_int("Vilken vara vill du editera?\n");
        if (replace > 0 && replace <= *size)
        {
            result = true;
        }
        else
        {
            printf("Ogiltig vara");
        }
    }
    replace = replace - 1;
    printf("Du vill editera följande vara:\n");
    print_item(&items[replace]);
    printf(" ");
    item_t new_item = input_item();
    items[replace] = new_item;
}

void add_item_to_db(item_t *db, int *db_siz)
{
    item_t new_item = input_item();
    db[*db_siz] = new_item;
    printf("=====One new item added to the database=====\n");
    *db_siz = *db_siz + 1;
}

void remove_item_from_db(item_t *db, int *db_siz)
{
    bool result = false;
    int replace = -1;
    while (result != true)
    {
        list_db(db, db_siz);
        replace = ask_question_int("Vilken vara vill du ta bort?\n");
        if (replace > 0 && replace <= *db_siz)
        {
            result = true;
        }
        else
        {
            printf("Ogiltig vara");
        }
    }
    replace = replace - 1;
    for (; replace < *db_siz - 1; replace++)
    {
        db[replace] = db[replace + 1];
    }
    (*db_siz)--;
}

void event_loop(item_t *db, int *db_siz)
{
    clear_input_buffer();
    bool quit = false;
    while (quit != true)
    {
        printf("\nTryck Enter för att fortsätta...");
        getchar();

        char result = ask_question_menu("\n[L]ägga till en vara\n"
                                        "[T]a bort en vara\n"
                                        "[R]edigera en vara\n"
                                        "Ån[g]ra senaste ändringen\n"
                                        "Lista [h]ela varukatalogen\n"
                                        "[A]vsluta");

        if (result == 'L')
        {
            add_item_to_db(db, db_siz);
        }
        if (result == 'T')
        {
            remove_item_from_db(db, db_siz);
        }
        if (result == 'R')
        {
            edit_db(db, db_siz);
        }
        if (result == 'G' || result == 'g')
        {
            printf("Not yet implemented!");
        }
        if (result == 'H' || result == 'h')
        {
            list_db(db, db_siz);
        }
        else if (result == 'A')
        {
            quit = true;
        }
    }
    printf("Exiting loop");
}

int main(int argc, char *argv[])
{
    char *array1[] = {"Laser", "Polka", "Extra"};
    char *array2[] = {"förnicklad", "smakande", "ordinär"};
    char *array3[] = {"skruvdragare", "kola", "uppgift"};

    if (argc < 2)
    {
        printf("Usage: %s number\n", argv[0]);
    }
    else
    {
        item_t db[16];  // Array med plats för 16 varor
        int db_siz = 0; // Antalet varor i arrayen just nu

        int items = atoi(argv[1]); // Antalet varor som skall skapas

        if (items > 0 && items <= 16)
        {
            for (int i = 0; i < items; ++i)
            {
                // Läs in en vara, lägg till den i arrayen, öka storleksräknaren
                item_t item = input_item();
                db[db_siz] = item;
                ++db_siz;
            }
        }
        else
        {
            puts("Sorry, must have [1-16] items in database.");
            return 1; // Avslutar programmet!
        }

        for (int i = db_siz; i < 16; ++i)
        {
            char *name = magick(array1, array2, array3, 3); // TODO: Lägg till storlek
            char *desc = magick(array1, array2, array3, 3); // TODO: Lägg till storlek
            int price = random() % 200000;
            char shelf[] = {random() % ('Z' - 'A') + 'A',
                            random() % 10 + '0',
                            random() % 10 + '0',
                            '\0'};
            item_t item = make_item(name, desc, price, strdup(shelf));

            db[db_siz] = item;
            ++db_siz;
        }

        // Skriv ut innehållet
        // list_db(db ,db_siz);

        // edit_db(db, db_siz);

        // list_db(db ,db_siz);

        // remove_item_from_db(db, &db_siz);

        // list_db(db, db_siz);

        event_loop(db, &db_siz);
    }
    return 0;
}
