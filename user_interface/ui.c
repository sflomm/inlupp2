#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "../business_logic/webstore_backend.h"
#include "../business_logic/webstore_types.h"
#include "../generic_types/hash_table_iterator.h"
#include "../generic_types/linked_list.h"
#include "../generic_types/list_iterator.h"
#include "../generic_types/utils.h"

static int compare_names(const void *a, const void *b)
{
  const char *name_a = *(char * const *)a;
  const char *name_b = *(char * const *)b;
  return strcmp(name_a, name_b);
}

static void warehouse_list_merch(warehouse_t *wh)
{
  ioopm_hash_table_t *merch_ht = wh->merch_ht;
  size_t total_amount_of_merch = merch_ht->size;

  if (total_amount_of_merch == 0)
  {
    puts("No merchandise in the warehouse.\n");
    return;
  }

  // collect all keys into an array
  char **names = calloc(total_amount_of_merch, sizeof(char *));
  ioopm_hash_table_iterator_t *merch_it = ioopm_hash_table_iterator_create(merch_ht);
  size_t count = 0;

  while (!ioopm_hash_table_iterator_at_end(merch_it) && count < total_amount_of_merch)
  {
    names[count++] = ioopm_hash_table_iterator_current_key(merch_it).s;
    ioopm_hash_table_iterator_advance(merch_it);
  }
  ioopm_hash_table_iterator_destroy(merch_it);

  // sort alphabetically
  qsort(names, count, sizeof(char *), compare_names);

  // print in sorted order, 20 at a time
  for (size_t i = 0; i < count; i++)
  {
    printf("%zu. %s\n", i + 1, names[i]);

    if ((i + 1) % 20 == 0 && i + 1 < count)
    {
      char *choice = ask_question_string("Continue? [Y/N] ");
      bool stop = (strcmp(choice, "N") == 0 || strcmp(choice, "n") == 0);

      if (stop)
      {
        puts("Returning to main menu...");
        break;
      }
    }
  }

  free(names);
  puts("");
}

static int compare_shelves(const void *a, const void *b)
{
  const shelf_t *shelf_a = *(shelf_t * const *)a;
  const shelf_t *shelf_b = *(shelf_t * const *)b;
  return strcmp(shelf_a->shelf, shelf_b->shelf);
}

/// list all storage locations for particular merch along with the quantities stored on each location
/// prints 20 merch at a time
static void warehouse_show_stock(warehouse_t *wh, char *key)
{
  merch_t *merch = warehouse_find_merch(wh, key);

  if (merch == NULL)
  {
    printf("No merchandise named %s exists.\n\n", key);
    return;
  }

  size_t size = ioopm_list_size(merch->locs);

  if (size == 0)
  {
    printf("%s is not stored on any shelf.\n\n", key);
    return;
  }

  // collect all shelves into an array
  shelf_t **shelves = calloc(size, sizeof(shelf_t *));
  ioopm_list_iterator_t *it = ioopm_list_iterator_create(merch->locs);
  size_t count = 0;

  while (!ioopm_list_iterator_at_end(it) && count < size)
  {
    shelves[count++] = ioopm_list_iterator_current(it).p;
    ioopm_list_iterator_advance(it);
  }
  ioopm_list_iterator_destroy(it);

  // sort alphabetically
  qsort(shelves, count, sizeof(shelf_t *), compare_shelves);

  for (size_t i = 0; i < count; i++)
  {
    printf("Shelf: %s. Stock: %zu\n", shelves[i]->shelf, shelves[i]->quant);
  }
  puts("");
  free(shelves);
}

static void add_merch(warehouse_t *warehouse)
{
    char *name = ask_question_string("Name: ");
    char *description = ask_question_string("Description: ");
    int price = ask_question_int("Price (SEK): ");
    printf("Do you want to add:\nName: %s\nDescription: %s\nPrice: %d\n", name, description, price);
    char *choice = ask_question_string("Y/N? ");
    if (strcmp(choice, "Y") == 0 || strcmp(choice, "y") == 0) warehouse_add_merch(warehouse, name, description, price);
    puts("");
}

static void list_merch(warehouse_t *warehouse)
{
    warehouse_list_merch(warehouse); 
}

static void remove_merch(warehouse_t *warehouse)
{
    char *merch = ask_question_string("Remove: ");
    if (warehouse_find_merch(warehouse, merch) == NULL)
    {
        printf("Merch %s not found, try again\n\n", merch);
        return;
    }
    printf("Do you want to remove %s?\n", merch);
    char *choice_d = ask_question_string("Y/N? ");
    if (strcmp(choice_d, "Y") == 0 || strcmp(choice_d, "y") == 0)
    {
        bool removed = warehouse_remove_merch(warehouse, merch);
        if (removed) printf("%s removed\n", merch);
    }
}

static void edit_merch(warehouse_t *warehouse)
{
    char *merch = ask_question_string("Edit: ");
    if (warehouse_find_merch(warehouse, merch) == NULL)
    {
        printf("Merch %s not found, try again\n\n", merch);
        return;
    }
    char *new_name = ask_question_string("Name of Merch: ");
    char *new_description = ask_question_string("Description of Merch: ");
    int new_price = ask_question_int("Price of Merch (SEK): ");
    printf("Is the new information of the merch %s correct?\nName: %s\nDescription: %s\nPrice: %d\n", merch, new_name, new_description, new_price);
    char *choice = ask_question_string("Y/N? ");
    if (strcmp(choice, "Y") == 0 || strcmp(choice, "y") == 0) warehouse_edit_merch(warehouse, merch, new_name, new_description, new_price);
    puts("");
}

