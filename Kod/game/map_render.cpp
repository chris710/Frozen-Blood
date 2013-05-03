//////////////////////////////////////////////////
///                MAP RENDER                  ///
///              map_render.cpp                ///
//////////////////////////////////////////////////

///POTRZEBNE PLIKI
#include "game.h"


bool gameInstance::RenderMap()
{
    if(!mapLoaded) return false; //Jezeli nie ma wczytanej mapy to konczymy
    int h,w; //Zmienne pomocnicze height i width
    h=0;w=0;

    for(int i=0;i<gameMap.size();i++) //Przechodzimy przez wszystkie pola pobierajac bitmapy z gameMap i je wypisujemy
    {
        al_draw_bitmap(gameMap[i]->tile,h*96,w*96,NULL);
        w++; //Zwiekszamy w
        if(w==mapSize[0]) { h++; w=0; }
        //TODO
        //Efekty oraz rotacja bitmapy podczas rysowania
    }
    return true;
}
