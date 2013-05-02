//////////////////////////////////////////////////
///             RESOURCE LOADER                ///
///              res_loader.cpp                ///
//////////////////////////////////////////////////

///POTRZEBNE BIBLIOTEKI
#include <fstream>

///POTRZEBNE PLIKI
#include "game.h"

bool gameInstance::ResourceLoader()
{
    std::ifstream resources[2];
    resources[0].open("game/units.cfg");
    resources[1].open("game/sounds.cfg");

    if(!resources[0].good()) { DisplayMessage("Blad!","Nie mozna otworzyc pliku units.cfg!"); return false; }
    if(!resources[1].good()) { DisplayMessage("Blad!","Nie mozna otworzyc pliku sounds.cfg!"); return false; }

    std::string line;

    for(int i=0;i<2;i++)
    {
        while(!resources[i].eof())
        {
            getline(resources[i],line);
            if(line=="UNIT")
            {
                std::string name,file;
                int stats;//Do dopisania
                getline(resources[i],name);
                getline(resources[i],file);
                resources[i]>>stats;
                if(!PushUnitCFG(name,file,stats)) { DisplayMessage("Krytyczny blad!","Ladowanie danych nie udalo sie."); return false; }
            }
            if(line=="SOUND")
            {
                std::string name,file;
                getline(resources[i],name);
                getline(resources[i],file);
                if(!PushSoundCFG(name,file)) return false;
            }
        }
        resources[i].close();
    }
    return true;
}

void gameInstance::ResourceUnloader()
{
    for(int i=0;i<unitList.size();i++)
    {
        al_destroy_bitmap(unitList[i]->bitmap);
        delete unitList[i];
    }
    for(int i=0;i<soundList.size();i++)
    {
        //al_delete_sound(unitList[i].sound);
        delete soundList[i];
    }
}

bool gameInstance::PushUnitCFG(std::string name,std::string file,int stats)
{
    unitStruct unit;
    unit.name=name;
    unit.bitmap = al_load_bitmap(file.c_str());
    if(!unit.bitmap) { return false; }
    unit.stats=stats;
    unitList.push_back(&unit);
    return true;
}
bool gameInstance::PushSoundCFG(std::string name,std::string file)
{
    soundStruct sound;
    sound.name=name;
    //if(!sound.sound = al_load_sound(file.c_str())) return false;
    soundList.push_back(&sound);
    return true;
}

