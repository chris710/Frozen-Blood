//////////////////////////////////////////////////
///                MAP RENDER                  ///
///              map_render.cpp                ///
//////////////////////////////////////////////////

///POTRZEBNE PLIKI
#include "game.h"


bool gameInstance::RenderMap()
{
    if(!mapLoaded) return false; //Jezeli nie ma wczytanej mapy to konczymy
    int h = 0,w = 0;
    for(int i=0;i<gameMap.size();i++) //Przechodzimy przez wszystkie pola pobierajac bitmapy z gameMap i je wypisujemy
    {
        switch(gameMap[i]->rotation)
        {
            default:
            case 0: al_draw_bitmap(gameMap[i]->tile,h*96+mapOffset[1],w*96+mapOffset[0],NULL); break;
           // case 1: al_draw_bitmap(gameMap[i]->tile,h*96+mapOffset[1],w*96+mapOffset[0],ALLEGRO_FLIP_HORIZONTAL); break;
           // case 2: al_draw_bitmap(gameMap[i]->tile,h*96+mapOffset[1],w*96+mapOffset[0],ALLEGRO_FLIP_VERTICAL); break;
            //case 3: al_draw_bitmap(gameMap[i]->tile,h*96+mapOffset[1],w*96+mapOffset[0],ALLEGRO_FLIP_VERTICAL|ALLEGRO_FLIP_HORIZONTAL); break;
        }
        w++; //Zwiekszamy w
        if(w==mapSize[0]) { h++; w=0; }
    }
     for(int i=0;i<gameMap.size();i++)
       if(gameMap[i]->currentUnit!=NULL) al_draw_bitmap(gameMap[i]->currentUnit->bitmap,gameMap[i]->currentUnit->xPos*96+mapOffset[1],gameMap[i]->currentUnit->yPos*96+mapOffset[0],NULL);

    return true;
}

bool gameInstance::RenderFieldBox()
{
    if(fieldBox!=NULL) //jezeli jest fieldbox
    {
        int x,y;
        x=(int)mouseState.x;
        y=(int)mouseState.y; //pobierz pozycje myszy

        if(x>=0 && x<=(mapSize[1]*96-1) && y>=0 && y<=(mapSize[0]*96-1)) //jezeli na mapie
        {
                x/=96;
                y/=96; //to rysuj na odpowiednim polu
                al_draw_bitmap(fieldBox,x*96+(mapOffset[1]%96),y*96+(mapOffset[0]%96),NULL);
                std::cout << "[DISPLAY] FIELDBOX UPTADED AT FIELD " << x+(abs(mapOffset[1])/96) << " " << y+(abs(mapOffset[0])/96) << std::endl;
        }
    }
}

bool gameInstance::MapScroll()
{
    int x = mouseState.x;
    int y = mouseState.y; //pobierz pozycje myszy

    if(x>=0 && x<=50  && mapSize[1]*96>width) //W LEWO; jezeli mysz na odpowiedniej pozycji to przewijaj
    {
      mapOffset[1]+=4;
    }
    else if(x<=width && x>=width-50  && mapSize[1]*96>width) // W PRAWO
    {
        mapOffset[1]-=4;
    }
    else if(y>=0 && y<=50 && mapSize[0]*96>height)
    {
        mapOffset[0]+=4;
    }// DO GORY
    else if(y<=height && y>=height-50 && mapSize[0]*96>height) //DO DOLU
    {
        mapOffset[0]-=4;
    }
    else
    {
        if(mapOffset[0]%96!=0) //poprawiamy przewiniecie do pelnego kafelka
        {
            if(mapOffset[0]>=-48) mapOffset[0]++; else mapOffset[0]--;
            return true;
        }
        if(mapOffset[1]%96!=0)
        {
            if(mapOffset[1]>=-48) mapOffset[1]++; else mapOffset[1]--;
            return true;
        }
        if(mapOffset[0]%96==0 && mapOffset[1]%96==0) return false;
    }
    if(mapOffset[1]>0) { mapOffset[1]=0; return false; } //jezeli poza mapa to reset pozycji
    if(abs(mapOffset[1])+width>mapSize[1]*96 && mapSize[1]*96>width) { mapOffset[1]=-1*abs(mapSize[1]*96-width); return false; }
    if(mapOffset[0]>0) { mapOffset[0]=0; return false; }
    if(mapSize[0]*96+mapOffset[0]<height && mapSize[0]*96>height) { mapOffset[0] = height-mapSize[0]*96; return false; }
    return true;
}
bool gameInstance::RenderUnitRange() //rysowanie zasiegu jednostek,do przerobienia
{
    if(!mapDrawUnitRange || selectedUnit==NULL) return false;
    for(int i=-1*selectedUnit->movementRange;i<=selectedUnit->movementRange;i++)
    {
        for(int j=-1*selectedUnit->movementRange;j<=selectedUnit->movementRange;j++)
        {
            if(selectedUnit->xPos+i>=0 && selectedUnit->yPos+j>=0 && selectedUnit->xPos+i<mapSize[0] && selectedUnit->yPos+j<mapSize[1])
            al_draw_bitmap(highlight,(selectedUnit->xPos+i)*96+mapOffset[1],(selectedUnit->yPos+j)*96+mapOffset[0],NULL);
        }
    }
}
