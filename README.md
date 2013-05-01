Temporary_project_name
======================

Gra (?) - ponoć strategia turowa


//////////////TUTAJ UMIEŚCIĆ SZCZEGÓŁY PROJEKTU (TZW. KOMPLETNY PROJEKT)

...WIP...
1) Ogólny opis gry (okreść kategorię gry, krótko ją streścić/ opisać; coś jak news w czasopiśmie komputerowym)
2) Cele gry (krótko o rzeczach do których się w grze dąży)
3) Fabuła, historie, świat, postacie inne pierdoły
4) Zasady i tryby gry (czyli czym to się je)
5) Interakcja między graczem a grą 
6) Opis interfejsu (grafiki, muzyki, poziomów)
7) Przebieg (trudne) opisać co będzie się działo w grze od momentu, kiedy użytkownik rozpoczyna grę, poprzez główne zdarzenia w grze, aż do momentu jej zakończenia, wygląda to tak jakbyś opisywał grę w którą sam grałeś
8) Schematy, mechanizmy rozwiązania, algorytmy
9) Podsumowanie (czyli tłumacz się dlaczego wybrałeś tak jak wybrałeś i ma być tak jak jest)

KOD GRY
- main.cpp
- main.h
- game/game.cpp
- game/game.h
- game/menu.cpp
- game/menu.h
- editor/level_editor.cpp
- editor/level_editor.h
- units/[RASA]/units.cpp
- units/[RASA]/units.h
- units/[RASA]/ai.cpp
- units/[RASA]/ai.h

ZASOBY GRY
- data/units/
- data/sounds/
- data/UI/
- data/UI/splash.png


//
//  UWAGI OGÓLNE DOTYCZĄCE PROJEKTU
//


//PROJEKT ROZCZŁONKOWAĆ JAK TYLKO SIĘ DA, W KAŻDYM PLIKU OSOBNY WPIS NA GÓRZE, TZW TO-DO-LIST; KAŻDA FUNKCJA Z PEŁNĄ DOKUMENTACJĄ (CO ONA ROBI, JAKIE ARGUMENTY PRZYJMUJE, CO ZWRACA, DODATKOWE UWAGI, ITP.)

//SCHEMAT TWORZENIA COMMITÓW:
//-TYTUŁ KAPITALIKAMI
//-(W NAWIASACH) W TYTULE PRZED NAZWĄ ZMIANY, POSTĘP ZMIANY (INPROGRESS,ALFA,BETA,FINAL)
//-TYTUŁ ZAWIERA PLIK/KLASĘ, W KTÓREJ ZACHODZĄ ZMIANY I OGÓLNĄ NAZWĘ ZMIANY/POPRAWKI
//-W TREŚCI ZAPISAĆ SZCZEGÓŁY DOKONANEJ PRACY I UWAGI ODNOŚNIE JEJ I JEJ EWENTUALNEGO WPŁYWU
NA RESZTĘ PROJEKTU

//KOD UDZIWNIONY ALE DZIAŁAJĄCY UNIEMOŻLIWIA DALSZĄ PRACĘ (CZYT. BEZ KODU SPAGHETTI, WSZYSTKO MA BYĆ ZMYŚLNE, PROSTE I CO NAJWAŻNIEJSZE W PEŁNI PRZEWIDYWALNE I OPANOWANE)

//PAMIĘTAJ ABY KOMENTOWAĆ KAŻDĄ LINIJKĘ!!! WAŻNE JEST ABY KOD BYŁ ZROZUMIAŁY NAWET DLA OSOBY POSTRONNEJ
//UŻYWAJ RÓŻNYCH METOD KOMENTOWANIA,NP.

//////////////////////////////////////////////////////////////////////////
//
//		TAK OPISUJEMY DUŻE I WAŻNE FRAGMENTY KODU
//
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////
//	A TUTAJ MNIEJSZE ALE NADAL WAŻNE
//////////////////////////////////////////////
void main (int bla)	//to jest bliski komentarz (po jednym tabie)	
		   				                                //a to daleki (jest wyrównany do prawej)
