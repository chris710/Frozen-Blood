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

bool editorInstance::CreateDisplay(ALLEGRO_DISPLAY* display, int ScreenHeight,int ScreenWidth)
{
    display = al_create_display(ScreenWidth,ScreenHeight); //Tworzenie ekranu gry korzystajac z uchwytu okna
    if(!display) //Jezeli sie udalo sie stworzyc okna, zamykamy program
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
    //if(displayUI) al_destroy_display(displayUI);
}

/////////////////////////////////
//      WYPEŁNIA MAPĘ WODĄ
/////////////////////////////////
void editorInstance::fillWater(resInstance* resLib)
{
    if(!mapLoaded || resLib->defaultTile==NULL) return;
    for(int i=0;i<mapSize[0];i++)
        for(int j=0;j<mapSize[1];j++)
        {
            mapTile* tile = new mapTile;
            tile->name="snow1";
            tile->tile=resLib->defaultTile;
            tile->effect="unwalkable";
            tile->rotation=0;
            gameMap.push_back(tile);
        }
}


//////////////////////////////
//      TWORZY NOWĄ MAPĘ
//////////////////////////////
void editorInstance::CreateMap(resInstance* resLib)
{
    if(mapLoaded) UnloadMap();
    std::cout<<"Podaj wys. i szer. mapy: "<<std::endl;
    std::cin>>mapSize[0]>>mapSize[1];
    while(mapSize[0]*mapScale>displayH || mapSize[1]*mapScale>displayW) mapScale-=4;

    mapLoaded=true;

    fillWater(resLib);      //wypełnia mapę wodą
}


///////////////////////////////////////////////
//      DODAJE KAFELEK NA MIEJSCE
///////////////////////////////////////////////
void editorInstance::AddTile(resInstance* resLib)
{
    int tile;       //rodzaj kafelka
    int x,y; //współrzędne wybieranego kafelka

    if(!mapLoaded)  return;

    std::cout<<"Podaj wspolrzedne kafelka: "<<std::endl;
    std::cin>>y>>x;

    std::cout<<"Podaj rodzaj kafelka: "<<std::endl;
    std::cin>>tile;
    ///TUTAJ ZROBIĆ WCZYTYWANIE Z BIBLIOTEKI KAFELKÓW/ ZROBIĆ BIBLIOTEKĘ KAFELKÓW
    gameMap[x+y*mapSize[0]]->tile=resLib->objLib[tile-1]->bitmap;     //ustawiamy grafikę
    gameMap[x+y*mapSize[0]]->name=resLib->objLib[tile-1]->name;       //ustawiamy id kafelka


}
