//////////////////////////////////////////////////
///                MAP RENDER                  ///
///              map_render.cpp                ///
//////////////////////////////////////////////////

///POTRZEBNE PLIKI
#include "game.h"


bool gameInstance::RenderMap()
{
    if(!mapLoaded) return false; //Jezeli nie ma wczytanej mapy to konczymy
    int height = 0,width = 0;
    for(int i=0;i<gameMap.size();i++) //Przechodzimy przez wszystkie pola pobierajac bitmapy z gameMap i je wypisujemy
    {
        switch(gameMap[i]->rotation)
        {
            default:
            case 0: al_draw_bitmap(gameMap[i]->tile,height*96,width*96,NULL); break;
            case 1: al_draw_bitmap(gameMap[i]->tile,height*96,width*96,ALLEGRO_FLIP_HORIZONTAL); break;
            case 2: al_draw_bitmap(gameMap[i]->tile,height*96,width*96,ALLEGRO_FLIP_VERTICAL); break;
            case 3: al_draw_bitmap(gameMap[i]->tile,height*96,width*96,ALLEGRO_FLIP_VERTICAL|ALLEGRO_FLIP_HORIZONTAL); break;
        }
        width++; //Zwiekszamy width
        if(width==mapSize[0]) { height++; width=0; }
    }
    return true;
}

bool gameInstance::RenderFieldBox()
{
    if(fieldBox!=NULL)
    {
        int mouseX,mouseY;
        mouseX=(int)mouseState.x;
        mouseY=(int)mouseState.y;

        if(mouseX>=0 && mouseX<=mapSize[1]*96-1 && mouseY>=0 && mouseY<=mapSize[0]*96-1)
        {
                mouseX/=96;
                mouseY/=96;
                al_draw_bitmap(fieldBox,mouseX*96,mouseY*96,NULL);
                std::cout << "[DISPLAY] FIELDBOX UPTADED AT FIELD " << mouseX << " " << mouseY << std::endl;
        }
    }
}
