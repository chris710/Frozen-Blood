//////////////////////////////////////////////////
///                   MAIN                     ///
///                 main.cpp                   ///
//////////////////////////////////////////////////

///BIBLIOTEKA ALLEGRO
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


///POTRZEBNE PLIKI
#include "game/game.h"


///DEFINICJE PROGRAMU
#define ScreenHeight 600
#define ScreenWidth 800

int main()
{
    //ALLEGRO_DISPLAY - tworzenie ektranu gry
    ALLEGRO_DISPLAY *display_AL; //Uchwyt do ektranu
    if(!al_init()) //Inicjalizacja Allegro, jezeli sie nie uda, zamykamy program
    {
        al_show_native_message_box(NULL,NULL,NULL,"Nie udalo sie zainicjalizowac Allegro 5.",NULL,NULL);
        return -1;
    }

    display_AL = al_create_display(ScreenWidth,ScreenHeight); //Tworzenie ekranu gry korzystajac z uchwytu okna
    if(!display_AL) //Jezeli sie udalo sie stworzyc okna, zamykamy program
    {
        al_show_native_message_box(NULL,NULL,NULL,"Nie udalo sie utworzyc obrazu.",NULL,NULL);
        return -1;
    }

    //ALLEGRO - Uruchamianie dodatkow i potrzebnych funkcji
    al_install_keyboard();
    al_install_audio();
    al_init_image_addon();
    al_init_acodec_addon();

    //ALLEGRO - Zwalnianie pamieci i zamkniecie programu
    al_destroy_display(display_AL);
    return 0;
}
