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

///POTRZEBNE PLIKI

class gameInstance
{
    public:
        gameInstance() { } //Konstruktor, wywoluje wczytywanie danych
        ~gameInstance() { }; //Destruktor, wywoluje czyszczenie pamieci
        struct unitStruct
        {
            std::string name;
            ALLEGRO_BITMAP* bitmap;
            int stats; //do zmiany
        };
        struct soundStruct
        {
            std::string name;
            ALLEGRO_SAMPLE* file;
        };
        struct objStruct
        {
            std::string name;
            ALLEGRO_BITMAP* bitmap;
        };
        ///KONTROLA OKNA
        bool CreateDisplay(int ScreenHeight,int ScreenWidth); //Tworzenie ekranu gry o podanej rozdzielczosci
        void ReleaseMemory(); //Zwalnianie pamieci zajetej przez Allegro, np. timer czy keystate
        void DisplayMessage(std::string title,std::string message); //Wyswietlanie wiadomosci na ekran

        ///RESOURCE LOADER
        bool PushUnitCFG(std::string name,std::string file,int stats); //Dodawanie do listy jednostek
        bool PushSoundCFG(std::string name,std::string file); //Dodawanie do listy dzwiekow
        bool PushObjCFG(std::string name,std::string file); //Dodawanie do listy dzwiekow
        bool ResourceLoader(); //Ladowanie calych list danych
        void ResourceUnloader(); //Usuwanie calych list danych

    private:
        ///KONTROLA OKNA
        ALLEGRO_DISPLAY* display_AL;

        ///RESOURCE LOADER
        std::vector<unitStruct*> unitList; //Listy dostepnych plikow jednostek oraz innych assetow
        std::vector<soundStruct*> soundList;
        std::vector<objStruct*> objList;
};

#endif
