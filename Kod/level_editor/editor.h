/////////////////////////
///
///     EDITOR.H
///
/////////////////////////
#ifndef EDITOR_H
#define EDITOR_H




//      TO-DO LIST:
//-sprzężyć z res_loaderem
//-dodać zapis do pliku
//-i odczyt
//-bajery z ekranem (przewijanie, wyświetlanie, podgląd na żywo)






///BIBLIOTEKI
#include<iostream>
#include<vector>
#include<fstream>
#include<conio.h>
#include<allegro5/allegro.h>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_image.h>

///POTRZEBNE PLIKI
#include"../game/game.h"

using namespace std;


///STRUKTURA KAFELKA
struct tile
{
    string type;        //id kafelka
    ALLEGRO_BITMAP *image;         //bitmapa kafelka
    int Xpos;       //pozycja pozioma
    int Ypos;       //pozycja pionowa
    int rotation;       //orientacja kafelka
    int effect;     //efekt kafelka (wtf?)
};



///KLASA EDYTORA
class editor
{
    public:
        bool createDisplay(int ScreenHeight,int ScreenWidth);   //Tworzenie ekranu gry o podanej rozdzielczosci
        void releaseMemory(); //Zwalnianie pamieci zajetej przez Allegro, np. timer czy keystate

        //ŁADOWANIE ZASOBÓW
        vector<tile*> lista;
        bool push(string name, string file);
};


///KLASA MAPY
class map
{
    public:
        string name;        //nazwa mapy
        int Xsize;      //szerokość mapy
        int Ysize;      //wysokość mapy

        tile** mapa;        //macierz

        map(int X, int Y, string n)          //konstruktor
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
        void fillWater(string name);        //wypełnia wodą
        void addTile(string type,int rotation, int Xpos, int Ypos);       //tworzy kafelek danego typu w danym miejscu
        void releaseMemory();       //zwalnia pamięć po macierzy
};



#endif
