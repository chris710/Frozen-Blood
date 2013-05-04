/////////////////////////
///
///     EDITOR.H
///
/////////////////////////
#ifndef EDITOR_H
#define EDITOR_H




//      TO-DO LIST:
//-sprzężyć z res_loaderem [DONE]
//-oznakować obrazki
//-dodać zapis do pliku
//-i odczyt
//-bajery z ekranem (przewijanie, wyświetlanie, podgląd na żywo)


#include "lib.h"
///POTRZEBNE PLIKI
#include "res_loader/res_loader.h"



///STRUKTURA KAFELKA
struct tile
{
    std::string type;        //id kafelka
    ALLEGRO_BITMAP *image;         //bitmapa kafelka
    //POZYCJA NIE POTRZEBNA BO I TAK TO W MACIERZY JEST
    int rotation;       //orientacja kafelka
    int effect;     //efekt kafelka (wtf?) - CHODZI O WPLYW KAFELKA NA JEDNOSTKI NA NIM
};



///KLASA EDYTORA
class editor
{
    public:
        editor(resInstance* gameLIBSource,int ScreenHeight,int ScreenWidth) { gameLIB=gameLIBSource; createDisplay(ScreenHeight,ScreenWidth); }
        //Uruchamianie poprzez podanie liba i wys i szer ekranu
        //Tworzenie ekranu gry o podanej rozdzielczosci
        void releaseMemory(); //Zwalnianie pamieci zajetej przez Allegro, np. timer czy keystate

        //ŁADOWANIE ZASOBÓW
        resInstance* gameLIB;
        ALLEGRO_DISPLAY *display;
    private:
        bool createDisplay(int ScreenHeight,int ScreenWidth); //URUCHAMIANE przez konstruktor - raz!
};


///KLASA MAPY
class map
{
    public:
        std::string name;        //nazwa mapy
        int Xsize;      //szerokość mapy
        int Ysize;      //wysokość mapy

        tile** mapa;        //macierz

        map(int X, int Y, std::string n)          //konstruktor
        {
            tile** mapa=new tile*[Y];
            name=n;
            Xsize=X;
            Ysize=Y;

            for(int i=0;i<Y;i++)        //generowanie tablicy 2d
            {
                mapa[i]=new tile[X];
            }

        }

        void createMap();        //tworzy pustą mapę
        void fillWater(std::string name);        //wypełnia wodą
        void addTile(std::string type,int rotation, int Xpos, int Ypos);       //tworzy kafelek danego typu w danym miejscu
        void releaseMemory();       //zwalnia pamięć po macierzy
};



#endif
