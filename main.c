#include <stdio.h>
#include "business_logic/webstore_backend.h"
#include "business_logic/webstore_types.h"
#include "user_interface/ui.h"

int main(void)
{
    puts("Program körs");
    // TODO: skapa några fler varor till databasen
    warehouse_t *warehouse = warehouse_create();
    warehouse_add_merch(warehouse, "Bohnanza", "Board game. Harvest the most beans to win!", 250);
    warehouse_replenish_stock(warehouse, "A1", warehouse_find_merch(warehouse, "Bohnanza"), 20);
    warehouse_add_merch(warehouse, "Catan", "Board game. Build villages and roads and become the most powerful settler of Catan!", 400);
    warehouse_replenish_stock(warehouse, "B1", warehouse_find_merch(warehouse, "Catan"), 15);
    warehouse_add_merch(warehouse, "Chess", "Classic timeless game. Play the smartest moves.", 150);
    warehouse_replenish_stock(warehouse, "C1", warehouse_find_merch(warehouse, "Chess"), 17);
    warehouse_add_merch(warehouse, "Fia med knuff", "Board game. Get to the finish line while you push your enemies off the board.", 120);
    warehouse_replenish_stock(warehouse, "D1", warehouse_find_merch(warehouse, "Fia med knuff"), 10);
    
    event_loop(warehouse);
    warehouse_destroy(warehouse);
    
    return 0; 
}