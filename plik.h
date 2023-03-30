#ifndef PLIK_H
#define PLIK_H
#include "mainwindow.h"
#include <fstream>

/**
* \file plik.h
* \brief Plik nagłówkowy modułu Plik
*/

// Struktury do utworzenia jednokierunkowej listy list jednokierunkowych potrzebnej do
// odczytu mapy o dowolnej wielkości
/**
 * @brief Struktura do przechowywania kolejne wartośći w wierszach, nowo wczytywanej mapy
 */
struct wiersze
{
    ///Wartość w określonej komórce listy
    int x;
    ///Wskaźnik do następnego elementu listy
    wiersze *nast;
};
/**
 * @brief Struktura przechowująca kolejne wiersze nowo wczytywanej mapy
 */
struct dane
{
    ///Wskaźnik do listy przechowującej kolejne elementy w wierszu
    wiersze *w;
    ///Wskaźnik do następnego elementu listy
    dane *nast;
};

bool Wczytaj(QWidget *okno, komorka **&m,int &W, int &K, bool czyMamMape);
void zapiszDoPlikuTxt(int, int, QWidget*, komorka**);
void zapiszObraz(QWidget*, QImage*);

using namespace std;
#endif // PLIK_H
