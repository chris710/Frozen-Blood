//////////////////////////////////////////////////
///                   GAME                     ///
///                 game.cpp                   ///
//////////////////////////////////////////////////

///POTRZEBNE BIBLIOTEKI

///POTRZEBNE PLIKI
#include "game.h"

bool gameInstance::CreateDisplay(int ScreenHeight,int ScreenWidth)
{
    //ALLEGRO_DISPLAY - tworzenie ektranu gry
    if(!al_init()) //Inicjalizacja Allegro, jezeli sie nie uda, zamykamy program
    {
        al_show_native_message_box(NULL,NULL,NULL,"Nie udalo sie zainicjalizowac Allegro 5.",NULL,NULL);
        return false;
    }

    displayAL = al_create_display(ScreenWidth,ScreenHeight); //Tworzenie ekranu gry korzystajac z uchwytu okna
    if(!displayAL) //Jezeli sie udalo sie stworzyc okna, zamykamy program
    {
        al_show_native_message_box(NULL,NULL,NULL,"Nie udalo sie utworzyc obrazu.",NULL,NULL);
        return false;
    }

    //ALLEGRO - Uruchamianie dodatkow i potrzebnych funkcji
    al_install_keyboard();
    al_install_audio();
    al_init_image_addon();
    al_init_acodec_addon();
}

void gameInstance::ReleaseMemory()
{
    for(int i=0;i<unitList.size();i++) delete unitList[i]; //Czyszczenie jednostek na polu bitwy, bitmapy zwalnia Resource Loader
    al_destroy_display(displayAL); //Zwalnianie ekranu
}

void gameInstance::DisplayMessage(std::string title,std::string message)
{
    al_show_native_message_box(displayAL,NULL,title.c_str(),message.c_str(),NULL,NULL); //Wyswietlanie wiadomosci o podanym tytule i wiadomosci
}

void gameInstance::CreateUnit(std::string type) //Tworzymy jednostke o podanym typie, typ wziety z unitLib
{
    unitInstance unit(type,this);
    this->unitList.push_back(&unit); //jednostka trafia na liste jednostek na mapie, trafia do obecnego gracza
}
int gameInstance::GetCurrentPlayer() //Zwraca numer obecnego gracza
{
    return playerCurrent;
}
void gameInstance::EndTurn() //Przesuwa kolejnosc na nastepnego gracza, albo resetuje ture.
{
    playerCurrent++;
    if(playerCurrent>playerList.size())
    {
        //game->playerAddGold();
        playerCurrent=0;
    }
}
