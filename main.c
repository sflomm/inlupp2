#include "business_logic/webstore_backend.h"
#include "business_logic/webstore_types.h"
#include "user_interface/ui.h"

int main(void)
{
    // Used AI to create database
    warehouse_t *warehouse = ioopm_warehouse_create();
    ioopm_add_merch(warehouse, "Catan", "Epic Board Game", 100);
    ioopm_replenish_stock(warehouse, "A1", ioopm_find_merch(warehouse, "Catan"), 10);
    ioopm_replenish_stock(warehouse, "X1", ioopm_find_merch(warehouse, "Catan"), 10);
    ioopm_replenish_stock(warehouse, "Y1", ioopm_find_merch(warehouse, "Catan"), 10);

    ioopm_add_merch(warehouse, "Codenames", "Epic Board Game", 50);

    ioopm_add_merch(warehouse, "Ticket to Ride", "Epic Board Game", 85);
    ioopm_replenish_stock(warehouse, "A2", ioopm_find_merch(warehouse, "Ticket to Ride"), 35);

    ioopm_add_merch(warehouse, "Carcassonne", "Epic Board Game", 60);
    ioopm_replenish_stock(warehouse, "A3", ioopm_find_merch(warehouse, "Carcassonne"), 28);

    ioopm_add_merch(warehouse, "Pandemic", "Epic Board Game", 95);
    ioopm_replenish_stock(warehouse, "A4", ioopm_find_merch(warehouse, "Pandemic"), 24);

    ioopm_add_merch(warehouse, "Terraforming Mars", "Epic Board Game", 220);
    ioopm_replenish_stock(warehouse, "A5", ioopm_find_merch(warehouse, "Terraforming Mars"), 18);

    ioopm_add_merch(warehouse, "Gloomhaven", "Epic Board Game", 650);
    ioopm_replenish_stock(warehouse, "B1", ioopm_find_merch(warehouse, "Gloomhaven"), 8);

    ioopm_add_merch(warehouse, "Scythe", "Epic Board Game", 275);
    ioopm_replenish_stock(warehouse, "B2", ioopm_find_merch(warehouse, "Scythe"), 14);

    ioopm_add_merch(warehouse, "Wingspan", "Epic Board Game", 180);
    ioopm_replenish_stock(warehouse, "B3", ioopm_find_merch(warehouse, "Wingspan"), 31);

    ioopm_add_merch(warehouse, "Azul", "Epic Board Game", 70);
    ioopm_replenish_stock(warehouse, "B4", ioopm_find_merch(warehouse, "Azul"), 47);

    ioopm_add_merch(warehouse, "Splendor", "Epic Board Game", 75);
    ioopm_replenish_stock(warehouse, "B5", ioopm_find_merch(warehouse, "Splendor"), 39);

    ioopm_add_merch(warehouse, "7 Wonders", "Epic Board Game", 110);
    ioopm_replenish_stock(warehouse, "C1", ioopm_find_merch(warehouse, "7 Wonders"), 22);

    ioopm_add_merch(warehouse, "Dominion", "Epic Board Game", 65);
    ioopm_replenish_stock(warehouse, "C2", ioopm_find_merch(warehouse, "Dominion"), 33);

    ioopm_add_merch(warehouse, "Agricola", "Epic Board Game", 160);
    ioopm_replenish_stock(warehouse, "C3", ioopm_find_merch(warehouse, "Agricola"), 16);

    ioopm_add_merch(warehouse, "Twilight Imperium", "Epic Board Game", 980);
    ioopm_replenish_stock(warehouse, "C4", ioopm_find_merch(warehouse, "Twilight Imperium"), 5);

    ioopm_add_merch(warehouse, "Brass: Birmingham", "Epic Board Game", 310);
    ioopm_replenish_stock(warehouse, "C5", ioopm_find_merch(warehouse, "Brass: Birmingham"), 12);

    ioopm_add_merch(warehouse, "Root", "Epic Board Game", 195);
    ioopm_replenish_stock(warehouse, "D1", ioopm_find_merch(warehouse, "Root"), 20);

    ioopm_add_merch(warehouse, "Spirit Island", "Epic Board Game", 240);
    ioopm_replenish_stock(warehouse, "D2", ioopm_find_merch(warehouse, "Spirit Island"), 15);

    ioopm_add_merch(warehouse, "Everdell", "Epic Board Game", 205);
    ioopm_replenish_stock(warehouse, "D3", ioopm_find_merch(warehouse, "Everdell"), 26);

    ioopm_add_merch(warehouse, "Dixit", "Epic Board Game", 55);
    ioopm_replenish_stock(warehouse, "D5", ioopm_find_merch(warehouse, "Dixit"), 44);

    ioopm_add_merch(warehouse, "Betrayal at House on the Hill", "Epic Board Game", 90);
    ioopm_replenish_stock(warehouse, "E1", ioopm_find_merch(warehouse, "Betrayal at House on the Hill"), 19);

    ioopm_add_merch(warehouse, "Eldritch Horror", "Epic Board Game", 145);
    ioopm_replenish_stock(warehouse, "E2", ioopm_find_merch(warehouse, "Eldritch Horror"), 13);

    ioopm_add_merch(warehouse, "Arkham Horror", "Epic Board Game", 170);
    ioopm_replenish_stock(warehouse, "E3", ioopm_find_merch(warehouse, "Arkham Horror"), 11);

    ioopm_add_merch(warehouse, "Risk", "Epic Board Game", 80);
    ioopm_replenish_stock(warehouse, "E4", ioopm_find_merch(warehouse, "Risk"), 37);

    ioopm_add_merch(warehouse, "Monopoly", "Epic Board Game", 52);
    ioopm_replenish_stock(warehouse, "E5", ioopm_find_merch(warehouse, "Monopoly"), 48);

    ioopm_add_merch(warehouse, "Clue", "Epic Board Game", 58);
    ioopm_replenish_stock(warehouse, "F1", ioopm_find_merch(warehouse, "Clue"), 30);

    ioopm_add_merch(warehouse, "Small World", "Epic Board Game", 100);
    ioopm_replenish_stock(warehouse, "F2", ioopm_find_merch(warehouse, "Small World"), 21);

    ioopm_add_merch(warehouse, "Puerto Rico", "Epic Board Game", 125);
    ioopm_replenish_stock(warehouse, "F3", ioopm_find_merch(warehouse, "Puerto Rico"), 17);

    ioopm_add_merch(warehouse, "Dune: Imperium", "Epic Board Game", 235);
    ioopm_replenish_stock(warehouse, "F4", ioopm_find_merch(warehouse, "Dune: Imperium"), 23);

    ioopm_add_merch(warehouse, "Mansions of Madness", "Epic Board Game", 190);
    ioopm_replenish_stock(warehouse, "F5", ioopm_find_merch(warehouse, "Mansions of Madness"), 9);

    ioopm_add_merch(warehouse, "Azul: Stained Glass of Sintra", "Epic Board Game", 88);
    ioopm_replenish_stock(warehouse, "G1", ioopm_find_merch(warehouse, "Azul: Stained Glass of Sintra"), 27);

    ioopm_add_merch(warehouse, "Cascadia", "Epic Board Game", 72);
    ioopm_replenish_stock(warehouse, "G2", ioopm_find_merch(warehouse, "Cascadia"), 36);

    ioopm_add_merch(warehouse, "Lords of Waterdeep", "Epic Board Game", 105);
    ioopm_replenish_stock(warehouse, "G3", ioopm_find_merch(warehouse, "Lords of Waterdeep"), 18);

    ioopm_add_merch(warehouse, "Concordia", "Epic Board Game", 135);
    ioopm_replenish_stock(warehouse, "G4", ioopm_find_merch(warehouse, "Concordia"), 15);

    ioopm_add_merch(warehouse, "Viticulture", "Epic Board Game", 150);
    ioopm_replenish_stock(warehouse, "G5", ioopm_find_merch(warehouse, "Viticulture"), 22);

    ioopm_add_merch(warehouse, "Arkham Horror: The Card Game", "Epic Board Game", 78);
    ioopm_replenish_stock(warehouse, "H1", ioopm_find_merch(warehouse, "Arkham Horror: The Card Game"), 40);

    ioopm_add_merch(warehouse, "Blood Rage", "Epic Board Game", 215);
    ioopm_replenish_stock(warehouse, "H2", ioopm_find_merch(warehouse, "Blood Rage"), 12);

    ioopm_add_merch(warehouse, "Kingdomino", "Epic Board Game", 54);
    ioopm_replenish_stock(warehouse, "H3", ioopm_find_merch(warehouse, "Kingdomino"), 46);

    ioopm_add_merch(warehouse, "Patchwork", "Epic Board Game", 62);
    ioopm_replenish_stock(warehouse, "H4", ioopm_find_merch(warehouse, "Patchwork"), 29);

    ioopm_add_merch(warehouse, "Jaipur", "Epic Board Game", 51);
    ioopm_replenish_stock(warehouse, "H5", ioopm_find_merch(warehouse, "Jaipur"), 43);

    ioopm_add_merch(warehouse, "Star Realms", "Epic Board Game", 59);
    ioopm_replenish_stock(warehouse, "I1", ioopm_find_merch(warehouse, "Star Realms"), 34);

    ioopm_add_merch(warehouse, "Food Chain Magnate", "Epic Board Game", 280);
    ioopm_replenish_stock(warehouse, "I2", ioopm_find_merch(warehouse, "Food Chain Magnate"), 7);

    ioopm_add_merch(warehouse, "Great Western Trail", "Epic Board Game", 225);
    ioopm_replenish_stock(warehouse, "I3", ioopm_find_merch(warehouse, "Great Western Trail"), 16);

    ioopm_add_merch(warehouse, "Ark Nova", "Epic Board Game", 260);
    ioopm_replenish_stock(warehouse, "I4", ioopm_find_merch(warehouse, "Ark Nova"), 20);

    ioopm_add_merch(warehouse, "Gaia Project", "Epic Board Game", 245);
    ioopm_replenish_stock(warehouse, "I5", ioopm_find_merch(warehouse, "Gaia Project"), 10);

    ioopm_add_merch(warehouse, "Mage Knight", "Epic Board Game", 165);
    ioopm_replenish_stock(warehouse, "J1", ioopm_find_merch(warehouse, "Mage Knight"), 14);

    ioopm_add_merch(warehouse, "Pandemic Legacy: Season 1", "Epic Board Game", 140);
    ioopm_replenish_stock(warehouse, "J2", ioopm_find_merch(warehouse, "Pandemic Legacy: Season 1"), 25);

    ioopm_add_merch(warehouse, "Descent: Journeys in the Dark", "Epic Board Game", 120);
    ioopm_replenish_stock(warehouse, "J3", ioopm_find_merch(warehouse, "Descent: Journeys in the Dark"), 9);

    ioopm_add_merch(warehouse, "War of the Ring", "Epic Board Game", 185);
    ioopm_replenish_stock(warehouse, "J4", ioopm_find_merch(warehouse, "War of the Ring"), 11);

    ioopm_add_merch(warehouse, "Bohnanza", "Epic Board Game", 200);
    ioopm_replenish_stock(warehouse, "J5", ioopm_find_merch(warehouse, "War of the Ring"), 100);
    
    ioopm_event_loop(warehouse);
    ioopm_warehouse_destroy(warehouse);
    
    return 0; 
}