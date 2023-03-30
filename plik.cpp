#include "mainwindow.h"
#include <string>
#include <QFileDialog>
#include "plik.h"

/**
* \file plik.cpp
* \brief Plik źródłowy modułu Plik
*/

//---------------------------------ZAPIS-DO-PLIKU---------------------------------
/**
 * @brief Funkcja zapisująca obraz mapy do pliku graficznego
 * @param okno Wskaźnik do okna głównego programu
 * @param image Obraz który chcemy zpisać
 */
void zapiszObraz(QWidget* okno, QImage* image)
{
    // Otwarcie okna zapisu i pobranie nazwy pliku do objektu klasy QString
    // (dwa rodzaje rozszerzeń pliku do wyboru: .jpeg i .png)
    QString nazwa = QFileDialog::getSaveFileName(okno, "Zapisz obraz", QDir::homePath(), "PNG (*.png);;JPEG (*.jpeg)");
    // Jeżeli pobrano nazwę
    if(nazwa!=nullptr)
    {
        // Zamiana z objektu klasy QString na zmienną typu string
        std::string str = nazwa.toStdString();
        // Zapis obrazu pod pobraną nazwą
        image->save(str.c_str());
    }
}

/**
 * @brief Funkcja zapisująca mapę do pliku tekstowego
 * @param W Liczba wierszy mapy
 * @param K Liczba kolumn mapy
 * @param okno wskaźnik do okna głównego programu
 * @param m Tablica przechowująca mapę
 */

void zapiszDoPlikuTxt(int W, int K, QWidget *okno, komorka **m)
{
    // Otwarcie okna zapisu i pobranie nazwy pliku do objektu klasy QString
    // plik zapisany jako plik tekstowy
    QString nazwa = QFileDialog::getSaveFileName(okno, "Zapisz mapę", QDir::homePath(), "TXT (*.txt)");
    // Jeżeli pobrano nazwę
    if(nazwa!=nullptr)
    {
        // Zamiana z objektu klasy QString na zmienną typu string
        std::string str = nazwa.toStdString();
        // Utworzenie objektu klasy ofstream - plik otwarty do zapisu
        ofstream plik(str.c_str());
        // Zapis kolejnych wierszy z tablicy 'm' przechowującej mapę
        for(int i=0;i<W;i++)
        {
            for(int j=0;j<K;j++)
            {
                plik<<m[i][j].wartoscObecna;
            }
            plik<<endl;
        }
        // zamknięcie pliku
        plik.close();
    }
}

//---------------------------------ODCZYT-Z-PLIKU---------------------------------


// Funkcje do obsługi list
/**
 * @brief Funkcja dodająca nowy element do listy przechowującej wiersze wczytywanej mapy
 * @param p Wskaźnik do początku listy
 */
void dodajDoListy(dane *&p)
{
    if(p==nullptr)
    {
        p=new dane;
        p->nast=nullptr;
        p->w=nullptr;
    }
    else
    {
        dane *h = p;
        while(h->nast)
            h=h->nast;
        dane *n = new dane;
        h->nast = n;
        n->nast = nullptr;
        n->w = nullptr;
    }
}
/**
 * @brief Funkcja dodaje nowy element do listy przechowywującej wartości w wierszach mapy
 * @param p Wskaźnik do początku listy
 * @param x Nowo dodawana wartość
 */
void dodajDoListy(wiersze *&p, int x)
{
    if(p==nullptr)
    {
        p=new wiersze;
        p->nast=nullptr;
        p->x = x;
    }
    else
    {
        wiersze *h = p;
        while(h->nast)
            h=h->nast;
        wiersze *n = new wiersze;
        h->nast = n;
        n->nast = nullptr;
        n->x = x;
    }
}
/**
 * @brief Funkcja usuwająca listę przechowującą wiersze wczytywanej mapy
 * @param g Wskaźnik do początku listy
 */
void usun(wiersze*&g)
{

    while(g)
    {
        wiersze *p = g;
        g = g->nast;
        delete p;

    }
}
/**
 * @brief Funkcja usuwająca listę kolejne wartości w wierszach nowo wczytywanej mapy
 * @param g Wskaźnik do początku listy
 */
void usun(dane*&g)
{

    while(g)
    {
        dane *p = g;
        g = g->nast;
        delete p;

    }
}
/**
 * @brief Funkcja usuwająca listę list przechowywującą wczytywaną mapę
 * @param p Wskaźnik do początku listy list
 */
void UsunLL(dane *&p)
{
    dane *h = p;
    while(h)
    {
        usun(h->w);
        h=h->nast;
    }
    usun(p);
}
/**
 * @brief Funkcja dodająca nowy element do listy list przechowującej wczytywaną mapę
 * @param p Wskaźnik do początku listy list
 * @param x Nowo dodawana wartość
 */
void nowyElement(dane *&p, int x)
{
    dane *h = p;
    while(h->nast)
        h = h->nast;

    dodajDoListy(h->w,x);
}

/**
 * @brief Funkcja przepisująca wartości z listy list do tablicy dynamicznej
 * @param p Wskaźnik do początku listy list
 * @param m Wskaźnik do tablicy przechowującej mapę w innych częściach programu
 * @param wu Liczba wierszy mapy
 * @param ka Liczba kolumn mapy
 */
void doTablicy(dane *p, komorka **&m, int wu, int ka)
{
    m = new komorka *[wu];
    for(int i=0;i<wu;i++)
        m[i] = new komorka [ka];

    dane *h = p;
    wiersze *a = nullptr;

    for(int i=0;i<wu;i++)
    {
        a = h->w;
        for(int j=0;j<ka;j++)
        {
            m[i][j].wartoscObecna = a->x;
            a = a->nast;
        }
        h = h->nast;
    }

}

/**
 * @brief Funkcja wczytująca mapę z pliku
 * @param okno Wskaźnik do głównego okna programu
 * @param m Wskaźnik do tablicy przechowującej mapę
 * @param W Liczba wierszy mapy
 * @param K Liczba kolumn mapy
 * @param czyMamMape Zmienna określająca czy program przechowuje jakąś mapę w tablicy 'm'
 * @return 1 jeśli się udało wczytać mapę, 0 gdy się nie udało
 */
bool Wczytaj(QWidget *okno, komorka**&m, int &W, int &K, bool czyMamMape)
{

    QString nazwa = QFileDialog::getOpenFileName(okno, "Wczytaj mapę", QDir::homePath(), "TXT (*.txt)");

    if(nazwa!=nullptr)
    {
        if(czyMamMape)
            UsunTablice(W,m);

        dane *p = nullptr;

        std::string str = nazwa.toStdString();
        std::ifstream plik(str.c_str());
        char z;
        int i=0,j=0;
        plik.get(z);

        W=0;
        K=0;

        dodajDoListy(p);
        while (((z >= 48 && z < 58) || z == 10) && !plik.eof())
        {
            if(z!=10)
            {
                nowyElement(p, z-48);
                j++;
            }else
            {
                if(i==0)K=j;
                j=0;
                i++;
                dodajDoListy(p);
            }
            plik.get(z);
        }
        W = i;
        doTablicy(p,m,W,K);
        UsunLL(p);
        return 1;
    }
    else
        return 0;
}
