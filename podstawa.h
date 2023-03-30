#ifndef PODSTAWA_H
#define PODSTAWA_H

#include <iostream>
#include <cstdlib>      //generowanie liczb pseudolosowych
#include <time.h>       //funkcja time();

/**
* \file podstawa.h
* \brief Plik nagłówkowy modułu Podstawa
*/

/**
 * @brief struktura do przechowywania wartości poszczególnych pól mapy w tablicy dynamicznej
*/

struct komorka
{
    ///Wartość obecna danej komórki
    int wartoscObecna;
    ///Wartość przyszła danej komórki
    int wartoscPrzyszla;
};

//struktura używana podczas generowania mapy
/**
 * @brief struktura używana podczas generowania mapy do przechowywania listy komórek
 */
struct lista
{
    ///Numer wiersza komórki
    int w;
    ///Numer kolumny komórki
    int k;
    ///Wskaźnik do następnego elementu listy
    lista *nast;
};



#endif // PODSTAWA_H
