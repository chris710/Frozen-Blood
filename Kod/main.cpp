//////////////////////////////////////////////////
///                   MAIN                     ///
///                 main.cpp                   ///
//////////////////////////////////////////////////

///POTRZEBNE PLIKI
#include "game/game.h"

///DEFINICJE PROGRAMU
#define ScreenHeight 600
#define ScreenWidth 800

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

    game->gameTimerAL = al_create_timer(1.0/game->fps); //tworzymy nowy timer
    al_register_event_source(game->eventQueueAL,al_get_timer_event_source(game->gameTimerAL)); //i go rejestrujemy jako zrodlo zdarzen

    //Rejestracja okna jako zrodlo zdarzen
    al_register_event_source(game->eventQueueAL,al_get_display_event_source(game->GetDisplay()));

    al_start_timer(game->gameTimerAL); //Uruchamiamy nasz timer

    game->LoadMap("test"); //Ladowanie testowej mapy, na razie brak interfejsu

    while(!game->exitGame) //Petla wlasciwa gry
    {

        al_wait_for_event(game->eventQueueAL,&game->gameEventsAL); //Czekamy na zdarzenie
        //Zamykanie przyciskiem
        if(game->gameEventsAL.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { std::cout << "[DISPLAY] ENDING" << std::endl; game->exitGame = true; break; }
        if(game->gameEventsAL.type == ALLEGRO_EVENT_KEY_DOWN) //Jezeli zdarzenie to wcisniety przycisk
        {
            switch(game->gameEventsAL.keyboard.keycode) //to sprawdzamy co to za przycisk
            {
            case ALLEGRO_KEY_ESCAPE: //w przypadku esc zamykamy program
                game->exitGame = true;
                break;
            }
        }
        if(game->updateDisplay) //Jezeli nalezy uaktualnic ekran, to to robimy
        {

            al_clear_to_color(al_map_rgb(157,67,67));
            game->RenderMap();
            al_flip_display();
            game->updateDisplay = false;
        }
    }
    game->ReleaseMemory(); //Zwalnianie pamieci zajetej przez gre, zwalniami Liby
    delete game; //Usuwamy instancje gry i konczymy
    return 0;
}
