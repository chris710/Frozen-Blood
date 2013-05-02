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
    std::ifstream resources[3];
    resources[0].open("game/units.cfg");
    resources[1].open("game/sounds.cfg");
    resources[2].open("game/tiles.cfg");

    if(!resources[0].good()) { DisplayMessage("Blad!","Nie mozna otworzyc pliku units.cfg!"); return false; }
    if(!resources[1].good()) { DisplayMessage("Blad!","Nie mozna otworzyc pliku sounds.cfg!"); return false; }
    if(!resources[2].good()) { DisplayMessage("Blad!","Nie mozna otworzyc pliku tiles.cfg!"); return false; }

    std::string line;

    for(int i=0;i<3;i++)
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
                PushUnitCFG(name,file,stats);
            }
            if(line=="SOUND")
            {
                std::string name,file;
                getline(resources[i],name);
                getline(resources[i],file);
                PushSoundCFG(name,file);
            }
            if(line=="OBJ")
            {
                std::string name,file;
                getline(resources[i],name);
                getline(resources[i],file);
                PushObjCFG(name,file);
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
        al_destroy_sample(soundList[i]->file);
        delete soundList[i];
    }
        for(int i=0;i<objList.size();i++)
    {
        al_destroy_bitmap(objList[i]->bitmap);
        delete objList[i];
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
    sound.file = al_load_sample(file.c_str());
    if(!sound.file) { return false; }
    soundList.push_back(&sound);
    return true;
}
bool gameInstance::PushObjCFG(std::string name,std::string file)
{
    objStruct obj;
    obj.name=name;
    obj.bitmap = al_load_bitmap(file.c_str());
    if(!obj.bitmap) { return false; }
    objList.push_back(&obj);
    return true;
}
