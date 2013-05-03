//////////////////////////////////////////////////
///             RESOURCE LOADER                ///
///              res_loader.cpp                ///
//////////////////////////////////////////////////

///POTRZEBNE PLIKI
#include "game.h"

bool gameInstance::ResourceLoader()
{
    std::ifstream resources[3]; //Otwieramy wszystkie pliki cfg zawierajace dane o obiektach gry
    resources[0].open("game/units.cfg");
    resources[1].open("game/sounds.cfg");
    resources[2].open("game/objs.cfg");

    if(!resources[0].good()) { DisplayMessage("Blad!","Nie mozna otworzyc pliku units.cfg!"); return false; } //Sprawdzamy czy
    if(!resources[1].good()) { DisplayMessage("Blad!","Nie mozna otworzyc pliku sounds.cfg!"); return false; } //listy sa dostepne
    if(!resources[2].good()) { DisplayMessage("Blad!","Nie mozna otworzyc pliku objs.cfg!"); return false; } // do wczytania

    std::string line;

    for(int i=0;i<3;i++)
    {
        while(!resources[i].eof()) //Wczytujemy po kolei ka�dy z plik�w do odpowiedniej listy
        {
            getline(resources[i],line);
            if(line=="[UNIT]")
            {
                std::string name,file,sound_movement,sound_attack,sound_death;
                int HP,attack,defence;
                getline(resources[i],line); //Sprawdzamy czy dany wpis w pliku cfg istnieje i czy jest na odpowiedniej pozycji
                if(line=="[NAME]") getline(resources[i],name); else continue; //wczytujemy dane, albo przerywamy je�eli s� niepoprawne
                getline(resources[i],line);
                if(line=="[BITMAP]") getline(resources[i],file); else continue;
                getline(resources[i],line);
                if(line=="[HP]") resources[i]>>HP; else continue;
                getline(resources[i],line);
                if(line=="[ATTACK]") resources[i]>>attack; else continue;
                getline(resources[i],line);
                if(line=="[DEFENCE]") resources[i]>>defence; else continue;
                getline(resources[i],line);
                if(line=="[SOUND_MOVEMENT]") getline(resources[i],sound_movement); else continue;
                getline(resources[i],line);
                if(line=="[SOUND_ATTACK]") getline(resources[i],sound_attack); else continue;
                getline(resources[i],line);
                if(line=="[SOUND_DEATH]") getline(resources[i],sound_death); else continue;
                std::cout << "[unitLIB] \"" << name << " " << file << "\" LOADING" <<std::endl;
                PushUnitCFG(name,file,HP,attack,defence,sound_movement,sound_attack,sound_death); //Dodajemy poprawne dane do listy
            }
            if(line=="[SOUND]")
            {
                std::string name,file;
                getline(resources[i],line);
                if(line=="[NAME]") getline(resources[i],name); else continue;
                getline(resources[i],line);
                if(line=="[FILE]") getline(resources[i],file); else continue;
                std::cout << "[soundLIB] \"" << name  << " " << file << "\" LOADING" <<std::endl;
                PushSoundCFG(name,file);
            }
            if(line=="[OBJ]")
            {
                std::string name,file;
                getline(resources[i],line);
                if(line=="[NAME]") getline(resources[i],name); else continue;
                getline(resources[i],line);
                if(line=="[FILE]") getline(resources[i],file); else continue;
                std::cout << "[objLIB] \"" << name  << " " << file << "\" LOADING" <<std::endl;
                PushObjCFG(name,file);
            }
            if(line=="[FIELDBOX]")
            {
                if(fieldBox!=NULL) continue;
                std::string file;
                getline(resources[i],file);
                fieldBox = al_load_bitmap(file.c_str());
                if(!fieldBox) std::cout << "[objLib] ERROR \"" << file << "\" - FILE NOT FOUND" << std::endl;
                else std::cout << "[objLib] FIELDBOX LOADED" << std::endl;
            }
            if(line=="[CURSOR]")
            {
                if(cursor!=NULL) continue;
                std::string file;
                getline(resources[i],file);
                cursor = al_load_bitmap(file.c_str());
                if(!cursor) std::cout << "[objLib] ERROR \"" << file << "\" - FILE NOT FOUND" << std::endl;
                else std::cout << "[objLib] CURSOR LOADED" << std::endl;
            }
            if(line=="[CURSORPRESSED]")
            {
                if(cursorPressed!=NULL) continue;
                std::string file;
                getline(resources[i],file);
                cursorPressed = al_load_bitmap(file.c_str());
                if(!cursorPressed) std::cout << "[objLib] ERROR \"" << file << "\" - FILE NOT FOUND" << std::endl;
                else std::cout << "[objLib] CURSORPRESSED LOADED" << std::endl;
            }
        }
        resources[i].close(); //Zamykamy pliki cfg
    }
    if(!fieldBox) std::cout << "[DISPLAY] FIELDBOX MISSING" << std::endl;
    if(!cursor) std::cout << "[DISPLAY] CURSOR MISSING" << std::endl;
    else    { mouseCursor = al_create_mouse_cursor(cursor,12,12); al_set_mouse_cursor(displayAL,mouseCursor); }
    if(!cursorPressed) std::cout << "[DISPLAY] CURSORPRESSED MISSING" << std::endl;
    else    mouseCursorPressed = al_create_mouse_cursor(cursorPressed,12,12);

    return true;
}

