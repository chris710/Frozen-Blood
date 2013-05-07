//////////////////////////////////////////////////
///                   MOUSE                    ///
///                mouse.cpp                   ///
//////////////////////////////////////////////////

#ifndef MOUSE_H
#define MOUSE_H

///POTRZEBNE PLIKI
#include "game.h"

void gameInstance::MapClick()
{
    int x,y;
    if(x>=0 && x<=(mapSize[1]*96-1) && y>=0 && y<=(mapSize[0]*96-1)) //Jezeli klikniecie nastapilo gdzies na mapie
    {
        x=(int)mouseState.x; //pobieramy pozycje myszy
        y=(int)mouseState.y;
        x/=96;
        y/=96;

        x=x+(abs(mapOffset[1])/96); //uzyskujemy odpowiedni kafelek
        y=y+(abs(mapOffset[0])/96);

        //Klikniecie na kafelek

        if(selectedUnit!=gameMap[x+y*mapSize[1]]->currentUnit) selectedUnit = gameMap[x+y*mapSize[1]]->currentUnit; // jezeli obecnie zaznaczona jednostka to ta na ktora kliknieto
        else { selectedUnit = NULL; mapDrawUnitRange=false; std::cout << "[MAP] CS" << std::endl;} // to odznacz
        if(!mapDrawUnitRange && selectedUnit!=NULL)  { std::cout << "[MAP] UNIT " << selectedUnit->name << " (ID: " << selectedUnit->ID << ") SELECTED" << std::endl; mapDrawUnitRange=true; } //albo rysuj jej zasieg
        //else sprawdz co jest na klknietym polu(ruch czy atak)
    }
}


#endif
