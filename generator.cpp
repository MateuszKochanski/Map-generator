#include "generator.h"
#include <fstream>

/**
* \file generator.cpp
* \brief Plik źródłowy modułu Generator
*/

//--------------------------OBSŁUGA-TABLICY-ZAWIERAJĄCEJ-MAPĘ--------------------------

/**
 * @brief Tworzenie tablicy i zapełnienie jej zerami
 * @param w Liczba wierszy tablicy
 * @param k Liczba kolumn tablicy
 * @return Wskaźnik do utworzonej tablicy
 */
komorka **PrzygotujTablice(int w, int k)
{
    komorka **m = new komorka *[w];
    for(int i=0;i<w;i++)
        m[i] = new komorka [k];

    for(int i=0;i<w;i++)
    {
        for(int j=0;j<k;j++)
        {
            m[i][j].wartoscObecna=0;
            m[i][j].wartoscPrzyszla=0;
        }
    }

    return m;
}

/**
 * @brief Usuwanie tablicy
 * @param w Liczba wierszy tablicy
 * @param m Wskaźnik do tablicy
 */
void UsunTablice(int w, komorka **m)
{
    for(int i=0;i<w;i++)
        delete [] m[i];
    delete [] m;
}

//---------------------------------GENEROWANIE-MAPY-------------------------------------

/**
 * @brief Funkcja generująca mapę
 *
 * 1. Funkcja Losuje wybraną przez użytkownika liczbę punktów na mapie
 * 2. Losuje wielkości poszczególnych wysp
 * 3. Uruchamia generowanie kolejnych wysp o wylosowanych wcześniej parametrach
 * @param W Liczba wierszy mapy
 * @param K Liczba kolumn mapy
 * @param m Wskaźnik do tablicy przechowującej mapę
 * @param wypelnienie Wyrażone w procentach wypełnienie mapy lądem
 * @param liczbaZiaren Liczba punktów rozrostu mapy
 */
void generujMape(int W, int K, komorka **m, int wypelnienie, int liczbaZiaren)
{

    int r = (W*K*wypelnienie)/100;
    if(liczbaZiaren>r)
        liczbaZiaren=r;
    int w,k;


    double s = 0;
    int s2 = 0;
    double *T = new double [liczbaZiaren];
    for(int i=0;i<liczbaZiaren;i++)
    {
        T[i] = (rand()%10+1);
        s += T[i];
    }
    int a;
    for(a=0;a<liczbaZiaren;a++)
    {
        T[a] = int((T[a]/s)*r);
        s2 += int(T[a]);

    }
    T[a-1] += r-s2;

    int gory = 2;                                           //pokrycie lądu górami
    int pustynie = 4;                                       //pokrycie lądu pustyniami
    int lasy = 4;                                           //pokrycie lądu lasami
    //Wskaźnik do listy przechowującej wszystkie sąsiednie pola do generowanej wyspy
    lista *lad;
    //Lista przechowująca wszystkie pola generowanej wyspy i sąsiednie pola
    lista *wyspa;
    int x = 0;

    for(int i=0;i<liczbaZiaren;i++)
    {
        if(int(T[i])>0)
        {

            do
            {
                do
                {
                    w = rand()%W;
                    k = rand()%K;
                }while(m[w][k].wartoscObecna != 0);


                lad = nullptr;
                wyspa = nullptr;

                x = rozrost(W,K,w,k,lad,wyspa,m,int(T[i]));
                nadajTerenWyspie(W,K,wyspa,x,m,gory,pustynie,lasy); //funkcja generująca teren na na wyspie
                usun(lad);                                          //usuwanie listy lad
                usun(wyspa);                                        //usuwanie listy wyspa
                T[i]-=x;
            }while(T[i]>0);

        }
    }

    delete [] T;

}

//---------------------------------GENEROWANIE-LĄDU-------------------------------------

/**
 * @brief Funkcja tworząca jedną wyspę zaczynając od podanego punktu.
 *
 * 1. Funkcja dodaje do listy przechowującej generowaną mapę pierwszy punkt
 * 2. Uruchamia w pętli funkcję losującą kolejne pola wyspy na mapie
 * @param W Liczba wierszy mapy
 * @param K Liczba kolumn mapy
 * @param w Numer wiersza punktu początkowego tworzenia się mapy
 * @param k Numer kolumny punktu początkowego tworzenia się mapy
 * @param g Wskaźnik do listy przechowującej wszystkie sąsiednie pola do wyspy
 * @param o Lista przechowująca wszystkie pola wyspy i sąsiednie pola
 * @param m Wskaźnik do tablicy przechowującej mapę
 * @param r Liczba komórek z których ma składać się generowana wyspa
 * @return Liczba pól ile udało się wygenerować (z powodu krztału i położenia wyspy nie zawsze ta liczba zgadza się z liczbą komórek z jakiej powinna składać się wyspa)
 */
