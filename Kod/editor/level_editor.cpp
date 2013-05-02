///////////////////////////////////////
///                                 ///
///                                 ///
///         EDYTOR POZIOMÓW         ///
///                                 ///
///                                 ///
///////////////////////////////////////




//      TO-DO LIST:
//  1)Tworzenie mapy jako macierzy 2wymiarowej
//  2)Stworzenie róznych rodzajów terenów (teren otwarty, woda, most, las, góry, osada, twierdza, droga) lub...
//  3)Pobranie zasobów (głównie obrazków i właściwości terenu) ze źródeł zewnętrznych
//  4)Stworzenie narzędzia do "ręcznego" zapełniania mapy (GUI?)
//  5)Użycie presetów terenu do wygenerowania mapy
//  6)Generator plików
//

///POTRZEBNE BIBLIOTEKI
#include <fstream>


///POTRZEBNE PLIKI
#include "../game/game.h"

///////////////////////////////////
//
//      WCZYTYWANIE MAPY Z PLIKU
//
///////////////////////////////////
bool MapLoader (std::string file,gameInstance* game)    //jako argument podajemy nazwę pliku z mapą,
// gameInstance potrzebna do bibliotek jednostek, dzwiekow, itd.
{
    std::ifstream map;                       //zmienna map określa plik z mapą do otwarcia
    std::string mapa="res/maps/"+file;      //string mapa to połączenie ścieżki pliku z mapą oraz argumentu z nazwą pliku
    map.open(mapa.c_str());                 //otwieramy plik

    std::string message="Nie mozna otworzyc pliku z mapa "+file+"!";
    if(!map.good()) { game->DisplayMessage("Blad!",message); return false; }      //sprawdzamy czy można otworzyć plik z mapą
}




