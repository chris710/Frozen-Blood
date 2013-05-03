//////////////////////////////////////////////////
///                MAP LOADER                  ///
///              map_loader.cpp                ///
//////////////////////////////////////////////////

///POTRZEBNE PLIKI
#include "game.h"

bool gameInstance::LoadMap(std::string file)
{
    if(mapLoaded) return false;
    file = "res/maps/"+file+".cfg";
    std::ifstream mapa;
    mapa.open(file.c_str());
    if(!mapa.good()) { std::cout << "[MAP] ERROR - \"" << file << "\" - FILE NOT FOUND" << std::endl; return false; }
    std::cout << "[MAP] \"" << file << "\" LOADING" <<  std::endl;
    std::string name,line;
    int x,y;

    getline(mapa,line);
    if(line=="[NAME]") getline(mapa,name); else { mapa.close(); std::cout << "[MAP] ERROR - [NAME] must be valid" << std::endl; return false; }
    mapLoaded=true;
    getline(mapa,line);
    if(line=="[SIZE]") mapa >> x >> y; else { mapa.close(); std::cout << "[MAP] ERROR - [SIZE] must be valid" << std::endl;return false; }
    mapName=name;
    mapSize[0]=x;
    mapSize[1]=y;

    while(mapa >> line && !mapa.eof())
    {
        mapTile* tile = new mapTile;
        if(line=="[TILE]")
        {
            mapa >> line;
            int k;
            for(k=0;k<objLib.size();k++)
                if(objLib[k]->name==line) { tile->tile=objLib[k]->bitmap; break; }
                else tile->tile=NULL;
            if(tile->tile==NULL) { std::cout << "[objLIB] ERROR - \"" << line << "\" - FILE NOT FOUND" << std::endl; UnloadMap(); return false; }
            if(k>=objLib.size()) { std::cout << "[objLIB] ERROR - \"" << line << "\" - FILE NOT FOUND" << std::endl; UnloadMap(); return false; }
            mapa >> line;
            tile->effect=line;
            mapa >> x;
            tile->rotation=x;
            tile->CurrentUnit=NULL;
            gameMap.push_back(tile);
        }
    }
    mapa.close();
    std::cout << "LOADED MAP: " << file << std::endl;
    return true;
}
void gameInstance::UnloadMap() //Usuwanie mapy z pamieci
{
    if(!mapLoaded) return;
    std::cout << "[MAP] \"" << mapName << "\" UNLOADING" << std::endl;
    for(int i=0;i<gameMap.size();i++) delete gameMap[i];
    gameMap.clear();
    mapName=""; //Czyscimy nazwe mapy oraz jej rozmiar i jednostki istniejace na mapie
    mapSize[0]=0;
    mapSize[1]=0;
    for(int i=0;i<unitList.size();i++) delete unitList[i];
    std::cout << "[MAP] FILE UNLOADED" << std::endl;
    mapLoaded=false;
    unitList.clear();
}