int rozrost(int W, int K, int w, int k, lista *&g, lista *&o, komorka **m, int r)
{
    int n = 0;                                                      //liczba elementów w liście
    int l = 1;                                                      //liczba wygenerowanych pól
    m[w][k].wartoscObecna = 1;
    dodajDoListy(w,k,o);
    Dodaj(W,K,w,k,g,o,m,n,l,r);

    while(l<r&&n>0)
        losujNastepnaKomorke(W,K,g,o,m,n,l,r);

    return l;
}

/**
 * @brief Funkcja losująca jedną z sąsiednich pól wyspy
 *
 * 1. Funkcja losuje jedno pole z listy przechowującej wszystkie pola dookoła generowanej wyspy
 * 2. Uruchamia funkcję dodającą to pole do wyspy
 * @param W Liczba wierszy mapy
 * @param K Liczba kolumn mapy
 * @param g Wskaźnik do listy przechowującej wszystkie sąsiednie pola do wyspy
 * @param o Lista przechowująca Wszystkie pola wyspy i sąsiednie pola
 * @param m Wskaźnik do tablicy przechowującej mapę
 * @param n Liczba elementów w liście 'g' (liczba sąsiednich komórek)
 * @param l Liczba już wygenerowanych komórek wyspy
 * @param r Liczba komórek z których ma składać się generowana wyspa
 */
void losujNastepnaKomorke(int W, int K, lista *&g, lista *&o, komorka**m,int &n, int &l, int r)
{
    lista *p = g;
    int licznik = 1;
    int los = rand()%n;

    while (1< los && p->nast) {
        los -= 1;
        p = p->nast;
        licznik++;
    }

    nowaKomorka(W,K,p->w,p->k,g,o,m,licznik,n,l,r);

}
/**
 * @brief Funkcja dodające wylosowaną komórkę do wyspy
 *
 * 1. Funkcja dodaje do tablicy przechowującej mapę, nowo wylosowaną komórkę
 * 2. Usuwa ją z listy przechowującej wszystkie sąsiednie pola do wyspy
 * 3. Jeśli trzeba uruchamia funkcję dodającą następne pola do listy przechowującej wszystkie sąsiednie pola
 * @param W Liczba wierszy mapy
 * @param K Liczba kolumn mapy
 * @param w Numer wiersza nowo dodanej komórki do wyspy
 * @param k Numer kolumny nowo dodanej komórki do wyspy
 * @param g Wskaźnik do listy przechowującej wszystkie sąsiednie pola do wyspy
 * @param o Lista przechowująca Wszystkie pola wyspy i sąsiednie pola
 * @param m Wskaźnik do tablicy przechowującej mapę
 * @param x Numer nowo dodanej komórki w liście 'g'
 * @param n Liczba elementów w liście 'g' (liczba sąsiednich komórek)
 * @param l Liczba już wygenerowanych komórek wyspy
 * @param r Liczba komórek z których ma składać się generowana wyspa
 */
void nowaKomorka(int W, int K, int w ,int k , lista *&g, lista *&o, komorka**m, int x, int &n,int &l, int r)
{
    m[w][k].wartoscObecna = 1;
    usunZListy(g,x);
    n--;
    if(n>0)
        Dodaj(W,K,w,k,g,o,m,n,l,r);
}

/**
 * @brief Funkcja dodająca do list, komórki z sąsiedztwa, nowo dodanej komórki do wyspy
 *
 * Funkcja sprawdza po kolei wszystkie kierunki od nowo dodanej komórki i jeśli jest możliwość dodaje je do list
 * @param W Liczba wierszy mapy
 * @param K Liczba kolumn mapy
 * @param wp Numer wiersza nowo dodanej komórki do wyspy
 * @param kp Numer kolumny nowo dodanej komórki do wyspy
 * @param g Wskaźnik do listy przechowującej wszystkie sąsiednie pola do wyspy
 * @param o Lista przechowująca Wszystkie pola wyspy i sąsiednie pola
 * @param m Wskaźnik do tablicy przechowującej mapę
 * @param n Liczba elementów w liście 'g' (liczba sąsiednich komórek)
 * @param l Liczba już wygenerowanych komórek wyspy
 * @param r Liczba komórek z których ma składać się generowana wyspa
 */
