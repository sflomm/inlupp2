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
