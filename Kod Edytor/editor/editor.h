//////////////////////////////////////////////////
///                  EDITOR                    ///
///                 editor.h                   ///
//////////////////////////////////////////////////


#ifndef EDITOR_H
#define EDITOR_H

///BIBLIOTEKA ALLEGRO
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

///POTRZEBNE BIBLIOTEKI
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <conio.h>

class resInstance;

///POTRZEBNE PLIKI
#include "../res_loader/res_loader.h"

class editorInstance
{
public:
    editorInstance() { mapLoaded = false; exitEditor = false; int fps = 60; mapScale=96; updateDisplay=true; }
    ///KONTROLA OKNA
    ALLEGRO_DISPLAY* displayAL; //Uchwyt okna głównego
    //ALLEGRO_DISPLAY* displayUI; //uchwyt okna z interfejsem
    ALLEGRO_EVENT_QUEUE *eventQueueAL; //Zdarzenia i timery ALLEGRO
    ALLEGRO_EVENT editorEventsAL;
    ALLEGRO_TIMER *editorTimerAL;
    ALLEGRO_KEYBOARD_STATE keyStateAL;
    bool Init();
    bool CreateDisplay(ALLEGRO_DISPLAY* display, int ScreenHeight,int ScreenWidth); //Tworzenie ekranu gry o podanej rozdzielczosci
    void ReleaseMemory(); //Zwalnianie pamieci zajetej przez Allegro, np. timer czy keystate
    void DisplayMessage(std::string title,std::string message); //Wyswietlanie wiadomosci na ekran
    int fps; //Ilosc klatek na sekunde
    bool updateDisplay; //Zmienna wskazujaca na to, czy trzeba przerysowywac cala mape
    bool exitEditor; //Zmienna sterujace petla gry


    ///MAPA
    bool LoadMap(std::string file, resInstance* resLib);
    bool SaveMap(std::string file);
    void UnloadMap();
    void CreateMap(resInstance* resLib);
    //RENDEROWANIE MAPY W OKNIE PODGLADU
    bool RenderMap();
    bool RenderUI(resInstance* resLib);
    bool mapLoaded;
    void AddTile(resInstance* resLib);
    void fillWater(resInstance* resLib);

    ///EDYTOR OPCJE
    bool displayWindow;
    int displayH;
    int displayW;

    ///STRUKTURA KAFELKA
    struct mapTile //Kafelek mapy
    {
        std::string name;
        ALLEGRO_BITMAP* tile;
        std::string effect;
        int rotation;
    };
    ///MAPA
    std::vector<mapTile*> gameMap;
    int mapSize[2];
    int mapScale;//Zalezna od rozmiaru mapy; skala
    std::string mapName; //Nazwa mapy
};

#endif
