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

// TODO: alfabetisk ordning hade varit najs att få till
// kanske måste importera några fler h-filer för att köra funktionen
// TODO: skriv in i ui.h och ta bort från merch_stock.h
void warehouse_list_merch(warehouse_t *wh)
{
  ioopm_hash_table_t *merch_ht = wh->merch_ht;
  ioopm_hash_table_iterator_t *merch_it = ioopm_hash_table_iterator_create(merch_ht);
  size_t total_amount_of_merch = merch_ht->size; // FIXME: konvertera size_t till int eller vice versa, casta
  size_t listed_merch_count = 1;

  while (!ioopm_hash_table_iterator_at_end(merch_it) && listed_merch_count <= total_amount_of_merch)
  {
    char *current_key = ioopm_hash_table_iterator_current_key(merch_it).s;
    printf("%zu. %s\n", listed_merch_count, current_key); // ersätta d med size_t kompatibel
    ioopm_hash_table_iterator_advance(merch_it);

    if (listed_merch_count % 20 == 0)
    {
      char *choice = ask_question_string("Continue? [Y/N] ");
      if (strcmp(choice, "N") == 0 || strcmp(choice, "n") == 0)
      {
        puts("Returning to main menu...");
        break;
      }  
    }
    listed_merch_count++;
  }  
}

// TODO: alphabetical order 
void warehouse_show_stock(warehouse_t *wh, char *key)
{
  merch_t *merch = warehouse_find_merch(wh, key);
  ioopm_list_iterator_t *it = ioopm_list_iterator_create(merch->locs);

  while (!ioopm_list_iterator_at_end(it))
  {
    link_t *current_link = ioopm_list_iterator_current(it).p;
    shelf_t *current_shelf = current_link->element.p;
    int quant = current_shelf->quant;
    char *shelf = current_shelf->shelf;
    printf("Shelf: %s. Stock: %d\n", shelf, quant);
    ioopm_list_iterator_advance(it);
  }

  ioopm_list_iterator_destroy(it);
}

static void replenish_merch(warehouse_t *warehouse) {
    char *merch_p_input = ask_question_string("Merch to replenish: ");
    merch_t *merch_p = warehouse_find_merch(warehouse, merch_p_input);
    if (merch_p == NULL)
    {
        printf("Merch %s not found, try again\n", merch_p_input);   
        replenish_merch(warehouse);
}
        char *shelf_p = ask_question_string("Store on shelf: ");
        int quantity = ask_question_int("Quantity to add: ");
        warehouse_replenish_stock(warehouse, shelf_p, merch_p, quantity);
}

static void create_cart(warehouse_t *warehouse) {
        shopping_cart_t *cart = warehouse_create_cart(warehouse);
        int id = (int)cart->id;
    printf("Created shopping cart with id: %d\n", id);
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
        printf("Shopping cart with id: %d, was removed", cart_id);
}


static void add_to_cart(warehouse_t *warehouse) {
    //check if cart is valid
    int cart_id;
    cart_helper(warehouse, &cart_id);
    char *merch = ask_question_string("Merch to be added to cart: ");
    int quant = ask_question_int("Quantity: ");
    size_t size_to_quant = (size_t)quant;
        while (!warehouse_add_to_cart(warehouse, cart_id, merch, quant)) {
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
            puts("Invalid quant or merch, try again");
                merch = ask_question_string("what merch do you want to remove: ");
                quant = ask_question_int("Quantity: ");
        }
    printf("%d of %s was removed from the shopping cart\n", quant, merch);
}

static void calculate_cost(warehouse_t *warehouse) {
    int cart_id;
    cart_helper(warehouse, &cart_id);
    size_t size_to_cart = (size_t)cart_id;
    int cost = (int)warehouse_calculate_cost(warehouse, size_to_cart);
    printf("Total cost of cart is: %d\n", cost); 
}

//FIXME: checkout failed
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

        // TODO: 
        // - hur ska vi tänka kring stora/små bokstäver på input? 
        // - fixa funktioner som behöver konfirmationssträngar
        // add_merch, list_merch, remove_merch, edit_merch
        // remove_cart
        // - event loopen blir enorm så vi kanske ska dela upp varje case i små funktioner? ABSTRAKTION.
        // vet inte vad som är bäst
        // - tror att det checkas dubbelt om det är rätt bokstav, det kan nog göras mer kompakt och smart 
        // - checken för om merchen finns skulle kunna göras till en funktion kanske? 
        // för den är med i nästan alla cases just nu... 

        switch (answer)
        {
        case 'A': // konfirmationssträng behövs
            puts("Add Merch");
            char *name = ask_question_string("Name: ");
            char *description = ask_question_string("Description: ");
            int price = ask_question_int("Price (SEK): ");
            warehouse_add_merch(warehouse, name, description, price);
            puts("");
            break;

        case 'L': 
            puts("List of All Merch:");
            warehouse_list_merch(warehouse);
            puts("");
            break;

        case 'D':
            puts("Remove Merch");
            char *merch_d = ask_question_string("Remove: ");
            if (warehouse_find_merch(warehouse, merch_d) == NULL)
            {
                printf("Merch %s not found, try again\n", merch_d);
                break;
            }
            printf("Do you want to remove %s?\n", merch_d);
            char *choice_d = ask_question_string("Y/N: ");
            if (strcmp(choice_d, "Y") == 0 || strcmp(choice_d, "y") == 0)
            {
                bool removed = warehouse_remove_merch(warehouse, merch_d);
                if (removed) printf("%s removed\n", merch_d);
            }
            break;

        case 'E':
            puts("Edit Merchandise");
            char *merch_e = ask_question_string("Edit: ");
            if (warehouse_find_merch(warehouse, merch_e) == NULL)
            {
                printf("Merch %s not found, try again\n", merch_e);
                break;
            }
            char *new_name = ask_question_string("Name of Merch: ");
            char *new_description = ask_question_string("Description of Merch: ");
            int new_price = ask_question_int("Price of Merch (SEK): ");
            printf("Is the new information of the merch %s correct?\nName: %s\nDescription: %s\nPrice: %d\n", merch_e, new_name, new_description, new_price);
            char *choice_e = ask_question_string("Y/N: ");
            if (strcmp(choice_e, "Y") == 0 || strcmp(choice_e, "y") == 0) warehouse_edit_merch(warehouse, merch_e, new_name, new_description, new_price);
            break;

        case 'S': // FIXME: funkar inte :( SEGFAULT
            puts("Show Stock of Merch");
            char *merch_s = ask_question_string("Choose Merch: ");
            if (warehouse_find_merch(warehouse, merch_s) == NULL)
            {
                printf("Merch %s not found, try again\n", merch_s);
                break;
            }
            warehouse_show_stock(warehouse, merch_s);
            break;

        case 'P': // FIXME: testa denna när show stock funkar
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

        case 'Q':
            // nothing to do, the loop condition ends the program
            break;

        default:
            puts("Invalid choice");
            break;
        }
        
    } while (answer != 'Q');
    
}
