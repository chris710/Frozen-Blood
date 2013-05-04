//////////////////////////////////////////////
///         MAIN.CPP
///     Główny plik edytora poziomów
//////////////////////////////////////////////



///POTRZEBNE PLIKI
#include "editor.h"


int main()
{

    ///Zeby skorzystac z res_loadera musisz przekazac do klasy edytora odniesienie do gameLIB
    resInstance* gameLIB = new resInstance;
    if(!gameLIB->ResourceLoader())
    {
            gameLIB->ResourceUnloader();
            //error
            return -1;
    }
    editor* gameEditor = new editor(gameLIB,800,600);        //tworzy instancję klasy edytora

    for(int i=0;i<gameEditor->gameLIB->objLib.size();i++)         //wypisuje wszystkie obrazki
    {
        cout<<i+1<<" - "<<gameEditor->gameLIB->objLib[i]->name<<endl;
    }


    //Po takim zabiegu w gameEditor->gameLib->objLib[iterator] masz po kolei kafelki z objs.cfg
    //w gameEditor->gameLib->soundLib[iterator] dzwieki
    //w gameEditor->gameLib->unitLib[iterator] template jednostek
    //dodatkowo masz dostep do kursorow i elementow UI
    ///problemem bedzie to, ze exek edytora jest w osobnym folderze, zeby to naprawic przekopiuj plik level_editor,exe do folderu [test] i tam odpalaj
    //STUB
    gameLIB->ResourceUnloader();
    delete gameLIB;
    return 0;
}
