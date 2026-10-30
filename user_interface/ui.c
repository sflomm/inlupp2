#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "../business_logic/webstore_backend.h"
#include "../business_logic/webstore_types.h"
#include "../generic_types/hash_table_iterator.h"
#include "../generic_types/utils.h"

// TODO: alfabetisk ordning hade varit najs att få till
// kanske måste importera några fler h-filer för att köra funktionen
// TODO: skriv in i ui.h och ta bort från merch_stock.h
void warehouse_list_merch(warehouse_t *wh)
{
  ioopm_hash_table_t *merch_ht = wh->merch_ht;
  ioopm_hash_table_iterator_t *merch_it = ioopm_hash_table_iterator_create(merch_ht);
  size_t total_amount_of_merch = merch_ht->size; // FIXME: konvertera size_t till int eller vice versa, casta
  int listed_merch_count = 1;

  while (!ioopm_hash_table_iterator_at_end(merch_it) && listed_merch_count <= total_amount_of_merch)
  {
    char *current_key = ioopm_hash_table_iterator_current_key(merch_it).s;
    printf("%d. %s\n", listed_merch_count, current_key); // ersätta d med size_t kompatibel
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

// ganska noobig funktion, skulle nog kunna optimeras
bool correct_letter(char *str)
{
    if (strlen(str) != 1)
    {
        return false;
    }

    char *letters = "AaLlDdEeSsPpCcRr+-=OoQq";
    char current = *letters; 

    while (current != '\0')
    {
        if (current == *str)
        {
            return true;
        } 

        letters++;
        current = *letters;
    }

    return false;
}

int toupper_modified(char *str)
{
    if (str == "+" || str == "-" || str == "=")
    {
        return atoi(str);
    }

    // (gamla koden) int letter = toupper(*str); FIXME: ersätt med gamla koden om nuvarande return inte funkar
    return toupper(*str);
}

char ask_question_menu(void)
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
                 "[Q] Quit program\n";
    answer_t answer = ask_question(menu, correct_letter, (convert_func *) toupper_modified);
    char answer_mod = answer.character;
    return answer_mod;
}

void event_loop(warehouse_t *warehouse)
{
    char answer;

    // lite oklart hur det funkar med +-=, kika på det

    do
    {
        answer = ask_question_menu();

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
            int *price = ask_question_int("Price: ");
            warehouse_add_merch(warehouse, name, description, price);
            break;

        case 'L': 
            puts("List of All Merch:");
            warehouse_list_merch(warehouse);
            break;

        case 'D':
            puts("Remove Merch");
            char *merch = ask_question_string("Remove: ");
            if (warehouse_find_merch(warehouse, merch) == NULL)
            {
                printf("Merch %s not found, try again\n", merch);
                break;
            }
            printf("Do you want to remove %s?\n", merch);
            char *choice = ask_question_string("Y/N: ");
            if (choice == "Y" || choice == "y")
            {
                bool removed = warehouse_remove_merch(warehouse, merch);
                if (removed) printf("%s removed\n", merch); // FIXME: ta bort sen för den här checken finns i funktionen redan
            }
            break;

        case 'E':
            puts("Edit Merchandise");
            char *merch = ask_question_string("Edit: ");
            if (warehouse_find_merch(warehouse, merch) == NULL)
            {
                printf("Merch %s not found, try again\n", merch);
                break;
            }
            char *new_name = ask_question_string("Name of Merch: ");
            char *new_description = ask_question_string("Description of Merch: ");
            int new_price = ask_question_int("Price of Merch (SEK): ");
            printf("Is the new information of the merch %s correct?\nName: %s\nDescription: %s\nPrice: %d\n", merch, new_name, new_description, new_price);
            char *choice = ask_question_string("Y/N: ");
            if (choice == "Y" || choice == "y") warehouse_edit_merch(warehouse, merch, new_name, new_description, new_price);
            break;

        case 'S':
            puts("Show Stock of Merch");
            char *merch = ask_question_string("Choose Merch: ");
            if (warehouse_find_merch(warehouse, merch) == NULL)
            {
                printf("Merch %s not found, try again\n", merch);
                break;
            }
            warehouse_show_stock(warehouse, merch);
            break;

        case 'P':
            puts("Replenish Merchandise");
            char *merch = ask_question_string("Merch to replenish: ");
            if (warehouse_find_merch(warehouse, merch) == NULL)
            {
                printf("Merch %s not found, try again\n", merch);
                break;
            }
            char *shelf = ask_question_string("Store on shelf: ");
            if (warehouse_find_shelf(warehouse, shelf) == NULL)
            {
                printf("Shelf %s not found, try again\n", shelf);
                break;
            }
            int quantity = ask_question_int("Quantity to add: ");
            warehouse_replenish_stock(warehouse, shelf, merch, quantity);
            break;

        // case 'C':
        //     warehouse_create_cart(warehouse);
        //     break;

        // case 'R':
        //     warehouse_remove_cart(warehouse, key);
        //     break;
        
        // case '+':
        //     warehouse_add_to_cart(warehouse->carts, cart, merch, quantity);
        //     break;
        
        // case '-':
        //     warehouse_remove_from_cart(warehouse, cart, merch, quantity);
        //     break;
        
        // case '=':
        //     warehouse_calculate_cost(warehouse->carts, cart);
        //     break;
        
        // case 'O':
        //     warehouse_checkout(warehouse, cart);
        //     break;

        case 'Q':
            // nothing to do, the loop condition ends the program
            break;

        default:
            puts("Invalid choice");
            break;
        }
        
    } while (answer != 'Q');
    
}

// FIXME: main borde kanske vara i en fil som bara heter main.c
// så låter man hela den här modulen med ui grejer vara separat?
int main(void)
{
    warehouse_t *warehouse = warehouse_create();
    // TODO: skapa några varor till databasen
    event_loop(warehouse);
    warehouse_destroy(warehouse);
    
    return 0; 
}