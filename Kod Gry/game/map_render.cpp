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
            case 0: al_draw_bitmap(gameMap[i]->tile,height*96+offset[1],width*96+offset[0],NULL); break;
            case 1: al_draw_bitmap(gameMap[i]->tile,height*96+offset[1],width*96+offset[0],ALLEGRO_FLIP_HORIZONTAL); break;
            case 2: al_draw_bitmap(gameMap[i]->tile,height*96+offset[1],width*96+offset[0],ALLEGRO_FLIP_VERTICAL); break;
            case 3: al_draw_bitmap(gameMap[i]->tile,height*96+offset[1],width*96+offset[0],ALLEGRO_FLIP_VERTICAL|ALLEGRO_FLIP_HORIZONTAL); break;
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

        if(mouseX>=0 && mouseX<=(mapSize[1]*96-1+(offset[1]%96)) && mouseY>=0 && mouseY<=(mapSize[0]*96-1+(offset[0]%96)))
        {
                mouseX/=96;
                mouseY/=96;
                al_draw_bitmap(fieldBox,mouseX*96+(offset[1]%96),mouseY*96+(offset[0]%96),NULL);
                std::cout << "[DISPLAY] FIELDBOX UPTADED AT FIELD " << mouseX+(abs(offset[1])/96) << " " << mouseY+(abs(offset[0])/96) << std::endl;
        }
    }
}

bool gameInstance::MapScroll()
{
    int x = mouseState.x;
    int y = mouseState.y;

    if(x>=0 && x<=30) //W LEWO
    {
      offset[1]+=4;
    }
    else if(x<=width && x>=width-30) // W PRAWO
    {
        offset[1]-=4;
    }
    else if(y>=0 && y<=30)
    {
        offset[0]+=4;
    }// DO GORY
    else if(y<=height && y>=height-30) //DO DOLU
    {
        offset[0]-=4;
    }
    else
    {
        if(offset[0]%96!=0)
        {
            if(offset[0]>=-48) offset[0]++; else offset[0]--;
            return true;
        }
        if(offset[1]%96!=0)
        {
            if(offset[1]>=-48) offset[1]++; else offset[1]--;
            return true;
        }
        if(offset[0]%96==0 && offset[1]%96==0) return false;
    }
    if(offset[1]>0) { offset[1]=0; return false; }
    if(abs(offset[1])+width>mapSize[1]*96) { offset[1]=-1*abs(mapSize[1]*96-width); return false; }
    if(offset[0]>0) { offset[0]=0; return false; }
    if(mapSize[0]*96+offset[0]<height) { offset[0] = height-mapSize[0]*96; return false; }
    return true;
}
