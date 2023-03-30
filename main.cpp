#include "mainwindow.h"

#include <QApplication>

/**
* \file main.cpp
* \brief Główna funkcja programu
*/

/**
 * @brief Główna funkcja frogramu
 */
int main(int argc, char *argv[])
{


    srand(time(0));

    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();



    return a.exec();
}

/**
 * \mainpage
 * \par Projekt z Przedmiotu ZAP II
 * Generator mapy do gry strategiczno-ekonomicznej
 * \author Mateusz Kochański
 * \date 25.05.2020
 * \version Gamma
 * \par Kontakt:
 * \a 01150977@pw.edu.pl
 * \par Cel projektu
 * Program powstał w celu realizacji projektu z przedmiotu ZAP II.
 * \n Jego zadaniem jest generowanie map 2D o określonych przez urzytkownika parametrach. Zapewnia możliwość zapisu i odczytu generowanych map, a mapy wyświetlane są w estetyczny i wygodny do przeglądania sposób.
 *\par Instrukcja
 * Aby wygenerować mapę należy ustawić odpowiednie parametry w panelu obsługi (opis parametrów na dole instrukcji), a następnie wcisnąć przycisk "Generuj mapę".
 * \n Aby usunąć mapę należy wcisnąć przycisk "Usuń mapę".
 * \n Aby zapisać mapę należy wcisnąć przycisk "Zapisz w formacie .txt", następnie nazwać plik i wcisnąć "Zapisz".
 * \n Aby zapisać obraz mapy należy wcisnąć przycisk "Zapisz obraz mapy", następnie nazwać plik i wcisnąć "Zapisz".
 * \n Aby wczytać mapę należy wcisnąć przycisk "Wczytaj mapę", następnie wybrać odpowiedni plik i wcisnąć "Otwórz".
 * \n Jeśli cała mapa nie mieści się na ekranie, można ją przesuwać. Aby to zrobić należy nakierować myszkę na mapę, wcisnąć lewy przycisk myszy, a następnie przesunąć ją w dowolnym kierunku.
 * \n\n Parametry generowanej mapy:
 * \n Szerokość mapy - liczba kolumn z jakiej będzie składać się genrowana mapa
 * \n Wysokość mapy - liczba wierszy z jakiej będzie się składać generowana mapa
 * \n Wypełnienie - Wypełnienie mapy lądem wyrażone w procentach
 * \n Liczba ziaren - Liczba pojedyńczych punktów z których będą generować się wyspy na mapie
*/
