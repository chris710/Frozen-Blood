//////////////////////////////////////////////////
///                   GAME                     ///
///                  game.h                    ///
//////////////////////////////////////////////////

#ifndef GAME_H
#define GAME_H

///BIBLIOTEKA ALLEGRO
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

///POTRZEBNE BIBLIOTEKI
#include <vector>
#include <string>

///WYSUNIETE DEKLARACJE
class unitInstance;

///POTRZEBNE PLIKI
#include "units.h"


class gameInstance
{
    public:
        gameInstance() { } //Konstruktor, wywoluje wczytywanie danych
        ~gameInstance() { }; //Destruktor, wywoluje czyszczenie pamieci
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
        ///KONTROLA OKNA
        bool CreateDisplay(int ScreenHeight,int ScreenWidth); //Tworzenie ekranu gry o podanej rozdzielczosci
        void ReleaseMemory(); //Zwalnianie pamieci zajetej przez Allegro, np. timer czy keystate
        void DisplayMessage(std::string title,std::string message); //Wyswietlanie wiadomosci na ekran

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

        ///SWIAT GRY
        void CreateUnit(std::string type);
        std::vector<unitInstance*> unitList;

        ///GRACZE
        int GetCurrentPlayer();
        void EndTurn();

    private:
        ///GRACZE
        std::vector<std::string> playerList;
        int playerCurrent;

        ///KONTROLA OKNA
        ALLEGRO_DISPLAY* displayAL; //Uchwyt okna

};

#endif
