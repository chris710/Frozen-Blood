//////////////////////////////////////////////////
///                MAP LOADER                  ///
///              map_loader.cpp                ///
//////////////////////////////////////////////////

///POTRZEBNE PLIKI
#include "editor.h"

bool editorInstance::LoadMap(std::string file, resInstance* resLib)
{
    if(mapLoaded) return false; //Jezeli istnieje zaladowana mapa to konczymy
    file = "res/maps/"+file+".cfg";
    std::ifstream mapa; //Otwieramy plik mapy i wczytujemy nazwe oraz rozmiar
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
    mapSize[0]=x; //Zapisujemy rozmiar i nazwe do klasy gameInstance
    mapSize[1]=y;

    while(mapSize[0]*mapScale>displayH || mapSize[1]*mapScale>displayW) mapScale-=4;

    while(mapa >> line && !mapa.eof()) //Tak dlugo jak jest cos do wczytania
    {
        mapTile* tile = new mapTile; //Nowy kafelek
        if(line=="[TILE]")
        {
            mapa >> line; //Uzupelniamy dane kafelka
            int k;
            for(k=0;k<resLib->objLib.size();k++)
                if(resLib->objLib[k]->name==line) { tile->tile=resLib->objLib[k]->bitmap; break; }
                else tile->tile=NULL;
            if(tile->tile==NULL) { std::cout << "[objLIB] ERROR - \"" << line << "\" - FILE NOT FOUND" << std::endl; UnloadMap(); return false; }
            if(k>=resLib->objLib.size()) { std::cout << "[objLIB] ERROR - \"" << line << "\" - FILE NOT FOUND" << std::endl; UnloadMap(); return false; }
            mapa >> line;
            tile->effect=line;
            mapa >> x;
            tile->rotation=x;
            gameMap.push_back(tile); //Dodajemy kafelek do obecnej mapy
        }
    }
    mapa.close(); //Zamykamy plik mapy
    std::cout << "[MAP] \"" << file << "\" LOADED" << std::endl;
    return true;
}
void editorInstance::UnloadMap() //Usuwanie mapy z pamieci
{
    if(!mapLoaded) return;
    std::cout << "[MAP] \"" << mapName << "\" UNLOADING" << std::endl; //Usuwanie mapy
    for(int i=0;i<gameMap.size();i++) delete gameMap[i];
    gameMap.clear();
    mapName=""; //Czyscimy nazwe mapy oraz jej rozmiar i jednostki istniejace na mapie
    mapSize[0]=0;
    mapSize[1]=0;
    std::cout << "[MAP] FILE UNLOADED" << std::endl;
    mapLoaded=false; //zadna mapa nie jest zaladowana
}
