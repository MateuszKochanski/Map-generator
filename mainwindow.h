#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include "generator.h"                                  //generowanie mapy
#include "podstawa.h"                                   //różne biblioteki i definicje struktur używanych w całym projekcie

/**
* \file mainwindow.h
* \brief Plik nagłówkowy modułu Mainwindow
*/

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief Klasa dziedzicząca po klasie QMainWindow, zawierająca między innymi wszystkie elementy wystroju okna programu
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    ///Zmienna określająca czy program przechowuje jakąś mapę
    bool czyMamMape = 0;
    ///Liczba wierszy mapy
    int W;
    ///Liczba kolumn mapy
    int K;
    ///Zmienna przechowująca rozmiar generowanej wyspy
    int r;
    ///Tablica przychowująca mapę w czasie pracy programu
    komorka **m = nullptr;
    ///Obraz generowanej mapy
    QImage *image;
    ///Painter do rysowaia po obrazie mapy
    QPainter *paintOnImage;
    ///Punkt początkowy na oknie programu służący do poruszania mapą
    QPoint from_point;
    ///Punkt końcowy na oknie programu służący do poruszania mapą
    QPoint to_point;
    ///Współrzędne na obrazie mapy
    QPoint pozycja;
    ///Kontrolka określająca czy właśnie poruszam mapą
    bool mapMove;
    ///Rozmiar wyświetlanej mapy
    QSize s;
    ///Punkt na oknie programu gdzie ma się wyświetlać mapa
    QPoint p;

    void paintEvent(QPaintEvent*);

    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);


private slots:
    void on_pbGeneruj_clicked();

    void on_pbWczytaj_clicked();

    void on_pbZapiszObraz_clicked();

    void on_pbZapiszTxt_clicked();

    void on_pbUsun_clicked();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
