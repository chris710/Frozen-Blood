//////////////////////////////////////////////////
///                  EDITOR                    ///
///                editor.cpp                 ///
//////////////////////////////////////////////////


///POTRZEBNE PLIKI
#include "editor.h"

bool editorInstance::Init()
{
    //ALLEGRO_DISPLAY - tworzenie ektranu gry
    if(!al_init()) //Inicjalizacja Allegro, jezeli sie nie uda, zamykamy program
    {
        al_show_native_message_box(NULL,NULL,NULL,"Nie udalo sie zainicjalizowac Allegro 5.",NULL,NULL);
        return false;
    }

    //ALLEGRO - Uruchamianie dodatkow i potrzebnych funkcji
    al_install_mouse();
    al_install_keyboard();
    al_install_audio();
    al_init_image_addon();
    al_init_acodec_addon();
    return true;
}

bool editorInstance::CreateDisplay(int ScreenHeight,int ScreenWidth)
{
    displayAL = al_create_display(ScreenWidth,ScreenHeight); //Tworzenie ekranu gry korzystajac z uchwytu okna
    if(!displayAL) //Jezeli sie udalo sie stworzyc okna, zamykamy program
    {
        al_show_native_message_box(NULL,NULL,NULL,"Nie udalo sie utworzyc obrazu.",NULL,NULL);
        return false;
    }
    displayH=ScreenHeight;
    displayW=ScreenWidth;
    return true;
}

void editorInstance::ReleaseMemory()
{
    UnloadMap(); //Jezeli jest co zwalniac, to usuwamy mape
    //Czyszczenie jednostek na polu bitwy, bitmapy zwalnia Resource Loader
    if(eventQueueAL) al_destroy_event_queue(eventQueueAL); //niszcenie timerow i list zdarzen ALLEGRO
    if(editorTimerAL) al_destroy_timer(editorTimerAL);
    if(displayAL) al_destroy_display(displayAL); //Zwalnianie ekranu
}
void editorInstance::fillWater(resInstance* resLib)
{
    if(!mapLoaded || resLib->defaultTile==NULL) return;
    for(int i=0;i<mapSize[0];i++)
        for(int j=0;j<mapSize[1];j++)
        {
            mapTile* tile = new mapTile;
            tile->tile=resLib->defaultTile;
            tile->effect="unwalkable";
            tile->rotation=0;
            gameMap.push_back(tile);
        }
}
