//////////////////////////////////////////////////
///                   MAIN                     ///
///                 main.cpp                   ///
//////////////////////////////////////////////////

#include "editor/editor.h"


int main()
{
    editorInstance* editor = new editorInstance;
    if(!editor->Init()) return -1;
    resInstance* resLib = new resInstance;
    if(!resLib->ResourceLoader()) { resLib->ResourceUnloader(); return -2; }
    editor->CreateDisplay(480,576);

    ////////////////////////////////////
    //      INICJALIZACJA ALLEGRO
    ////////////////////////////////////
    editor->eventQueueAL = al_create_event_queue(); //Tworzymy nowa kolejke zdarzen
    al_register_event_source(editor->eventQueueAL,al_get_keyboard_event_source()); // i ja rejestrujemy
    al_register_event_source(editor->eventQueueAL,al_get_mouse_event_source()); // i rejestrujemy zdarzenia klawiatury i myszy
    editor->editorTimerAL = al_create_timer(1.0/editor->fps); //tworzymy nowy timer
    al_register_event_source(editor->eventQueueAL,al_get_timer_event_source(editor->editorTimerAL)); //i go rejestrujemy jako zrodlo zdarzen
    //Rejestracja okna jako zrodlo zdarzen
    al_register_event_source(editor->eventQueueAL,al_get_display_event_source(editor->displayAL));
    al_start_timer(editor->editorTimerAL); //Uruchamiamy nasz timer


    /////////////////////////////////
    //
    //      PĘTLA EDYTORA
    //
    ////////////////////////////////
    while(!editor->exitEditor)
    {
        al_wait_for_event(editor->eventQueueAL,&editor->editorEventsAL); //Czekamy na zdarzenie

        switch(editor->editorEventsAL.type) //Switch obslugi zdarzen
        {
            case ALLEGRO_EVENT_DISPLAY_CLOSE: //Jezeli wcisnieto przycisk "X"
                std::cout << "[DISPLAY] ENDING" << std::endl; //Zamykamy program
                editor->exitEditor = true;
                break;

            /////////////////////////
            //      STEROWANIE
            /////////////////////////
            case ALLEGRO_EVENT_KEY_DOWN: //Jezeli wcisnieto przycisk na klawiaturze
            {

                switch(editor->editorEventsAL.keyboard.keycode) //to sprawdzamy co to za przycisk
                {
                    case ALLEGRO_KEY_ESCAPE: //w przypadku esc zamykamy program
                    {
                        editor->exitEditor = true;
                        break;
                    }
                    case ALLEGRO_KEY_L:     //ładuje mapę z pliku
                    {
                        editor->UnloadMap();
                        std::cout << "Podaj nazwe mapy: ";
                        std::string name;
                        std::cin >> name;
                        if(name!="") editor->LoadMap(name.c_str(),resLib);
                        editor->updateDisplay=true;
                        break;
                    }
                    case ALLEGRO_KEY_N:     //tworzy nową mapę
                    {
                        editor->CreateMap(resLib);
                        editor->updateDisplay=true;
                        break;
                    }
                    case ALLEGRO_KEY_S:     //zapisuje mapę do pliku
                    {
                        std::cout<<"Podaj nazwe mapy: ";
                        std::cin>>editor->mapName;

                        std::string file = "res/maps/"+editor->mapName+".cfg";
                        std::ifstream mapatmp;
                        mapatmp.open(file.c_str());
                        if( mapatmp.good() )  //nadpisanie mapy
                        {
                            std::cout<<"Czy chcesz nadpisac mape? (Y/N)"<<std::endl;

                            char over=getch();      //zmienna do nadpisania
                            switch (over)                                       ///nadpisanie
                            {
                                case 'y': //nadpisz
                                {
                                    editor->exitEditor = true;
                                    editor->SaveMap(editor->mapName);
                                    break;
                                }
                                case 'n':     break;  //nie nadpisuj
                            }
                        }
                        else     editor->SaveMap(editor->mapName);
                        break;
                    }
                }
                break;
            }
        }

        if(editor->updateDisplay)       //render mapy
        {
            al_clear_to_color(al_map_rgb(157,67,67)); //czyscimi
            editor->RenderMap(); //renderujemy mape
            al_flip_display(); //wyswietlamy
            editor->updateDisplay = false;
        }
    }

    resLib->ResourceUnloader();
    editor->ReleaseMemory();
    delete resLib;
    delete editor;
    return 0;
}
