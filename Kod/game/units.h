//////////////////////////////////////////////////
///                  UNITS                     ///
///                 units.h                    ///
//////////////////////////////////////////////////

#ifndef UNITS_H
#define UNITS_H

///POTRZEBNE PLIKI
#include "game.h"

class unitInstance
{
    public:
        unitInstance(std::string type,gameInstance* game); //Konstruktor
        ~unitInstance() {} //Destruktor
        int HP;     //punkty zdrowia, domy�lnie 100
        int Xpos,Ypos;      //po�o�enie X-owe i Y-owe na mapie
        int attack;     //poziom ataku
        int defence;    //poziom obrony
        int ful;
        ALLEGRO_SAMPLE* sound_movement;
        ALLEGRO_SAMPLE* sound_attack;
        ALLEGRO_SAMPLE* sound_death;
        ALLEGRO_BITMAP* bitmap; //bitmapa
};

#endif
