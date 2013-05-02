//////////////////////////////////////////////////
///                   GAME                     ///
///                  game.h                    ///
//////////////////////////////////////////////////

#ifndef GAME_H
#define GAME_H

///POTRZEBNE BIBLIOTEKI
#include <vector>
#include <string>

///POTRZEBNE PLIKI

class gameInstance
{
    public:
        struct unitStruct
        {
            std::string name;
            std::string bitmap;
            int stats; //do zmiany
        };
        struct soundStruct
        {
            std::string name;
            std::string file;
        };
        bool PushUnitCFG(unitStruct* unit); //Dodawanie do listy jednostek
        bool PushSoundCFG(unitStruct* unit); //Dodawanie do listy dzwiekow
        bool ResourceLoader(); //Ladowanie calych plikow danych
        bool ResourceUnloader(); //Usuwanie calych list danych

    private:
        gameInstance() { ResourceLoader(); } //Konstruktor, wywoluje wczytywanie danych
        ~gameInstance() { ResourceUnloader(); }; //Destruktor, wywoluje czyszczenie pamieci

        std::vector<unitStruct*> unitList; //Listy dostepnych plikow jednostek oraz innych assetow
        std::vector<soundStruct*> soundList;

};

#endif
