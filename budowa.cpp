#include "budowa.h"

/**
* \file budowa.cpp
* \brief Plik źródłowy modułu Budowa
*/

/**
 * @brief Funkcja tworząca obraz mapy
 *
 * Funkcja tworzy obraz mapy z części grafiki dołączonej do programu na podstawie tablicy 'm'. Najpierw definiowane są współrzędne i wymiary każdego fragmentu mapy,
 *  a następnie na przygotowanym pustym obrazie, umieszczane są jego kolejne warstwy w następującej kolejności:
 * \n 1. Wszystkie obrazy główne trawy, lasu, wody, pustyni i gór
 * \n 2. Krawędzie pustyni
 * \n 3. Rogi pustyni
 * \n 4. Krawędzie trawy
 * \n 5. Rogi trawy
 * \n 6. Krawędzie gór
 * \n 7. Krawędzie lasu
 * \n 8. Rogi lasu
 * @param W Liczba wierszy mapy
 * @param K Liczba kolumn mapy
 * @param m Wskaźnik do mapy
 * @param paintOnImage Obiekt klasy QPainter do rysowania po pliku graficznym
 */

void BudowaMapy(int W, int K, komorka **m, QPainter* paintOnImage)
{
    // Utworzenie objektu klasy QImage przechowywującej obrazy potrzebne do budowy mapy
    // Odczytane z pliku "obrazy.png"
    QImage zrodlo("obrazy.png");

    // Współrzędne obrazów kolejno: trawy, lasu, wody, pustyni, gór
    QPointF Pt(0.0, 0.0);
    QPointF Pl(0.0, 32.0);
    QPointF Pw(0.0, 64.0);
    QPointF Pp(0.0, 96.0);
    QPointF Pg(0.0, 128.0);
    // Współrzędne obrazów krawędzi trawy
    QPointF PktG(0.0, 187.0);
    QPointF PktD(0.0, 160.0);
    QPointF PktL(27.0, 192.0);
    QPointF PktP(0.0, 192.0);
    // Współrzędne obrazów krawędzi lasu
    QPointF PklG(0.0, 251.0);
    QPointF PklD(0.0, 224.0);
    QPointF PklL(22.0, 192.0);
    QPointF PklP(5.0, 192.0);
    // Współrzędne obrazów rogów trawy
    QPointF PktPD(0.0, 178.0);
    QPointF PktLD(13.0, 179.0);
    QPointF PktPG(4.0, 179.0);
    QPointF PktLG(9.0, 178.0);
    // Współrzędne obrazów rogów lasu
    QPointF PklPD(12.0, 247.0);
    QPointF PklLD(8.0, 247.0);
    QPointF PklPG(0.0, 247.0);
    QPointF PklLG(4.0, 247.0);
    // Współrzędne obrazów krawędzi gór
    QPointF PkgG(0.0, 347.0);
    QPointF PkgD(0.0, 320.0);
    QPointF PkgL(17.0, 192.0);
    QPointF PkgP(10.0, 192.0);
    // Współrzędne obrazów krawędzi pustyni
    QPointF PkpG(0.0, 283.0);
    QPointF PkpD(0.0, 256.0);
    QPointF PkpL(27.0, 288.0);
    QPointF PkpP(0.0, 288.0);
    // Współrzędne obrazów rogów pustyni
    QPointF PkpPD(0.0, 274.0);
    QPointF PkpLD(13.0, 275.0);
    QPointF PkpPG(4.0, 275.0);
    QPointF PkpLG(9.0, 274.0);

    // Wymiary krawędzi poziomych i pionowych
    QSizeF krawedzie(32.0, 5.0);
    QSizeF krawedzie2(5.0, 32.0);
    // Różne wymiary rogów
    QSizeF rog1(4.0, 5.0);
    QSizeF rog2(5.0, 4.0);
    QSizeF rog(4.0, 4.0);
    // Rzomiar komórki
    QSizeF rozmiar(32.0, 32.0);


    // Połączenie ww. danych
    //r - rogi              P - prawa
    //kr - krawędzie        L - lewa
    //                      D - dół
    //                      G - góra

    QRectF trawa(Pt, rozmiar);
    QRectF las(Pl, rozmiar);
    QRectF woda(Pw, rozmiar);
    QRectF pustynia(Pp, rozmiar);
    QRectF gory(Pg, rozmiar);

    QRectF krTrawyGora(PktG, krawedzie);
    QRectF krTrawyDol(PktD, krawedzie);
    QRectF krTrawyLewa(PktL, krawedzie2);
    QRectF krTrawyPrawa(PktP, krawedzie2);

    QRectF rTrawyPD(PktPD, rog1);
    QRectF rTrawyLD(PktLD, rog2);
    QRectF rTrawyPG(PktPG, rog2);
    QRectF rTrawyLG(PktLG, rog1);

    QRectF krLasuG(PklG, krawedzie);
    QRectF krLasuD(PklD, krawedzie);
    QRectF krLasuL(PklL, krawedzie2);
    QRectF krLasuP(PklP, krawedzie2);

    QRectF rLasuPD(PklPD, rog);
    QRectF rLasuLD(PklLD, rog);
    QRectF rLasuPG(PklPG, rog);
    QRectF rLasuLG(PklLG, rog);

    QRectF krGoryG(PkgG, krawedzie);
    QRectF krGoryD(PkgD, krawedzie);
    QRectF krGoryL(PkgL, krawedzie2);
    QRectF krGoryP(PkgP, krawedzie2);

    QRectF krPustyniGora(PkpG, krawedzie);
    QRectF krPustyniDol(PkpD, krawedzie);
    QRectF krPustyniLewa(PkpL, krawedzie2);
    QRectF krPustyniPrawa(PkpP, krawedzie2);

    QRectF rPustyniPD(PkpPD, rog1);
    QRectF rPustyniLD(PkpLD, rog2);
    QRectF rPustyniPG(PkpPG, rog2);
    QRectF rPustyniLG(PkpLG, rog1);

    //miejsce "wklejania" kolejnych części mapy
    QRectF miejsce(0.0,0.0,32.0,32.0);


    for(int i=0;i<W;i++)
    {

        for(int j=0;j<K;j++)
        {
            miejsce.setRect(j*32.0, i*32.0, 32.0, 32.0);


            if(m[i][j].wartoscObecna == 0)
               paintOnImage->drawImage(miejsce, zrodlo, woda);
            else if(m[i][j].wartoscObecna==2)
               paintOnImage->drawImage(miejsce, zrodlo, trawa);
            else if(m[i][j].wartoscObecna==3)
               paintOnImage->drawImage(miejsce, zrodlo, las);
            else if(m[i][j].wartoscObecna==4)
               paintOnImage->drawImage(miejsce, zrodlo, pustynia);
            else if(m[i][j].wartoscObecna==5)
               paintOnImage->drawImage(miejsce, zrodlo, gory);
        }

    }

    //pustynia
    for(int i = 0;i<W;i++)
    {
        for(int j=0;j<K;j++)
        {
            if(m[i][j].wartoscObecna==4)
            {
                if(j>0)
                {
                    if(m[i][j-1].wartoscObecna==0)
                    {
                        miejsce.setRect((j)*32.0-5.0,(i)*32.0, 5.0, 32.0);
                        paintOnImage->drawImage(miejsce, zrodlo, krPustyniLewa);

                    }

                }
                if(j<K-1)
                {
                    if(m[i][j+1].wartoscObecna==0)
                    {
                        miejsce.setRect((j+1)*32.0,(i)*32.0, 5.0, 32.0);
                        paintOnImage->drawImage(miejsce, zrodlo, krPustyniPrawa);
                    }

                }
                if(i>0)
                {
                    if(m[i-1][j].wartoscObecna==0)
                    {
                        miejsce.setRect((j)*32.0,(i)*32.0-5.0, 32.0, 5.0);
                        paintOnImage->drawImage(miejsce, zrodlo, krPustyniGora);
                    }

                }
                if(i<W-1)
                {
                    if(m[i+1][j].wartoscObecna==0)
                    {
                        miejsce.setRect((j)*32.0,(i+1)*32.0, 32.0, 5.0);
                        paintOnImage->drawImage(miejsce, zrodlo, krPustyniDol);
                    }

                }
            }
        }
    }

    for(int i = 0;i<W;i++)
    {
        for(int j=0;j<K;j++)
        {
            if(m[i][j].wartoscObecna==4)
            {
                if(j>0 && i>0)
                {
                    if(m[i][j-1].wartoscObecna==0 && m[i-1][j].wartoscObecna==0 && m[i-1][j-1].wartoscObecna==0)
                    {
                        miejsce.setRect((j)*32.0-4.0,(i)*32.0-5.0, 4.0, 5.0);
                        paintOnImage->drawImage(miejsce, zrodlo, rPustyniLG);

                    }

                }
                if(j<K-1 && i>0)
                {
                    if(m[i][j+1].wartoscObecna==0 && m[i-1][j].wartoscObecna==0 && m[i-1][j+1].wartoscObecna==0)
                    {
                        miejsce.setRect((j+1)*32.0,(i)*32.0 - 4.0, 5.0, 4.0);
                        paintOnImage->drawImage(miejsce, zrodlo, rPustyniPG);
                    }

                }
                if(j<K-1 && i<W-1)
                {
                    if(m[i+1][j].wartoscObecna==0 && m[i][j+1].wartoscObecna==0 && m[i+1][j+1].wartoscObecna==0)
                    {
                        miejsce.setRect((j+1)*32.0,(i+1)*32.0, 4.0, 5.0);
                        paintOnImage->drawImage(miejsce, zrodlo, rPustyniPD);
                    }

                }
                if(i<W-1 && j>0)
                {
                    if(m[i+1][j].wartoscObecna==0 && m[i][j-1].wartoscObecna==0 && m[i+1][j-1].wartoscObecna==0)
                    {
                        miejsce.setRect((j)*32.0-5.0,(i+1)*32.0, 5.0, 4.0);
                        paintOnImage->drawImage(miejsce, zrodlo, rPustyniLD);
                    }

                }
            }
        }
    }
//krawędzie lądu
    for(int i = 0;i<W;i++)
    {
        for(int j=0;j<K;j++)
        {
            if(m[i][j].wartoscObecna==2||m[i][j].wartoscObecna==3)
            {
                if(j>0)
                {
                    if(m[i][j-1].wartoscObecna==0||m[i][j-1].wartoscObecna==4)
                    {
                        miejsce.setRect((j)*32.0-5.0,(i)*32.0, 5.0, 32.0);
                        paintOnImage->drawImage(miejsce, zrodlo, krTrawyLewa);

                    }

                }
                if(j<K-1)
                {
                    if(m[i][j+1].wartoscObecna==0||m[i][j+1].wartoscObecna==4)
                    {
                        miejsce.setRect((j+1)*32.0,(i)*32.0, 5.0, 32.0);
                        paintOnImage->drawImage(miejsce, zrodlo, krTrawyPrawa);
                    }

                }
                if(i>0)
                {
                    if(m[i-1][j].wartoscObecna==0||m[i-1][j].wartoscObecna==4)
                    {
                        miejsce.setRect((j)*32.0,(i)*32.0-5.0, 32.0, 5.0);
                        paintOnImage->drawImage(miejsce, zrodlo, krTrawyGora);
                    }

                }
                if(i<W-1)
                {
                    if(m[i+1][j].wartoscObecna==0||m[i+1][j].wartoscObecna==4)
                    {
                        miejsce.setRect((j)*32.0,(i+1)*32.0, 32.0, 5.0);
                        paintOnImage->drawImage(miejsce, zrodlo, krTrawyDol);
                    }

                }
            }
        }
    }
//rogi lądu
    for(int i = 0;i<W;i++)
    {
        for(int j=0;j<K;j++)
        {
            if(m[i][j].wartoscObecna==2||m[i][j].wartoscObecna==3)
            {
                if(j>0 && i>0)
                {
                    if((m[i][j-1].wartoscObecna==0 || m[i][j-1].wartoscObecna==4 )&& (m[i-1][j].wartoscObecna==0||m[i-1][j].wartoscObecna==4) && (m[i-1][j-1].wartoscObecna==0||m[i-1][j-1].wartoscObecna==4))
                    {
                        miejsce.setRect((j)*32.0-4.0,(i)*32.0-5.0, 4.0, 5.0);
                        paintOnImage->drawImage(miejsce, zrodlo, rTrawyLG);

                    }

                }
                if(j<K-1 && i>0)
                {
                    if((m[i][j+1].wartoscObecna==0 ||m[i][j+1].wartoscObecna==4 )&& (m[i-1][j].wartoscObecna==0||m[i-1][j].wartoscObecna==4) && (m[i-1][j+1].wartoscObecna==0||m[i-1][j+1].wartoscObecna==4))
                    {
                        miejsce.setRect((j+1)*32.0,(i)*32.0 - 4.0, 5.0, 4.0);
                        paintOnImage->drawImage(miejsce, zrodlo, rTrawyPG);
                    }

                }
                if(j<K-1 && i<W-1)
                {
                    if((m[i+1][j].wartoscObecna==0||m[i+1][j].wartoscObecna==4) && (m[i][j+1].wartoscObecna==0||m[i][j+1].wartoscObecna==4) && (m[i+1][j+1].wartoscObecna==0||m[i+1][j+1].wartoscObecna==4))
                    {
                        miejsce.setRect((j+1)*32.0,(i+1)*32.0, 4.0, 5.0);
                        paintOnImage->drawImage(miejsce, zrodlo, rTrawyPD);
                    }

                }
                if(i<W-1 && j>0)
                {
                    if((m[i+1][j].wartoscObecna==0||m[i+1][j].wartoscObecna==4) && (m[i][j-1].wartoscObecna==0||m[i][j-1].wartoscObecna==4) && (m[i+1][j-1].wartoscObecna==0||m[i+1][j-1].wartoscObecna==4))
                    {
                        miejsce.setRect((j)*32.0-5.0,(i+1)*32.0, 5.0, 4.0);
                        paintOnImage->drawImage(miejsce, zrodlo, rTrawyLD);
                    }

                }
            }
        }
    }

//krawędzie gory
    for(int i = 0;i<W;i++)
    {
        for(int j=0;j<K;j++)
        {
            if(m[i][j].wartoscObecna==5)
            {
                if(j>0)
                {
                    if(m[i][j-1].wartoscObecna!=5&&m[i][j-1].wartoscObecna!=3)
                    {
                        miejsce.setRect((j)*32.0-5.0,(i)*32.0, 5.0, 32.0);
                        paintOnImage->drawImage(miejsce, zrodlo, krGoryL);

                    }

                }
                if(j<K-1)
                {
                    if(m[i][j+1].wartoscObecna!=5&&m[i][j+1].wartoscObecna!=3)
                    {
                        miejsce.setRect((j+1)*32.0,(i)*32.0, 5.0, 32.0);
                        paintOnImage->drawImage(miejsce, zrodlo, krGoryP);
                    }

                }
                if(i>0)
                {
                    if(m[i-1][j].wartoscObecna!=5&&m[i-1][j].wartoscObecna!=3)
                    {
                        miejsce.setRect((j)*32.0,(i)*32.0-5.0, 32.0, 5.0);
                        paintOnImage->drawImage(miejsce, zrodlo, krGoryG);
                    }

                }
                if(i<W-1)
                {
                    if(m[i+1][j].wartoscObecna!=5&&m[i+1][j].wartoscObecna!=3)
                    {
                        miejsce.setRect((j)*32.0,(i+1)*32.0, 32.0, 5.0);
                        paintOnImage->drawImage(miejsce, zrodlo, krGoryD);
                    }

                }
            }
        }

    }

    for(int i = 0;i<W;i++)
    {
        for(int j=0;j<K;j++)
        {
            if(m[i][j].wartoscObecna==3)
            {
                if(j>0)
                {
                    if(m[i][j-1].wartoscObecna!=3)
                    {
                        miejsce.setRect((j)*32.0-5.0,(i)*32.0, 5.0, 32.0);
                        paintOnImage->drawImage(miejsce, zrodlo, krLasuL);

                    }

                }
                if(j<K-1)
                {
                    if(m[i][j+1].wartoscObecna!=3)
                    {
                        miejsce.setRect((j+1)*32.0,(i)*32.0, 5.0, 32.0);
                        paintOnImage->drawImage(miejsce, zrodlo, krLasuP);
                    }

                }
                if(i>0)
                {
                    if(m[i-1][j].wartoscObecna!=3)
                    {
                        miejsce.setRect((j)*32.0,(i)*32.0-5.0, 32.0, 5.0);
                        paintOnImage->drawImage(miejsce, zrodlo, krLasuG);
                    }

                }
                if(i<W-1)
                {
                    if(m[i+1][j].wartoscObecna!=3)
                    {
                        miejsce.setRect((j)*32.0,(i+1)*32.0, 32.0, 5.0);
                        paintOnImage->drawImage(miejsce, zrodlo, krLasuD);
                    }

                }
            }
        }
    }

    for(int i = 0;i<W;i++)
    {
        for(int j=0;j<K;j++)
        {
            if(m[i][j].wartoscObecna==3)
            {
                if(j>0 && i>0)
                {
                    if(m[i][j-1].wartoscObecna!=3 && m[i-1][j].wartoscObecna!=3 && m[i-1][j-1].wartoscObecna!=3)
                    {
                        miejsce.setRect((j)*32.0-4.0,(i)*32.0-4.0, 4.0, 4.0);
                        paintOnImage->drawImage(miejsce, zrodlo, rLasuLG);

                    }

                }
                if(j<K-1 && i>0)
                {
                    if(m[i][j+1].wartoscObecna!=3 && m[i-1][j].wartoscObecna!=3 && m[i-1][j+1].wartoscObecna!=3)
                    {
                        miejsce.setRect((j+1)*32.0,(i)*32.0 - 4.0, 4.0, 4.0);
                        paintOnImage->drawImage(miejsce, zrodlo, rLasuPG);
                    }

                }
                if(j<K-1 && i<W-1)
                {
                    if(m[i+1][j].wartoscObecna!=3 && m[i][j+1].wartoscObecna!=3 && m[i+1][j+1].wartoscObecna!=3)
                    {
                        miejsce.setRect((j+1)*32.0,(i+1)*32.0, 4.0, 4.0);
                        paintOnImage->drawImage(miejsce, zrodlo, rLasuPD);
                    }

                }
                if(i<W-1 && j>0)
                {
                    if(m[i+1][j].wartoscObecna!=3 && m[i][j-1].wartoscObecna!=3 && m[i+1][j-1].wartoscObecna!=3)
                    {
                        miejsce.setRect((j)*32.0-4.0,(i+1)*32.0, 4.0, 4.0);
                        paintOnImage->drawImage(miejsce, zrodlo, rLasuLD);
                    }

                }
            }
        }
    }
}
