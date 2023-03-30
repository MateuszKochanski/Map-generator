#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "generator.h"                          //generowanie mapy
#include "podstawa.h"                           //różne biblioteki i definicje struktur używanych w całym projekcie
#include "plik.h"
#include "budowa.h"

/**
* \file mainwindow.cpp
* \brief Plik źródłowy modułu Mainwindow
*/

/**
 * @brief Konstruktor klasy MainWindow
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Ustawienie kursora mapy na otwartą dłoń
    ui->mapWidget->setCursor(Qt::OpenHandCursor);

}

/**
 * @brief Destruktor klasy MainWindow
*/
MainWindow::~MainWindow()
{
    // Usunięcie mapy
    if(czyMamMape)
    {
        UsunTablice(W, m);
        delete image;
        delete paintOnImage;
    }
    delete ui;
}

/**
 * @brief Metoda rysująca na oknie programu
 *
 * Rysuje ona mapę, oraz odświerza wartości suwaków do ustawiana parametrów generatora
 */
void MainWindow::paintEvent(QPaintEvent *)
{
    // Utworzenie objektu klasy QPainter do rysowania po oknie programu
    QPainter painter(this);

    // Ustawienie odpowiednich wymiarów obszaru wyświetlania mapy w tym Widgetu "mapWidget"
    s.setWidth(this->width()-350);
    s.setHeight(this->height()-100);

    // Ustawienie współrzędnych obszaru wyświetlania mapy
    p.setX(300);
    p.setY(50);

    // Połączenie ww. danych w objekt klasy QRect
    QRect a(p,s);

    // Sprawdzam czy jest przechowywana jakaś mapa
    if(czyMamMape)
    {
        // Poprawiam rozmiar obszaru mapy, na wypadek gdy ten jest mniejszy od wcześniej ustawionego
        if(s.width()>K*32)
            s.setWidth(K*32);
        if(s.height()>W*32)
            s.setHeight(W*32);
        a.setSize(s);

        // Ustawiam odpowiednie współrzędne punktu na obrazie mapy (Uwzględniam odpowiednie przesunięcie jeżeli takowe istnieje)
        pozycja.setX(pozycja.x()-(to_point.x()-from_point.x()));
        pozycja.setY(pozycja.y()-(to_point.y()-from_point.y()));

        // Zabezpieczenie przeciw przekroczeniu rozmiaru obrazu
        if(pozycja.x()<0)
            pozycja.setX(0);
        else if(pozycja.x()>32*K-s.width())
            pozycja.setX(32*K-s.width());
        if(pozycja.y()<0)
            pozycja.setY(0);
        else if(pozycja.y()>32*W-s.height())
            pozycja.setY(32*W-s.height());

        // objekt klasy QRect przechowujący współrzędne, oraz wymiary wyświetlanej części obrazu mapy
        QRect b(pozycja,s);

        // Rysowanie mapy
        painter.drawImage(a, *image, b);
    }
    // Ustawienie wymiarów Widgetu mapWidget
    ui->mapWidget->setGeometry(a);
    //Rysowanie czarnego prostokąta określającego obszar mapy na oknie
    painter.drawRect(a);
    //Napisy przy parametrach
    QString s = QString::number(ui->hsSzerokosc->value());
    QString wys = QString::number(ui->hsWysokosc->value());
    QString wyp = QString::number(ui->hsWypelnienie->value());
    QString z = QString::number(ui->hsLiczbaZiaren->value());

    ui->lSzerokosc->setText("SZEROKOSC: "+s);
    ui->lWysokosc->setText("WYSOKOSC: "+wys);
    ui->lWypelnienie->setText("WYPELNIENIE: "+wyp+"%");
    ui->lZiarna->setText("LICZBA ZIAREN: "+z);

    painter.end();

}

/**
 * @brief Metoda reakcji na wciśnięcie przycisku myszy
 *
 * Jeśli myszka wskazuje na obszar mapy, następuje zmiana kursora, a mapą wtedy można poruszać
 */
