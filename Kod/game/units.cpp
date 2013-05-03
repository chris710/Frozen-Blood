//////////////////////////////////////////////////
///                  UNITS                     ///
///                units.cpp                   ///
//////////////////////////////////////////////////

///POTRZEBNE PLIKI
#include "units.h"

unitInstance::unitInstance(std::string type,gameInstance* game) //Ladowanie danych o jednostce z listy
{
    owner = game->GetCurrentPlayer();
    for(int i=0;i<game->unitLib.size();i++)
    {
        if(game->unitLib[i]->name==type)
        {
            HP = game->unitLib[i]->HP;
            attack = game->unitLib[i]->attack;
            defence = game->unitLib[i]->defence;
            bitmap = game->unitLib[i]->bitmap;
            ful = i;
            ID = time(NULL);
            break;
        }
    }
    for(int i=0;i<game->soundLib.size();i++)
    {
        if(game->soundLib[i]->name==game->unitLib[ful]->sound_movement) sound_movement=game->soundLib[i]->file;
        if(game->soundLib[i]->name==game->unitLib[ful]->sound_attack) sound_attack=game->soundLib[i]->file;
        if(game->soundLib[i]->name==game->unitLib[ful]->sound_death) sound_death=game->soundLib[i]->file;
    }
}
