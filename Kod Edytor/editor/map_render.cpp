//////////////////////////////////////////////////
///                MAP RENDER                  ///
///              map_render.cpp                ///
//////////////////////////////////////////////////

///POTRZEBNE PLIKI
#include "editor.h"


bool editorInstance::RenderMap()
{
    if(!mapLoaded) return false; //Jezeli nie ma wczytanej/nowej mapy to konczymy
    int height = 0,width = 0;
    std::cout << (float)mapScale/96.0*96;
    std::cout << int((float)mapScale/96.0*96);
    for(int i=0;i<gameMap.size();i++) //Przechodzimy przez wszystkie pola pobierajac bitmapy z gameMap i je wypisujemy
    {
        switch(gameMap[i]->rotation)
        {
            default:
            case 0:
                std::cout << "Kafelek: " << width*mapScale << " " << height*mapScale << std::endl;
                al_draw_scaled_bitmap(gameMap[i]->tile,0,0,96,96,height*mapScale,width*mapScale,int((float)(mapScale)/96.0*96),int((float)(mapScale)/96.0*96),NULL);
                break;
            case 1:
                al_draw_scaled_bitmap(gameMap[i]->tile,0,0,96,96,height*mapScale,width*mapScale,int((float)(mapScale)/96.0*96),int((float)(mapScale)/96.0*96),ALLEGRO_FLIP_HORIZONTAL);
                break;
        }
        width++; //Zwiekszamy width
        if(width==mapSize[0]) { height++; width=0; }
    }
    return true;
}