void Dodaj(int W, int K, int wp, int kp, lista *&g, lista *&o, komorka**m,  int &n, int &l, int r)
{
    int a = 1;
    if(wp>0 && l<r)//góra
    {
        if(m[wp-1][kp].wartoscObecna == 0)
        {
            n++;
            l++;
            dodajDoListy(wp-1,kp,g);
            dodajDoListy(wp-1,kp,o);
            m[wp-1][kp].wartoscObecna = a;
        }

    }
    if(kp<K-1 && l<r)//prawa
    {
        if(m[wp][kp+1].wartoscObecna == 0)
        {
            n++;
            l++;
            dodajDoListy(wp,kp+1,g);
            dodajDoListy(wp,kp+1,o);
            m[wp][kp+1].wartoscObecna = a;
        }
    }
    if(wp<W-1 && l<r)//dół
    {
        if(m[wp+1][kp].wartoscObecna == 0)
        {
            n++;
            l++;
            dodajDoListy(wp+1,kp,g);
            dodajDoListy(wp+1,kp,o);
            m[wp+1][kp].wartoscObecna = a;
        }
    }
    if(kp>0 && l<r)//lewa
    {
        if(m[wp][kp-1].wartoscObecna == 0)
        {
            n++;
            l++;
            dodajDoListy(wp,kp-1,g);
            dodajDoListy(wp,kp-1,o);
            m[wp][kp-1].wartoscObecna = a;
        }
    }
}


//-------------------------------GENEROWANIE-TERENU-------------------------------------

/**
 * @brief Funkcja nadająca teren wyspie złożonej z komórek zawartych w liście 'o'
 * @param W Liczba wierszy mapy
 * @param K Liczba kolumn mapy
 * @param o Lista przechowująca Wszystkie pola wyspy i sąsiednie pola
 * @param r Liczba komórek z których składa się wyspa
 * @param m Wskaźnik do tablicy przechowującej mapę
 * @param a Współczynnik pokrycie lądu górami
 * @param b Współczynnik pokrycie lądu pustyniami
 * @param c Współczynnik pokrycie lądu lasem
 */
void nadajTerenWyspie(int W, int K, lista *&o, int r, komorka **m, int a, int b, int c)
{
    lista *p =o;
    int z = r;//nie przyznane pola
    int liczbaGor = r/400+(rand()%2);
    int liczbaPustyn = r/600+(rand()%2);
    int liczbaLasow = r/100+(rand()%2)*(rand()%2);


    terenuj(W,K,z,liczbaGor,6,a,5,o,m);
    if(z)terenuj(W,K,z,liczbaPustyn,6,b,4,o,m);//////
    if(z)terenuj(W,K,z,liczbaLasow,5,c,3,o,m);
    if(z)
    {
        p = o;
        while(p)
        {
            m[p->w][p->k].wartoscObecna = 2;
            p = p->nast;
        }
    }

}

/**
 * @brief Funkcja losująca pierwsze punkty określonego terenu
 * @param W Liczba wierszy mapy
 * @param K Liczba kolumn mapy
 * @param z Liczba komórek o nie przyznanym rodzaju terenu
 * @param liczbaZrodel Liczba pierwszych wygenerowanych punktów określonego terenu
 * @param gestosc Współczynnik pokrycia lądu danym terenem
 * @param powtorzenia Liczba powtórzeń rozrostu określonego rodzaju terenu
 * @param teren Rodzaj generowanego terenu
 * @param o Lista przechowująca Wszystkie pola wyspy i sąsiednie pola
 * @param m Wskaźnik do tablicy przechowującej mapę
 */
void terenuj(int W,int K, int &z, int liczbaZrodel, int gestosc, int powtorzenia, int teren, lista *&o, komorka **m)
{
    int centra;
    lista *p = o;


    for(int i=0;i<liczbaZrodel;i++)
    {
        p=o;
        centra = rand()%z;
        for(int j=0;j<centra;j++)
        {
            p=p->nast;
        }

        m[p->w][p->k].wartoscObecna=teren;
        usunZListy(o,centra+1);
        z--;
    }

    for(int i=0;i<powtorzenia;i++)
    {
        if(z)
            etap(W,K,z,gestosc,teren,o,m);
    }
}



/**
 * @brief Funkcja która dla każdej komórki z listy 'o' przyznaje określony teren, jeśli spełni ona pewne warunki
 *
 * 1. Funkcja bada prawdopodobieństwo wystąpienia danego rodzaju terenu w kolejnych komórkach i na tej podstawie ustawia przyszłe rodzaje terenu wyspy
 * 2. Przepisuje nowe wartości przyszłe do wartości obecnych
 * @param W Liczba wierszy mapy
 * @param K Liczba kolumn mapy
 * @param z Liczba komórek o nie przyznanym rodzaju terenu
 * @param x Współczynnik pokrycia lądu danym terenem
 * @param teren Rodzaj generowanego terenu
 * @param o Lista przechowująca Wszystkie pola wyspy i sąsiednie pola
 * @param m Wskaźnik do tablicy przechowującej mapę
 */