void gameInstance::ResourceUnloader()
{
    for(int i=0;i<unitLib.size();i++) //Usuwamy wszystkie obiekty z list
    {
        std::cout << "[unitLIB] \"" << unitLib[i]->name << "\" UNLOADED" <<std::endl;
        al_destroy_bitmap(unitLib[i]->bitmap); //Czyscimy bitmapy jednostek
        delete unitLib[i];
        unitLib[i]=NULL;
    }
    for(int i=0;i<soundLib.size();i++)
    {
        std::cout << "[soundLIB] \"" << soundLib[i]->name << "\" UNLOADED" <<std::endl;
        al_destroy_sample(soundLib[i]->file); //dzwieki
        delete soundLib[i];
        soundLib[i]=NULL;
    }
    for(int i=0;i<objLib.size();i++)
    {
        std::cout << "[objLIB] \"" << objLib[i]->name << "\" UNLOADED" <<std::endl;
        al_destroy_bitmap(objLib[i]->bitmap); // oraz bitmapy obiektow i tla
        delete objLib[i];
        objLib[i]=NULL;
    }
    if(cursor) { al_destroy_bitmap(cursor); std::cout << "[objLIB] CURSOR UNLOADED" <<std::endl; }
    if(cursorPressed) { al_destroy_bitmap(cursorPressed); std::cout << "[objLIB] CURSORPRESSED UNLOADED" <<std::endl; }
    if(fieldBox) { al_destroy_bitmap(fieldBox); std::cout << "[objLIB] FIELDBOX UNLOADED" <<std::endl; }
    unitLib.clear();
    soundLib.clear();
    objLib.clear();
}

bool gameInstance::PushUnitCFG(std::string name,std::string file,int HP,int attack,int defence,std::string sound_movement,
                               std::string sound_attack,std::string sound_death)
{
    unitStruct* unit = new unitStruct; //Dodajemy do listy nowy wpis o podanych parametrach
    unit->name=name;
    unit->bitmap=NULL;
    unit->bitmap = al_load_bitmap(file.c_str()); //Ladujemy bitmape z pliku, tylko RAZ w calym programie!
    if(!unit->bitmap) { delete &unit;  std::cout << "[unitLIB] ERROR \"" << file << "\" - FILE NOT FOUND | SKIPPING" << std::endl; return false;} //Jezeli sie nie uda, to przerywamy, bo i tak nic nie bedzie widac
    unit->HP=HP;
    unit->attack=attack;
    unit->defence=defence;
    unit->sound_movement=sound_movement; //Tylko nazwy dzwiekow, przy tworzeniu instancji jednostki ustawiane sa odpowiednie pointery
    unit->sound_attack=sound_attack;
    unit->sound_death=sound_death;
    unitLib.push_back(unit); //Dodajemy do biblioteki
    std::cout << "[unitLIB] \"" << unit->name << "\" LOADED" <<std::endl;
    return true;
}
bool gameInstance::PushSoundCFG(std::string name,std::string file)
{
    soundStruct* sound = new soundStruct;
    sound->name=name;
    sound->file=NULL;
    sound->file = al_load_sample(file.c_str());
    if(!sound->file) { delete sound;  std::cout << "[soundLIB] ERROR \"" << file << "\" - FILE NOT FOUND | SKIPPING" << std::endl; return false; }
    soundLib.push_back(sound);
    std::cout << "[soundLIB] \"" << sound->name << "\" LOADED" <<std::endl;
    return true;
}
bool gameInstance::PushObjCFG(std::string name,std::string file) //Lista elementow mapy
{
    objStruct* obj = new objStruct;
    obj->name=name;
    obj->bitmap=NULL;
    obj->bitmap = al_load_bitmap(file.c_str());
    if(!obj->bitmap) { delete obj;  std::cout << "[objLIB] ERROR \"" << file << "\" - FILE NOT FOUND | SKIPPING" << std::endl; return false; }
    objLib.push_back(obj);
    std::cout << "[objLIB] \"" << obj->name << "\" LOADED" <<std::endl;
    return true;
}
