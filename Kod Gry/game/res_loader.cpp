//////////////////////////////////////////////////
///             RESOURCE LOADER                ///
///              res_loader.cpp                ///
//////////////////////////////////////////////////

///POTRZEBNE PLIKI
#include "game.h"

bool gameInstance::ResourceLoader()
{
    std::ifstream resources[3]; //Otwieramy wszystkie pliki cfg zawierajace dane o obiektach gry
    resources[0].open("game/sounds.cfg");
    resources[1].open("game/units.cfg");
    resources[2].open("game/objs.cfg");

    if(!resources[0].good()) { DisplayMessage("Blad!","Nie mozna otworzyc pliku sounds.cfg!"); return false; } //Sprawdzamy czy
    if(!resources[1].good()) { DisplayMessage("Blad!","Nie mozna otworzyc pliku units.cfg!"); return false; } //listy sa dostepne
    if(!resources[2].good()) { DisplayMessage("Blad!","Nie mozna otworzyc pliku objs.cfg!"); return false; } // do wczytania

    std::string line;

    for(int i=0;i<3;i++)
    {
        while(!resources[i].eof()) //Wczytujemy po kolei ka¿dy z plików do odpowiedniej listy
        {
            getline(resources[i],line);
            if(line=="[UNIT]")
            {
                std::string name,file,sound_movement,sound_attack,sound_death;
                int HP,attack,defence;
                resources[i]>>line; //Sprawdzamy czy dany wpis w pliku cfg istnieje i czy jest na odpowiedniej pozycji
                if(line=="[NAME]") resources[i] >> name; else  continue;  //wczytujemy dane, albo przerywamy je¿eli s¹ niepoprawne
                resources[i] >> line;
                if(line=="[BITMAP]") resources[i] >> file; else continue;
                resources[i] >> line;
                if(line=="[HP]") resources[i] >> HP;  else continue;
                resources[i] >> line;
                if(line=="[ATTACK]") resources[i] >> attack; else continue;
                resources[i] >> line;
                if(line=="[DEFENCE]") resources[i]>>defence; else continue;
                resources[i] >> line;
                if(line=="[SOUND_MOVEMENT]") resources[i] >> sound_movement; else continue;
                resources[i] >> line;
                if(line=="[SOUND_ATTACK]") resources[i] >> sound_attack; else continue;
                resources[i] >> line;
                if(line=="[SOUND_DEATH]") resources[i] >> sound_death; else continue;
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
        }
        resources[i].close(); //Zamykamy pliki cfg
    }
    std::cout << "[UI] FIELDBOX \"res/drawable/UI/fieldbox.png\" LOADING" <<std::endl;
    fieldBox = al_load_bitmap("res/drawable/UI/fieldbox.png");
    if(!fieldBox)
    {
        std::cout << "[UI] ERROR \"res/drawable/UI/fieldbox.png\" - FILE NOT FOUND" << std::endl;
        DisplayMessage("Blad!","Nie mozna odnalezc pliku \"fieldbox.png\"");
        return false;
    }
    else  std::cout << "[UI] FIELDBOX LOADED" <<std::endl;
    std::cout << "[UI] CURSOR(1) \"res/drawable/UI/cursor1.png\" LOADING" <<std::endl;
    cursor[0] = al_load_bitmap("res/drawable/UI/cursor1.png");
    if(!cursor[0])
    {
        std::cout << "[UI] ERROR \"res/drawable/UI/cursor1.png\" - FILE NOT FOUND" << std::endl;
        DisplayMessage("Blad!","Nie mozna odnalezc pliku \"cursor1.png\"");
        return false;
    }
    else
    {
        mouseCursor[0] = al_create_mouse_cursor(cursor[0],12,12);
        std::cout << "[UI] CURSOR(1) LOADED" <<std::endl;
        al_set_mouse_cursor(displayAL,mouseCursor[0]);
    }
    std::cout << "[UI] CURSOR(2) \"res/drawable/UI/cursor2.png\" LOADING" <<std::endl;
    cursor[1] = al_load_bitmap("res/drawable/UI/cursor2.png");
    if(!cursor[1])
    {
        std::cout << "[UI] ERROR \"res/drawable/UI/cursor2.png\" - FILE NOT FOUND" << std::endl;
        DisplayMessage("Blad!","Nie mozna odnalezc pliku \"cursor2.png\"");
        return false;
    }
    else
    {
        mouseCursor[1] = al_create_mouse_cursor(cursor[1],12,12);
        std::cout << "[UI] CURSOR(2) LOADED" <<std::endl;
    }
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
    if(cursor[0]) { al_destroy_bitmap(cursor[0]); std::cout << "[UI] CURSOR(1) UNLOADED" <<std::endl; }
    if(cursor[1]) { al_destroy_bitmap(cursor[1]); std::cout << "[UI] CURSOR(2) UNLOADED" <<std::endl; }
    if(fieldBox) { al_destroy_bitmap(fieldBox); std::cout << "[UI] FIELDBOX UNLOADED" <<std::endl; }
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
    if(!unit->bitmap) { delete unit;   std::cout << "[unitLIB] ERROR \"" << file << "\" - FILE NOT FOUND | SKIPPING" << std::endl; return false;} //Jezeli sie nie uda, to przerywamy, bo i tak nic nie bedzie widac
    unit->HP=HP;
    unit->attack=attack;
    unit->defence=defence;
    //unit->sound_movement=sound_movement; //Tylko nazwy dzwiekow, przy tworzeniu instancji jednostki ustawiane sa odpowiednie pointery
    //unit->sound_attack=sound_attack;
    //unit->sound_death=sound_death;
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