static void show_stock(warehouse_t *warehouse)
{
    char *merch = ask_question_string("Choose Merch: ");
    if (warehouse_find_merch(warehouse, merch) == NULL)
    {
        printf("Merch %s not found, try again\n\n", merch);
        return;
    }
    warehouse_show_stock(warehouse, merch);
}

static void replenish_merch(warehouse_t *warehouse) {
    char *merch_string = ask_question_string("Merch to replenish: ");
    merch_t *merch = warehouse_find_merch(warehouse, merch_string);
    if (merch == NULL)
    {
        printf("Merch %s not found, try again\n", merch_string);   
        replenish_merch(warehouse);
    }
    char *shelf = ask_question_string("Store on shelf: ");
    int quantity = ask_question_int("Quantity to add: ");
    warehouse_replenish_stock(warehouse, shelf, merch, quantity);
}

static void create_cart(warehouse_t *warehouse) {
        shopping_cart_t *cart = warehouse_create_cart(warehouse);
        int id = (int)cart->id;
    printf("Created shopping cart with id: %d\n\n", id);
}

static void cart_helper(warehouse_t *warehouse, int *cart_id) {
    bool cart_exists = false;
    while (!cart_exists) {
    *cart_id = ask_question_int("Specify your cart_id: ");
    size_t index = 0;
        if (warehouse_find_shopping_cart(warehouse, (size_t)*cart_id, &index) == NULL) {
            puts("Invalid cart, try again");
    } else {
        cart_exists = true;
    }
    }

}

static void remove_cart(warehouse_t *warehouse) {
    int cart_id;
    cart_helper(warehouse, &cart_id);
    size_t size_to_cart = (size_t)cart_id;
    size_t index = 0;
    warehouse_remove_cart(warehouse, size_to_cart, &index);
        printf("Shopping cart with id: %d, was removed\n\n", cart_id);
}


static void add_to_cart(warehouse_t *warehouse) {
    //check if cart is valid
    int cart_id;
    cart_helper(warehouse, &cart_id);
    char *merch = ask_question_string("Merch to be added to cart: ");
    int quant = ask_question_int("Quantity: ");

    while (!warehouse_add_to_cart(warehouse, cart_id, merch, (size_t)quant)) {
        puts("Invalid quant or merch, try again");
            merch = ask_question_string("Merch to be added to cart: ");
            quant = ask_question_int("Quantity: ");
    }
    printf("%d of %s was added to the shopping cart\n", quant, merch);
}

static void remove_from_cart(warehouse_t *warehouse) {
    //check if cart is valid
    int cart_id;
     cart_helper(warehouse, &cart_id);
    char *merch = ask_question_string("what merch do you want to remove: ");
    int quant = ask_question_int("Quantity: ");
        while (!warehouse_remove_from_cart(warehouse, (size_t)cart_id, merch, (size_t)quant)) {
            puts("Invalid quant or merch, try again\n");
                merch = ask_question_string("what merch do you want to remove: ");
                quant = ask_question_int("Quantity: ");
        }
    printf("%d of %s was removed from the shopping cart\n\n", quant, merch);
}

static void calculate_cost(warehouse_t *warehouse) {
    int cart_id;
    cart_helper(warehouse, &cart_id);
    size_t size_to_cart = (size_t)cart_id;
    int cost = (int)warehouse_calculate_cost(warehouse, size_to_cart);
    printf("Total cost of cart is: %d\n", cost); 
}

static void checkout(warehouse_t *warehouse) {
    int cart_id;
    cart_helper(warehouse, &cart_id);
    if (!warehouse_checkout(warehouse, (size_t)cart_id)) {
        puts("Checkout failed");
        return;
    } else {
        puts("Successfully checked out");
    }
}

void event_loop(warehouse_t *warehouse)
{
    char *menu = "[A] Add Merchandise\n"
                 "[L] List Merchandise\n"
                 "[D] Remove Merchandise\n"
                 "[E] Edit Merchandise\n"
                 "[S] Show Stock\n"
                 "[P] Replenish Merchandise\n"
                 "[C] Create Shopping Cart\n"
                 "[R] Remove Shopping Cart\n"
                 "[+] Add To Shopping Cart\n"
                 "[-] Remove From Shopping Cart\n"
                 "[=] Calculate Cost of Shopping Cart\n"
                 "[O] Checkout Shopping Cart\n"
                 "[Q] Quit program\n"
                 "> ";

    char answer;

    do
    {
        answer = ask_question_menu(menu);
        puts("");

        switch (answer)
        {
        case 'A':
            puts("Add Merch");
            add_merch(warehouse);
            break;

        case 'L': 
            puts("List of All Merch:");
            list_merch(warehouse);   
            break;

        case 'D':
            puts("Remove Merch");
            remove_merch(warehouse);
            break;

        case 'E':
            puts("Edit Merchandise");
            edit_merch(warehouse);
            break;

        case 'S': 
            puts("Show Stock of Merch");
            show_stock(warehouse);
            break;

        case 'P':
            replenish_merch(warehouse);
            break;

        case 'C':
            create_cart(warehouse);
            break;

        case 'R':
            remove_cart(warehouse);
            break;
        
        case '+':
            add_to_cart(warehouse);
            break;
        
        case '-':
            remove_from_cart(warehouse);
            break;
        
        case '=':
            calculate_cost(warehouse);
            break;
        
        case 'O':
            checkout(warehouse);
            break;
        }
        
    } while (answer != 'Q');
    
}
