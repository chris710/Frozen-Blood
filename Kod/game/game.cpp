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

    display_AL = al_create_display(ScreenWidth,ScreenHeight); //Tworzenie ekranu gry korzystajac z uchwytu okna
    if(!display_AL) //Jezeli sie udalo sie stworzyc okna, zamykamy program
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
    al_destroy_display(display_AL);
}

void gameInstance::DisplayMessage(std::string title,std::string message)
{
    al_show_native_message_box(display_AL,NULL,title.c_str(),message.c_str(),NULL,NULL);
}
