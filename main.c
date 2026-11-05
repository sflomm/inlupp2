#include <stdio.h>
#include "business_logic/webstore_backend.h"
#include "business_logic/webstore_types.h"
#include "user_interface/ui.h"

int main(void)
{
    // Used AI to create database
    warehouse_t *warehouse = warehouse_create();
    warehouse_add_merch(warehouse, "Catan", "Epic Board Game", 100);
    warehouse_replenish_stock(warehouse, "A1", warehouse_find_merch(warehouse, "Catan"), 10);
    warehouse_replenish_stock(warehouse, "X1", warehouse_find_merch(warehouse, "Catan"), 10);
    warehouse_replenish_stock(warehouse, "Y1", warehouse_find_merch(warehouse, "Catan"), 10);

    warehouse_add_merch(warehouse, "Codenames", "Epic Board Game", 50);

    warehouse_add_merch(warehouse, "Ticket to Ride", "Epic Board Game", 85);
    warehouse_replenish_stock(warehouse, "A2", warehouse_find_merch(warehouse, "Ticket to Ride"), 35);

    warehouse_add_merch(warehouse, "Carcassonne", "Epic Board Game", 60);
    warehouse_replenish_stock(warehouse, "A3", warehouse_find_merch(warehouse, "Carcassonne"), 28);

    warehouse_add_merch(warehouse, "Pandemic", "Epic Board Game", 95);
    warehouse_replenish_stock(warehouse, "A4", warehouse_find_merch(warehouse, "Pandemic"), 24);

    warehouse_add_merch(warehouse, "Terraforming Mars", "Epic Board Game", 220);
    warehouse_replenish_stock(warehouse, "A5", warehouse_find_merch(warehouse, "Terraforming Mars"), 18);

    warehouse_add_merch(warehouse, "Gloomhaven", "Epic Board Game", 650);
    warehouse_replenish_stock(warehouse, "B1", warehouse_find_merch(warehouse, "Gloomhaven"), 8);

    warehouse_add_merch(warehouse, "Scythe", "Epic Board Game", 275);
    warehouse_replenish_stock(warehouse, "B2", warehouse_find_merch(warehouse, "Scythe"), 14);

    warehouse_add_merch(warehouse, "Wingspan", "Epic Board Game", 180);
    warehouse_replenish_stock(warehouse, "B3", warehouse_find_merch(warehouse, "Wingspan"), 31);

    warehouse_add_merch(warehouse, "Azul", "Epic Board Game", 70);
    warehouse_replenish_stock(warehouse, "B4", warehouse_find_merch(warehouse, "Azul"), 47);

    warehouse_add_merch(warehouse, "Splendor", "Epic Board Game", 75);
    warehouse_replenish_stock(warehouse, "B5", warehouse_find_merch(warehouse, "Splendor"), 39);

    warehouse_add_merch(warehouse, "7 Wonders", "Epic Board Game", 110);
    warehouse_replenish_stock(warehouse, "C1", warehouse_find_merch(warehouse, "7 Wonders"), 22);

    warehouse_add_merch(warehouse, "Dominion", "Epic Board Game", 65);
    warehouse_replenish_stock(warehouse, "C2", warehouse_find_merch(warehouse, "Dominion"), 33);

    warehouse_add_merch(warehouse, "Agricola", "Epic Board Game", 160);
    warehouse_replenish_stock(warehouse, "C3", warehouse_find_merch(warehouse, "Agricola"), 16);

    warehouse_add_merch(warehouse, "Twilight Imperium", "Epic Board Game", 980);
    warehouse_replenish_stock(warehouse, "C4", warehouse_find_merch(warehouse, "Twilight Imperium"), 5);

    warehouse_add_merch(warehouse, "Brass: Birmingham", "Epic Board Game", 310);
    warehouse_replenish_stock(warehouse, "C5", warehouse_find_merch(warehouse, "Brass: Birmingham"), 12);

    warehouse_add_merch(warehouse, "Root", "Epic Board Game", 195);
    warehouse_replenish_stock(warehouse, "D1", warehouse_find_merch(warehouse, "Root"), 20);

    warehouse_add_merch(warehouse, "Spirit Island", "Epic Board Game", 240);
    warehouse_replenish_stock(warehouse, "D2", warehouse_find_merch(warehouse, "Spirit Island"), 15);

    warehouse_add_merch(warehouse, "Everdell", "Epic Board Game", 205);
    warehouse_replenish_stock(warehouse, "D3", warehouse_find_merch(warehouse, "Everdell"), 26);

    warehouse_add_merch(warehouse, "Dixit", "Epic Board Game", 55);
    warehouse_replenish_stock(warehouse, "D5", warehouse_find_merch(warehouse, "Dixit"), 44);

    warehouse_add_merch(warehouse, "Betrayal at House on the Hill", "Epic Board Game", 90);
    warehouse_replenish_stock(warehouse, "E1", warehouse_find_merch(warehouse, "Betrayal at House on the Hill"), 19);

    warehouse_add_merch(warehouse, "Eldritch Horror", "Epic Board Game", 145);
    warehouse_replenish_stock(warehouse, "E2", warehouse_find_merch(warehouse, "Eldritch Horror"), 13);

    warehouse_add_merch(warehouse, "Arkham Horror", "Epic Board Game", 170);
    warehouse_replenish_stock(warehouse, "E3", warehouse_find_merch(warehouse, "Arkham Horror"), 11);

    warehouse_add_merch(warehouse, "Risk", "Epic Board Game", 80);
    warehouse_replenish_stock(warehouse, "E4", warehouse_find_merch(warehouse, "Risk"), 37);

    warehouse_add_merch(warehouse, "Monopoly", "Epic Board Game", 52);
    warehouse_replenish_stock(warehouse, "E5", warehouse_find_merch(warehouse, "Monopoly"), 48);

    warehouse_add_merch(warehouse, "Clue", "Epic Board Game", 58);
    warehouse_replenish_stock(warehouse, "F1", warehouse_find_merch(warehouse, "Clue"), 30);

    warehouse_add_merch(warehouse, "Small World", "Epic Board Game", 100);
    warehouse_replenish_stock(warehouse, "F2", warehouse_find_merch(warehouse, "Small World"), 21);

    warehouse_add_merch(warehouse, "Puerto Rico", "Epic Board Game", 125);
    warehouse_replenish_stock(warehouse, "F3", warehouse_find_merch(warehouse, "Puerto Rico"), 17);

    warehouse_add_merch(warehouse, "Dune: Imperium", "Epic Board Game", 235);
    warehouse_replenish_stock(warehouse, "F4", warehouse_find_merch(warehouse, "Dune: Imperium"), 23);

    warehouse_add_merch(warehouse, "Mansions of Madness", "Epic Board Game", 190);
    warehouse_replenish_stock(warehouse, "F5", warehouse_find_merch(warehouse, "Mansions of Madness"), 9);

    warehouse_add_merch(warehouse, "Azul: Stained Glass of Sintra", "Epic Board Game", 88);
    warehouse_replenish_stock(warehouse, "G1", warehouse_find_merch(warehouse, "Azul: Stained Glass of Sintra"), 27);

    warehouse_add_merch(warehouse, "Cascadia", "Epic Board Game", 72);
    warehouse_replenish_stock(warehouse, "G2", warehouse_find_merch(warehouse, "Cascadia"), 36);

    warehouse_add_merch(warehouse, "Lords of Waterdeep", "Epic Board Game", 105);
    warehouse_replenish_stock(warehouse, "G3", warehouse_find_merch(warehouse, "Lords of Waterdeep"), 18);

    warehouse_add_merch(warehouse, "Concordia", "Epic Board Game", 135);
    warehouse_replenish_stock(warehouse, "G4", warehouse_find_merch(warehouse, "Concordia"), 15);

    warehouse_add_merch(warehouse, "Viticulture", "Epic Board Game", 150);
    warehouse_replenish_stock(warehouse, "G5", warehouse_find_merch(warehouse, "Viticulture"), 22);

    warehouse_add_merch(warehouse, "Arkham Horror: The Card Game", "Epic Board Game", 78);
    warehouse_replenish_stock(warehouse, "H1", warehouse_find_merch(warehouse, "Arkham Horror: The Card Game"), 40);

    warehouse_add_merch(warehouse, "Blood Rage", "Epic Board Game", 215);
    warehouse_replenish_stock(warehouse, "H2", warehouse_find_merch(warehouse, "Blood Rage"), 12);

    warehouse_add_merch(warehouse, "Kingdomino", "Epic Board Game", 54);
    warehouse_replenish_stock(warehouse, "H3", warehouse_find_merch(warehouse, "Kingdomino"), 46);

    warehouse_add_merch(warehouse, "Patchwork", "Epic Board Game", 62);
    warehouse_replenish_stock(warehouse, "H4", warehouse_find_merch(warehouse, "Patchwork"), 29);

    warehouse_add_merch(warehouse, "Jaipur", "Epic Board Game", 51);
    warehouse_replenish_stock(warehouse, "H5", warehouse_find_merch(warehouse, "Jaipur"), 43);

    warehouse_add_merch(warehouse, "Star Realms", "Epic Board Game", 59);
    warehouse_replenish_stock(warehouse, "I1", warehouse_find_merch(warehouse, "Star Realms"), 34);

    warehouse_add_merch(warehouse, "Food Chain Magnate", "Epic Board Game", 280);
    warehouse_replenish_stock(warehouse, "I2", warehouse_find_merch(warehouse, "Food Chain Magnate"), 7);

    warehouse_add_merch(warehouse, "Great Western Trail", "Epic Board Game", 225);
    warehouse_replenish_stock(warehouse, "I3", warehouse_find_merch(warehouse, "Great Western Trail"), 16);

    warehouse_add_merch(warehouse, "Ark Nova", "Epic Board Game", 260);
    warehouse_replenish_stock(warehouse, "I4", warehouse_find_merch(warehouse, "Ark Nova"), 20);

    warehouse_add_merch(warehouse, "Gaia Project", "Epic Board Game", 245);
    warehouse_replenish_stock(warehouse, "I5", warehouse_find_merch(warehouse, "Gaia Project"), 10);

    warehouse_add_merch(warehouse, "Mage Knight", "Epic Board Game", 165);
    warehouse_replenish_stock(warehouse, "J1", warehouse_find_merch(warehouse, "Mage Knight"), 14);

    warehouse_add_merch(warehouse, "Pandemic Legacy: Season 1", "Epic Board Game", 140);
    warehouse_replenish_stock(warehouse, "J2", warehouse_find_merch(warehouse, "Pandemic Legacy: Season 1"), 25);

    warehouse_add_merch(warehouse, "Descent: Journeys in the Dark", "Epic Board Game", 120);
    warehouse_replenish_stock(warehouse, "J3", warehouse_find_merch(warehouse, "Descent: Journeys in the Dark"), 9);

    warehouse_add_merch(warehouse, "War of the Ring", "Epic Board Game", 185);
    warehouse_replenish_stock(warehouse, "J4", warehouse_find_merch(warehouse, "War of the Ring"), 11);

    warehouse_add_merch(warehouse, "Bohnanza", "Epic Board Game", 200);
    warehouse_replenish_stock(warehouse, "J5", warehouse_find_merch(warehouse, "War of the Ring"), 100);
    
    event_loop(warehouse);
    warehouse_destroy(warehouse);
    
    return 0; 
}