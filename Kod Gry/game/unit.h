//////////////////////////////////////////////////
///                  UNITS                     ///
///                 units.h                    ///
//////////////////////////////////////////////////

#ifndef UNIT_H
#define UNIT_H

///POTRZEBNE PLIKI
#include "game.h"

///WYSUNIETE DEKLARACJE
class gameInstance;

class unitInstance
{
    public:
        unitInstance(std::string type,gameInstance* game, int x, int y); //Konstruktor
        ~unitInstance() {} //Destruktor
        std::string name;
        int HP;     //punkty zdrowia, domyœlnie 100
        int xPos,yPos;      //po³o¿enie X-owe i Y-owe na mapie
        int attack;     //poziom ataku
        int defence;    //poziom obrony
        int ful;
        int owner;
        int exp;    //ilość zdobytego doświadczenia
        int level;    //poziom doświadczenia
        int ID;
        int attackRange;
        int movementRange;
        bool tired; //czy juz uzyta
        bool movement;
        int moveTo[2]; //x y ruch na pole

        ALLEGRO_SAMPLE* sound_movement;
        ALLEGRO_SAMPLE* sound_attack;
        ALLEGRO_SAMPLE* sound_death;
        ALLEGRO_BITMAP* bitmap; //bitmapa
};

#endif
