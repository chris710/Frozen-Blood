//////////////////////////////////////////////////
///                   MAIN                     ///
///                 main.cpp                   ///
//////////////////////////////////////////////////

///POTRZEBNE PLIKI
#include "game/game.h"
#include "game/units.h"
#include "editor/level_editor.h"

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
    //Wlasciwa petla gry
    game->eventQueueAL = al_create_event_queue();
    al_register_event_source(game->eventQueueAL,al_get_keyboard_event_source());

    game->gameTimerAL = al_create_timer(1.0/game->fps);
    al_register_event_source(game->eventQueueAL,al_get_timer_event_source(game->gameTimerAL));


    al_start_timer(game->gameTimerAL);
    while(!game->exitGame)
    {
        al_wait_for_event(game->eventQueueAL,&game->gameEventsAL);
        if(game->gameEventsAL.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(game->gameEventsAL.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                game->exitGame = true;
                break;
            }
        }
        if(game->updateDisplay)
        {
            al_flip_display();
            al_clear_to_color(al_map_rgb(157,67,67));
        }
    }
    game->ReleaseMemory(); //Zwalnianie pamieci zajetej przez gre
    delete game;
    return 0;
}
