#include "business_logic/webstore_backend.h"

void event_loop(warehouse_t *wh)
{
    char answer;

    do
    {
        // answer = ask_question_menu();
        if (answer == 'A')
        {
            // warehouse_add_merch();
        }
        else if (answer == 'L')
        {
            // warehouse_list_merch();
        }
        else if (answer == 'D')
        {
            // warehouse_remove_merch();
        }
        else if (answer == 'E')
        {
            // warehouse_edit_merch();
        }
        else if (answer == 'S')
        {
            // warehouse_show_stock();
        }
        else if (answer == 'P')
        {
            // warehouse_replenish_stock();
        }
        else if (answer == 'C')
        {
            // warehouse_create_cart();
        }
        else if (answer == 'R')
        {
            // warehouse_remove_cart();
        }
        else if (answer == '+')
        {
            // warehouse_add_to_cart();
        }
        else if (answer == '-')
        {
            // warehouse_remove_from_cart();
        }
        else if (answer == '=')
        {
            // warehouse_calculate_cost();
        }
        else if (answer == 'O')
        {
            // warehouse_checkout();
        }
    } while (answer != 'Q');
    
}

int main(void)
{
    warehouse_t *wh = warehouse_create();
    // TODO: build a base stock of stuff
    event_loop(wh);

    return 0;
}