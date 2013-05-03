//////////////////////////////////////////////////
///                MAP RENDER                  ///
///              map_render.cpp                ///
//////////////////////////////////////////////////

///POTRZEBNE PLIKI
#include "game.h"


bool gameInstance::RenderMap()
{
    if(!mapLoaded) return false;
    int h,w;
    h=0;w=0;

    for(int i=0;i<gameMap.size();i++)
    {
        al_draw_bitmap(gameMap[i]->tile,h*96,w*96,NULL);
        w++;
        if(w==mapSize[0]) { h++; w=0; }
    }
    return true;
}
