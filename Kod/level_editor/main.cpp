//////////////////////////////////////////////
///         MAIN.CPP
///     Główny plik edytora poziomów
//////////////////////////////////////////////



///POTRZEBNE PLIKI
#include <conio.h>
#include "editor.h"


///DEFINICJE
#define FPS 20

int main()
{

    bool done=false;        //zmienna do pętli edytora, kiedy przyjmuje true program kończy się
    struct tile* Tmp=(struct tile *)malloc(sizeof(struct tile));        //struktura tymczasowa wyboru kafelka

    ///Zeby skorzystac z res_loadera musisz przekazac do klasy edytora odniesienie do gameLIB
    resInstance* gameLIB = new resInstance;

    editor* gameEditor = new editor(gameLIB,800,600);       //tworzymy ekran
    if(!gameLIB->ResourceLoader())          //ładujemy grafiki
    {
            gameLIB->ResourceUnloader();
            //error
            return -1;
    }
      //tworzy instancję klasy edytora

    for(int i=0;i<gameEditor->gameLIB->objLib.size();i++)         //wypisuje wszystkie obrazki
    {
        std::cout<<i+1<<" - "<<gameEditor->gameLIB->objLib[i]->name<<std::endl;
    }
    //Po takim zabiegu w gameEditor->gameLib->objLib[iterator] masz po kolei kafelki z objs.cfg
    //w gameEditor->gameLib->soundLib[iterator] dzwieki
    //w gameEditor->gameLib->unitLib[iterator] template jednostek
    //dodatkowo masz dostep do kursorow i elementow UI
    ///problemem bedzie to, ze exek edytora jest w osobnym folderze, zeby to naprawic przekopiuj plik level_editor,exe do folderu [test] i tam odpalaj

    //////////////////////////////////////////////
    //
    //      INICJALIZACJA ALLEGRO
    //
    /////////////////////////////////////////////
    ALLEGRO_KEYBOARD_STATE keyState;                                                    //rejestrowanie modułów
	ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	//al_register_event_source(event_queue, al_get_display_event_source(display));

	al_start_timer(timer);




    /////////////////////////////////////
    //
    //      PĘTLA EDYTORA
    //
    ////////////////////////////////////
    while(!done)
    {
        ALLEGRO_EVENT events;

		al_wait_for_event(event_queue, &events);        //listener kolejki na eventy
		al_get_keyboard_state(&keyState);           //stan klawiszy


        ///////////////////////////////
        //      WYBIERANIE KAFELKA
        //////////////////////////////
		if(events.type == ALLEGRO_EVENT_KEY_UP)
		{
                switch(events.keyboard.keycode)
                {
                    case ALLEGRO_KEY_ESCAPE:        //WYŁĄCZANIE ESC
                    {
                        done = true;
                        break;
                    }
                    case ALLEGRO_KEY_N:         //TWORZENIE NOWEJ MAPY
                    {
                        map* nowa=new map(16,16,"nowa");        //tworzymy nową mapę, chwilowo ma rozmiar 16x16
                        nowa->createMap();      //tworzymy pustą mapę       ///nie działa
                        break;
                    }
                    case ALLEGRO_KEY_1:         //bridge
                    {
                        Tmp->type="bridge";
                        Tmp->image=gameEditor->gameLIB->objLib[0]->bitmap;
                        Tmp->rotation=0;    //0 czyli nie obrócony
                        Tmp->effect=5;      //most daje 5 defence'a
                        break;
                    }
                    case ALLEGRO_KEY_2:         //forest1
                    {
                        Tmp->type="forest1";
                        Tmp->image=gameEditor->gameLIB->objLib[1]->bitmap;
                        Tmp->rotation=0;    //0 czyli nie obrócony
                        Tmp->effect=10;      //las daje 10 defence'a
                        break;
                    }
                    case ALLEGRO_KEY_3:         //forest2
                    {
                        Tmp->type="forest2";
                        Tmp->image=gameEditor->gameLIB->objLib[2]->bitmap;
                        Tmp->rotation=0;    //0 czyli nie obrócony
                        Tmp->effect=10;      //forest daje 10 defence'a
                        break;
                    }
                    case ALLEGRO_KEY_4:         //mountains1
                    {
                        Tmp->type="mountains1";
                        Tmp->image=gameEditor->gameLIB->objLib[3]->bitmap;
                        Tmp->rotation=0;    //0 czyli nie obrócony
                        Tmp->effect=15;      //góry dają 15 defence'a
                        break;
                    }
                    case ALLEGRO_KEY_5:         //mountains2
                    {
                        Tmp->type="mountains2";
                        Tmp->image=gameEditor->gameLIB->objLib[4]->bitmap;
                        Tmp->rotation=0;    //0 czyli nie obrócony
                        Tmp->effect=15;      //góry dają 15 defence'a
                        break;
                    }
                    case ALLEGRO_KEY_6:         //skrzyżowanie 3 dróg
                    {
                        Tmp->type="road_crossing3";
                        Tmp->image=gameEditor->gameLIB->objLib[5]->bitmap;
                        Tmp->rotation=0;    //0 czyli nie obrócony
                        Tmp->effect=0;      //droga nie daje obrony
                        break;
                    }
                    case ALLEGRO_KEY_7:         //skrzyżowanie 3 dróg
                    {
                        Tmp->type="road_crossing3";
                        Tmp->image=gameEditor->gameLIB->objLib[5]->bitmap;
                        Tmp->rotation=0;    //0 czyli nie obrócony
                        Tmp->effect=0;      //droga nie daje obrony
                        break;
                    }
                }
        }
    }









    gameLIB->ResourceUnloader();
    delete gameLIB;
    gameEditor->releaseMemory();
    return 0;
}