void etap(int W,int K, int &z, int x, int teren, lista *&o,komorka **m)
{
    lista *p;
    int y;
    int licznik;

    p = o;

    while(p)
    {
        y=rand()%x;

        if(y<prawdopodobienstwo(W,K,p->w,p->k,m,teren))
            m[p->w][p->k].wartoscPrzyszla = teren;
        p=p->nast;
    }

    p = o;

    licznik = 0;
    while(p)
    {
        licznik++;
        if(m[p->w][p->k].wartoscPrzyszla == teren)
        {
           m[p->w][p->k].wartoscObecna = teren;
           p=p->nast;
           usunZListy(o,licznik);
           licznik--;
           z--;
        }
        else
            p=p->nast;
    }
}

/**
 * @brief Funkcja określająca prawdopodobieństwo wystąpienia danego rodzaju terenu w danej komórce
 *
 * Funkcja, na podstawie ilości wystąpienia danego rodzaju terenu w okolicy badanego punktu, oblicza współczynnik prawdopodobieństwa
 *  wystąpienia danego rodzaju terenu w badanej komórce
 * @param W Liczba wierszy mapy
 * @param K Liczba kolumn mapy
 * @param w Numer wiersza badanej komórki
 * @param k Numer kolumny badanej komórki
 * @param m Wskaźnik do tablicy przechowującej mapę
 * @param co Rodzaj generowanego terenu
 * @return Współczynnik prawdopodobieństwa wystąpienia danego rodzaju terenu w określonej komórce
 */
int prawdopodobienstwo(int W, int K, int w, int k, komorka **m, int co)
{
    int x = 0;
    //góra
    if(w>0)
        if(m[w-1][k].wartoscObecna == co)
            x+=2;
    //dół
    if(w<W-1)
        if(m[w+1][k].wartoscObecna == co)
            x+=2;
    //lewa
    if(k>0)
        if(m[w][k-1].wartoscObecna == co)
            x+=2;
    //prawa
    if(k<K-1)
        if(m[w][k+1].wartoscObecna == co)
            x+=2;
    //góra lewa
    if(w>0 && k>0)
        if(m[w-1][k-1].wartoscObecna == co)
            x+=2;
    //dół lewa
    if(w<W-1 && k>0)
        if(m[w+1][k-1].wartoscObecna == co)
            x+=2;
    //dół prawa
    if(w<W-1 && k<K-1)
        if(m[w+1][k+1].wartoscObecna == co)
            x+=2;
    //góra prawa
    if(w>0 && k<K-1)
        if(m[w-1][k+1].wartoscObecna == co)
            x+=2;
    //góra góra
    if(w-1>0)
        if(m[w-2][k].wartoscObecna == co)
            x+=1;
    //lewa lewa
    if(k-1>0)
        if(m[w][k-2].wartoscObecna == co)
            x+=1;
    //prawa prawa
    if(k<K-2)
        if(m[w][k+2].wartoscObecna == co)
            x+=1;
    //góra góra
    if(w-1>0)
        if(m[w-2][k].wartoscObecna == co)
            x+=1;
    //dół dół
    if(w<W-2)
        if(m[w+2][k].wartoscObecna == co)
            x+=1;

    return x;
}

//----------------------------------OBSŁUGA-LIST----------------------------------------

/**
 * @brief Funkcja usuwająca listę jednokierunkową
 * @param g Wskaźnik do pierwszego elementu listy
 */
void usun(lista*&g)
{

    while(g)
    {
        lista *p = g;
        g = g->nast;
        delete p;

    }
}

/**
 * @brief Funkcja usuwająca z listy element o numerze x licząc od początku
 * @param g Wskaźnik do pierwszego elementu listy
 * @param x Numer usuwanego elementu
 */
void usunZListy(lista *&g, int x)
{
    lista *n = g;
    if(x==1)
    {
        g = g->nast;
        delete n;
    }else
    {
        for(int i=1;i<x-1;i++)
        {
            n = n->nast;
        }
        lista *d = n->nast;
        n->nast = d->nast;
        delete d;
    }
}

/**
 * @brief Funkcja dodająca element do listy
 * @param w Numer wiersza dodawanego elementu
 * @param k Numer kolumny dodawanego elementu
 * @param g Wskaźnik do pierszego elementu listy
 */
void dodajDoListy(int w, int k, lista *&g)
{
    if(g==nullptr)
    {
        g=new lista;
        g->nast=nullptr;
        g->w=w;
        g->k=k;
    }
    else
    {
        lista *p = g;
        while(p->nast)
            p=p->nast;
        lista *n = new lista;
        p->nast = n;
        n->nast = nullptr;
        n->w = w;
        n->k = k;
    }
}
