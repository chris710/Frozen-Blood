//////////////////////////////////////////////////
///                   MAIN                     ///
///                 main.cpp                   ///
//////////////////////////////////////////////////

///POTRZEBNE PLIKI
#include "game/game.h"

///DEFINICJE PROGRAMU
#define ScreenHeight 672
#define ScreenWidth 960

int main()
{
    gameInstance* game = new gameInstance; //Tworzenie instancji gry
    if(!game->CreateDisplay(ScreenHeight,ScreenWidth)) return -1; //Tworzenie ekranu gry, jezeli wystapi blad to konczymy
    if(!game->ResourceLoader()) //Ladowanie danych, jezeli wystapi blad to usuwamy to co sie udalo zaladowac i konczymy
    {
        game->ReleaseMemory();
        return -1;
    }
    //Ustawianie zmiennych ALLEGRO i wlasciwa petla gry
    game->eventQueueAL = al_create_event_queue(); //Tworzymy nowa kolejke zdarzen
    al_register_event_source(game->eventQueueAL,al_get_keyboard_event_source()); // i ja rejestrujemy
    al_register_event_source(game->eventQueueAL,al_get_mouse_event_source()); // i rejestrujemy zdarzenia klawiatury i myszy
    game->gameTimerAL = al_create_timer(1.0/game->fps); //tworzymy nowy timer
    al_register_event_source(game->eventQueueAL,al_get_timer_event_source(game->gameTimerAL)); //i go rejestrujemy jako zrodlo zdarzen
    //Rejestracja okna jako zrodlo zdarzen
    al_register_event_source(game->eventQueueAL,al_get_display_event_source(game->displayAL));
    al_start_timer(game->gameTimerAL); //Uruchamiamy nasz timer
    std::cout << "Podaj nazwe mapy: ";
    std::string map;
    std::cin >> map;
    if(!game->LoadMap(map.c_str())) {game->ReleaseMemory(); return -1; } //Ladowanie testowej mapy, na razie brak interfejsu
    game->CreateUnit("test");
    while(!game->exitGame) //Petla wlasciwa gry
    {
        al_wait_for_event(game->eventQueueAL,&game->gameEventsAL); //Czekamy na zdarzenie
        al_get_mouse_state(&game->mouseState); //Pobieramy stan myszy
        switch(game->gameEventsAL.type) //Switch obslugi zdarzen
        {
        case ALLEGRO_EVENT_DISPLAY_CLOSE: //Jezeli wcisnieto przycisk "X"
            std::cout << "[DISPLAY] ENDING" << std::endl; //Zamykamy program
            game->exitGame = true;
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: //Jezeli wcisnieto przycisk myszy(dowolny!)
            if(game->cursor[0]!=NULL)          //Jezeli mamy wlasny kursor
            {
                if(game->mouseState.buttons & 1)
                {
                    al_set_mouse_cursor(game->displayAL,game->mouseCursor[1]); //Ustawiamy go, jezeli wcisnieto lewy przycisk
                    game->MapClick();
                }
                game->updateDisplay=true; //i updatujemy ekran
            }
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP: //Puszczono przycisk myszy
            if(game->cursor[1]!=NULL)
            {
                if(!game->mouseState.buttons & 1) al_set_mouse_cursor(game->displayAL,game->mouseCursor[0]); //Jezeli to lewy podniesiono, to zamieniamy kursor
                game->updateDisplay=true;
            }
            break;
        case ALLEGRO_EVENT_KEY_DOWN: //Jezeli wcisnieto przycisk na klawiaturze
            switch(game->gameEventsAL.keyboard.keycode) //to sprawdzamy co to za przycisk
            {
            case ALLEGRO_KEY_ESCAPE: //w przypadku esc zamykamy program
                if(game->mapDrawUnitRange && game->selectedUnit!=NULL)
                {
                game->selectedUnit = NULL;
                game->mapDrawUnitRange = false;
                std::cout << "[MAP] CS" << std::endl;
                game->updateDisplay=true;
                }
                else game->exitGame=true;
                break;
            }
            break;
        case ALLEGRO_EVENT_MOUSE_AXES:
             //Jezeli przesunieto mysz to updatujemy ekran(bo mamy fieldboxa do zaaktualizowania)
            game->updateDisplay=true;
            break;
        }
        if(game->updateDisplay || game->mapScroll) //Jezeli nalezy uaktualnic ekran, to to robimy
        {
            al_clear_to_color(al_map_rgb(157,67,67)); //czyscimi
            game->mapScroll=game->MapScroll();
            game->RenderMap(); //renderujemy mape
            game->RenderFieldBox(); //renderujemy fieldboxa
            if(game->selectedUnit!=NULL) game->RenderUnitRange();
            al_flip_display(); //wyswietlamy
            game->updateDisplay = false;
        }
    }
    game->ReleaseMemory(); //Zwalnianie pamieci zajetej przez gre, zwalniami Liby
    delete game; //Usuwamy instancje gry i konczymy
    return 0;
}
