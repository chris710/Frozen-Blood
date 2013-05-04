////////////////////////////////
///
///         EDITOR.CPP
///
////////////////////////////////

///POTRZEBNE PLIKI
#include "editor.h"





///FUNKCJE


//////////////////////////////////////////////////////////////////////////
//
//      CREATE DISPLAY - TWORZY OKNO EDYTORA I INICJALIZUJE ALLEGRO
//
//////////////////////////////////////////////////////////////////////////
bool editor::createDisplay(int ScreenHeight,int ScreenWidth)
{
    //ALLEGRO_DISPLAY - tworzenie ektranu gry
    if(!al_init()) //Inicjalizacja Allegro, jezeli sie nie uda, zamykamy program
    {
        al_show_native_message_box(NULL,NULL,NULL,"Nie udalo sie zainicjalizowac Allegro 5.",NULL,NULL);
        return false;
    }
    ALLEGRO_DISPLAY *display;
    display = al_create_display(ScreenWidth,ScreenHeight); //Tworzenie ekranu gry korzystajac z uchwytu okna
    if(!display) //Jezeli sie udalo sie stworzyc okna, zamykamy program
    {
        al_show_native_message_box(NULL,NULL,NULL,"Nie udalo sie utworzyc obrazu.",NULL,NULL);
        return false;
    }

    //ALLEGRO - Uruchamianie dodatkow i potrzebnych funkcji
    al_install_mouse();
    al_install_keyboard();
    al_init_image_addon();
    return true;
}


/*
/////////////////////////////////////////////////////////////
//
//      RELEASE MEMORY - ZWALNIA PAMIĘĆ PO ALLEGRO
//
/////////////////////////////////////////////////////////////
void editor::releaseMemory()
{
    if(eventQueueAL) al_destroy_event_queue(eventQueueAL); //niszcenie timerow i list zdarzen ALLEGRO
    if(gameTimerAL) al_destroy_timer(gameTimerAL);
    if(mouseCursor) al_destroy_mouse_cursor(mouseCursor);
    if(mouseCursorPressed) al_destroy_mouse_cursor(mouseCursorPressed);
    if(displayAL) al_destroy_display(displayAL); //Zwalnianie ekranu
}*/




//////////////////////////////////////////////////////
//
//      CREATE MAP - TWORZY NOWĄ, PUSTĄ MAPĘ
//
///////////////////////////////////////////////////////
void map::createMap()
{
    for (int i=0; i<Ysize; i++)
    {
        for(int j=0; j<Xsize; j++)
        {

            mapa[i][j].image;         ///TO juz jest tile
        }

    }
}



//////////////////////////////////////////////////////
//
//      FILL WATER - WYPEŁNIA MAPĘ WODĄ
//
/////////////////////////////////////////////////////
void map::fillWater(string name)
{

}
