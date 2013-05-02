//////////////////////////////////////////////////
///                   MAIN                     ///
///                 main.cpp                   ///
//////////////////////////////////////////////////

///POTRZEBNE PLIKI
#include "game/game.h"
#include "game/units.h"

///DEFINICJE PROGRAMU
#define ScreenHeight 600
#define ScreenWidth 800

int main()
{
    gameInstance* game = new gameInstance; //Tworzenie instancji gry
    if(!game->CreateDisplay(ScreenHeight,ScreenWidth)) return -1; //Tworzenie ekranu gry, jezeli wystapi blad to konczymy
    if(!game->ResourceLoader()) //Ladowanie danych, jezeli wystapi blad to usuwamy to co sie udalo zaladowac i konczymy
    {
        game->ResourceUnloader();
        game->ReleaseMemory();
        return -1;
    }
    //Wlasciwa petla gry
    game->CreateUnit("test");


    game->ResourceUnloader(); //Usuwanie list zasobow
    game->ReleaseMemory(); //Zwalnianie pamieci zajetej przez gre
    delete game;
    return 0;
}
