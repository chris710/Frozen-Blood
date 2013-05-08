//////////////////////////////////////////////////
///                  UNITS                     ///
///                units.cpp                   ///
//////////////////////////////////////////////////

///POTRZEBNE PLIKI
#include "unit.h"

unitInstance::unitInstance(std::string type,gameInstance* game, int x, int y) //Ladowanie danych o jednostce z listy
{
    owner = game->GetCurrentPlayer();
    xPos = x;
    yPos = y;
    for(int i=0;i<game->unitLib.size();i++)
    {
        if(game->unitLib[i]->name==type)
        {
            name = type;
            HP = game->unitLib[i]->HP;
            attack = game->unitLib[i]->attack;
            defence = game->unitLib[i]->defence;
            bitmap = game->unitLib[i]->bitmap;
            ful = i; //Fast unit list access
            ID = game->unitLib.size(); //Niepowtarzalny ID jednostki
            attackRange = 1;
            movementRange = 2;
            tired = false;
            movement = false;
            moveTo[0] = 0;
            moveTo[1] = 0;
            break;
        }
    }
    for(int i=0;i<game->soundLib.size();i++)
    {
        if(game->soundLib[i]->name==game->unitLib[ful]->sound_movement) sound_movement=game->soundLib[i]->file; //Pointery na pliki dzwiekowe
        if(game->soundLib[i]->name==game->unitLib[ful]->sound_attack) sound_attack=game->soundLib[i]->file;
        if(game->soundLib[i]->name==game->unitLib[ful]->sound_death) sound_death=game->soundLib[i]->file;
    }
}
