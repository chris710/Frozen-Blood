
//////////////////////////////////////////
//
//      GŁÓWNA KLASA JEDNOSTEK
//
/////////////////////////////////////////
#include "game.h"

class unit
{
    public:
        int health;     //punkty zdrowia, domyślnie 100
        int Xpos,Ypos;      //położenie X-owe i Y-owe na mapie
        int attack;     //poziom ataku
        int defence;    //poziom obrony
        string type;    //rodzaj jednostki
};