void MainWindow::mousePressEvent(QMouseEvent* event)
{

    if(event->buttons() & Qt::LeftButton)                       //Gdy wcisnę lewy przycisk myszy
    {

        QPoint h = this->mapFrom(this,event->pos());            //Określam pozycję kursora


        if(h.x()<p.x()+s.width() && h.x()>p.x() && h.y() < p.y() + s.height() && h.y()>p.y())//Sprawdzam czy jest na mapie
        {

            from_point = h;                                     //Punkt początkowy = pozycja kursora

            mapMove = 1;                                        //Zmienna określająca czy w tym momencie poruszam mapą

            ui->mapWidget->setCursor(Qt::ClosedHandCursor);     //Zmiana kursora mapy na zamkniętą dłoń
        }

        else                                                    //W przeciwnym wypadku nie poruszam mapy
            mapMove = 0;

    }
}

/**
 * @brief Metoda reakcji na poruszanie myszką
 *
 * Jeśli myszka podczas wciśnięcia wskazywała na obszar mapy, jest możliwe poruszanie mapą
 */
void MainWindow::mouseMoveEvent(QMouseEvent* event)
{

    if(event->buttons() & Qt::LeftButton)                       //Gdy ruszam myszą...
    {  
        if(mapMove==1)                                          //...Gdy kontrolka wskazuje że poruszam mapą
        {           
            to_point = this->mapFrom(this,event->pos());        //Ustawiam wartość końcową przesunięcia

            repaint();                                          //Rysuję mapę przesuniętą o różnice to_point - from_point

            from_point = to_point;                              //początek przesunięcia = koniec przesunięcia
        }

    }
}

/**
 * @brief Metoda reakcji na zwolnienie przycisku myszy
 */
void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{

    if(!(event->buttons() & Qt::LeftButton))                    //Gdy zwolnię lewy przycisk myszy
    {       
        mapMove = 0;                                            //Ustawiam kontrolkę na 0

        ui->mapWidget->setCursor(Qt::OpenHandCursor);           //Zmiana kursora mapy na otwartą dłoń
    }
}

/**
 * @brief Metoda reakcji na wciśnięcie przycisku "Generuj mapę"
 *
 * Metoda ta usuwa mapę jeśli jakaś jest w pamięci, pobiera parametry nowo generowanej mapy z suwaków z panelu urzytkownika, a następnie generuje nową mapę na ich podstawie
 */
void MainWindow::on_pbGeneruj_clicked()
{

    if(czyMamMape)                                              //Usuwanie poprzedniej mapy
    {
        UsunTablice(W, m);
        delete image;
        delete paintOnImage;
        czyMamMape = 0;
    }
    //-----------------------------WYMIARY GENEROWANEJ MAPY-------------------------------
    W = ui->hsWysokosc->value();
    K = ui->hsSzerokosc->value();
    //--------------------WYPEŁNIENIE MAPY LĄDEM W % (od 0 do 100)------------------------
    int wypelnienie = ui->hsWypelnienie->value();
    //---------------------------LICZBA ZIAREN ROZROSTU MAPY------------------------------
    int liczbaZiaren = ui->hsLiczbaZiaren->value();

    ui->pbGeneruj->setEnabled(0);                               //Ustawienie aktywności przycisków
    ui->pbWczytaj->setEnabled(0);    

    repaint();                                                  //Odświerzenie

    m = PrzygotujTablice(W, K);                                 //Utworzenie tablicy o danych wymiarach

    generujMape(W, K, m, wypelnienie, liczbaZiaren);            //GENEROWANIE MAPY

    image = new QImage(32*K, 32*W, QImage::Format_ARGB32);      //Tworzenie obiektu klasy QImage do przechowywania obrazu mapy

    paintOnImage = new QPainter;                                //Tworzenie obiekt klasy QPainter do rysowania po obrazie

    paintOnImage->begin(image);                                 //Podpięcie grafiki pod obiekt klasy QPainter

    from_point.setX(0);                                         //Zerowanie zmiennych służących do poruszania się po mapie
    from_point.setY(0);
    to_point.setX(0);
    to_point.setY(0);
    mapMove = 0;

    pozycja.setX(0);                                            //Zerowanie współrzędnych punktu na obrazie mapy
    pozycja.setY(0);    

    BudowaMapy(W, K, m, paintOnImage);                          //Budowa obrazu mapy

    paintOnImage->end();                                        //Odpięcie grafiki od obiektu klasy QPainter

    czyMamMape = 1;                                             //Zmienna określająca czy istnieje tablica zawierająca mapę

    ui->pbGeneruj->setEnabled(1);                               //Ustawienie aktywności przycisków
    ui->pbWczytaj->setEnabled(1);
    ui->pbZapiszTxt->setEnabled(1);
    ui->pbZapiszObraz->setEnabled(1);
    ui->pbUsun->setEnabled(1);


    repaint();                                                  //Rysowanie mapy
}

