#ifndef GENERATOR_H
#define GENERATOR_H

#include "podstawa.h"

/**
* \file generator.h
* \brief Plik nagłówkowy modułu Generator
*/

void generujMape(int, int, komorka **, int, int);

//--------------------------OBSŁUGA-TABLICY-ZAWIERAJĄCEJ-MAPĘ--------------------------
komorka **PrzygotujTablice(int, int);
void UsunTablice(int, komorka**);


//---------------------------------GENEROWANIE-LĄDU-------------------------------------
int rozrost(int , int, int, int, lista *&, lista *&, komorka **,  int);
void losujNastepnaKomorke(int, int, lista *&, lista *&, komorka**, int&, int&, int);
void nowaKomorka(int, int,int,int, lista *&, lista *&, komorka**, int, int &, int &, int);
void Dodaj(int, int, int, int, lista *&, lista *&, komorka**,  int&, int&, int);


//-------------------------------GENEROWANIE-TERENU-------------------------------------
void nadajTerenWyspie(int, int, lista*&, int, komorka**, int, int, int);
void terenuj(int,int, int&, int, int, int, int, lista*&, komorka**);
void etap(int, int, int &, int, int, lista *&,komorka **);
int prawdopodobienstwo(int, int, int, int, komorka **, int);


//----------------------------------OBSŁUGA-LIST----------------------------------------
void usun(lista*&);
void dodajDoListy(int, int, lista*&);
void usunZListy(lista*&, int);


#endif // GENERATOR_H
