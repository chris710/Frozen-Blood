//////////////////////////////////////////////////
///                MAP LOADER                  ///
///              map_loader.cpp                ///
//////////////////////////////////////////////////

///POTRZEBNE PLIKI
#include "game.h"

bool gameInstance::LoadMap(std::string file)
{
    std::ifstream plik;                       //zmienna plik okre�la plik z map� do otwarcia
    std::string mapa="res/maps/"+file+".map";      //string mapa to po��czenie �cie�ki pliku z map� oraz argumentu z nazw� pliku
    plik.open(mapa.c_str());                 //otwieramy plik

    std::string message="Nie mozna otworzyc pliku z mapa "+file+"!";
    if(!plik.good()) { DisplayMessage("Blad!",message); return false; }      //sprawdzamy czy mo�na otworzy� plik z map�
    std::string line;
    getline(plik,line);
    if(line=="[NAME]") getline(plik,mapName);  else return false;
    getline(plik,line);
    if(line=="[SIZE]") plik >> mapSize[0] >> mapSize[1]; else return false;

    gameMap = new mapTile*[mapSize[0]];
    for(int i=0;i<mapSize[0];i++) gameMap[i] = new mapTile[mapSize[i]];

    bool eof = false;
    for(int i=0;i<mapSize[0];i++)
    {
        if(eof) break;
        for(int j=0;j<mapSize[1];j++)
        {
            if(plik.eof()) { eof=true; break; }
            else
            {
                getline(plik,line);
                if(line=="[TILE]")
                {
                    getline(plik,line);
                    for(int k=0;k<objLib.size();k++) if(objLib[k]->name==line) gameMap[i][j].tile=objLib[k]->bitmap;
                }   else return false;
                getline(plik,line);
                if(line=="[EFFECT]")  getline(plik,gameMap[i][j].effect);   else return false;
                getline(plik,line);
                if(line=="[ROTATION]")  plik >> gameMap[i][j].rotation;   else return false;
            }
        }
    }
    return true;
}
void gameInstance::UnloadMap()
{
    for(int i=0;i<mapSize[0];i++) delete [] gameMap[i];
    delete [] gameMap;
    mapName="";
    mapSize[0]=NULL;
    mapSize[1]=NULL;
    unitList.clear();
}