/**
 * @brief Metoda reakcji na wciśnięcie przycisku "Wczytaj mapę"
 */
void MainWindow::on_pbWczytaj_clicked()
{

    if(Wczytaj(this, m, W, K, czyMamMape))                      //Jeśli wybrano odpowiedni plik funkcja Wczytaj() wczytuje mapę z pliku do tablicy 'm' i zwraca '1'
    {

        ui->pbGeneruj->setEnabled(0);                           //Ustawienie aktywności przycisków
        ui->pbWczytaj->setEnabled(0);

        repaint();                                              //Odświerzenie

        if(czyMamMape)                                          //Usuwanie poprzedniego obrazu mapy
        {
            delete image;
            delete paintOnImage;
        }

        image = new QImage(32*K, 32*W, QImage::Format_ARGB32);  //Tworzenie obiektu klasy QImage do przechowywania obrazu mapy

        paintOnImage = new QPainter;                            //Tworzenie obiekt klasy QPainter do rysowania po obrazie
        paintOnImage->begin(image);                             //Podpięcie grafiki pod obiekt klasy QPainter

        from_point.setX(0);                                     //Zerowanie zmiennych służących do poruszania się po mapie
        from_point.setY(0);
        to_point.setX(0);
        to_point.setY(0);
        mapMove = 0;

        pozycja.setY(0);                                        //Zerowanie współrzędnych punktu na obrazie mapy

        BudowaMapy(W, K, m, paintOnImage);                      //Budowa obrazu mapy

        paintOnImage->end();                                    //Odpięcie grafiki od obiektu klasy QPainter

        czyMamMape = 1;                                         //Zmienna określająca czy istnieje tablica zawierająca mapę

        ui->pbGeneruj->setEnabled(1);                           //Ustawienie aktywności przycisków
        ui->pbWczytaj->setEnabled(1);
        ui->pbZapiszTxt->setEnabled(1);
        ui->pbZapiszObraz->setEnabled(1);
        ui->pbUsun->setEnabled(1);

        repaint();                                              //Rysowanie mapy
    }
}

/**
 * @brief Metoda reakcji na wciśnięcie przycisku "Usuń mapę"
 */
void MainWindow::on_pbUsun_clicked()
{ 
    czyMamMape = 0;                                             //Zmienna określająca czy istnieje tablica zawierająca mapę

    ui->pbZapiszTxt->setEnabled(0);                             //Ustawienie aktywności przycisków
    ui->pbZapiszObraz->setEnabled(0);
    ui->pbUsun->setEnabled(0);   

    UsunTablice(W, m);                                          //Usuwanie mapy
    delete image;
    delete paintOnImage;    

    repaint();                                                  //Odświerzenie obrazu
}
/**
 * @brief Metoda reakcji na wciśnięcie przycisku "Zapisz obraz mapy"
 */
void MainWindow::on_pbZapiszObraz_clicked()
{
    zapiszObraz(this, image);                                   //Funkcja zapisu obrazu
}
/**
 * @brief Metoda reakcji na wciśnięcie przycisku "Zapisz do pliku .txt"
 */
void MainWindow::on_pbZapiszTxt_clicked()
{    
    zapiszDoPlikuTxt(W,K,this,m);                               //Funkcja zapisu mapy w pliku .txt
}
