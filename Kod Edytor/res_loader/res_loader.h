//////////////////////////////////////////////////
///                   RESLOADER                ///
///                  res_loader.h              ///
//////////////////////////////////////////////////

#ifndef RES_LOADER_H
#define RES_LOADER_H

#include "../editor/editor.h"

class resInstance
{
    public:
        resInstance() {} //Konstruktor, wywoluje wczytywanie danych
        ~resInstance() { }; //Destruktor, wywoluje czyszczenie pamieci
        struct unitStruct //Struktura jednostki na liscie
        {
            std::string name; //Zawiera domyslne dane o jednostce
            ALLEGRO_BITMAP* bitmap;
            int HP,attack,defence,ful;
            std::string sound_movement,sound_attack,sound_death;
        };
        struct soundStruct
        {                       //Element listy dzwiekow
            std::string name;
            ALLEGRO_SAMPLE* file;
        };
        struct objStruct
        {                       //Element listy obiektow
            std::string name;
            ALLEGRO_BITMAP* bitmap;
        };
        struct mapTile //Kafelek mapy
        {
            ALLEGRO_BITMAP* tile;
            std::string effect;
            int rotation;
        };
        ALLEGRO_BITMAP* defaultTile;
        ///RESOURCE LOADER
        bool PushUnitCFG(std::string name,std::string file,int HP,int attack, int defence,std::string sound_movement,
                         std::string sound_attack,std::string sound_death); //Dodawanie do listy jednostek
        bool PushSoundCFG(std::string name,std::string file); //Dodawanie do listy dzwiekow
        bool PushObjCFG(std::string name,std::string file); //Dodawanie do listy dzwiekow
        bool ResourceLoader(); //Ladowanie calych list danych
        void ResourceUnloader(); //Usuwanie calych list danych

        std::vector<unitStruct*> unitLib; //Listy dostepnych plikow jednostek oraz innych assetow
        std::vector<soundStruct*> soundLib;
        std::vector<objStruct*> objLib;

};

#endif
