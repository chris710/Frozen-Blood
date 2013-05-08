//////////////////////////////////////////////////
///                   MOUSE                    ///
///                mouse.cpp                   ///
//////////////////////////////////////////////////

///POTRZEBNE PLIKI
#include "game.h"

void gameInstance::MapClick()
{
    int x,y;
    x=(int)mouseState.x; //pobieramy pozycje myszy
    y=(int)mouseState.y;
    x/=96;
    y/=96;

    x=x+(abs(mapOffset[1])/96); //uzyskujemy odpowiedni kafelek
    y=y+(abs(mapOffset[0])/96);

    //std::cout << x+y*mapSize[1] << std:: endl;
    //Klikniecie na kafelek
    if(selectedUnit==NULL && gameMap[x+y*mapSize[1]]->currentUnit==NULL) return;
    else if(selectedUnit!=NULL && gameMap[x+y*mapSize[1]]->currentUnit==NULL)
    {
        //Move
    }
    else
    {
        if(selectedUnit!=gameMap[x+y*mapSize[1]]->currentUnit) selectedUnit = gameMap[x+y*mapSize[1]]->currentUnit; // jezeli obecnie zaznaczona jednostka to ta na ktora kliknieto
        else { selectedUnit = NULL; mapDrawUnitRange=false; std::cout << "[MAP] CS" << std::endl;} // to odznacz
        if(!mapDrawUnitRange && selectedUnit!=NULL)  { std::cout << "[MAP] UNIT " << selectedUnit->name << " (ID: " << selectedUnit->ID << ") SELECTED" << std::endl; mapDrawUnitRange=true; } //albo rysuj jej zasieg
        //else sprawdz co jest na klknietym polu(ruch czy atak)
    }
}

