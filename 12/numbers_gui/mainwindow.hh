/*
*  Kasper Kivistö
*  50302871
*  kasper.kivisto@tuni.fi
*
*  Projektin toteutettu GUI.
*/
#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "gameboard.hh"
#include "numbertile.hh"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QMessageBox>
#include <QTimer>
#include <QEventLoop>
#include <cmath>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor
    MainWindow(QWidget *parent = nullptr);

    // Destructor
    ~MainWindow();

    // Näppäin painallukset käsittelevä funktio
    void keyPressEvent(QKeyEvent* event) override;

    // Tyhjentää pelialueen ja käy jokaisen ruudun uudelleen läpi ja kutsuu
    // board_update funktiota piirtämään jokaisen ruudun.
    // Myös lisää uuden 2, jos tarve.
    void board_update(bool add_new = false);

    // Piirtää pelialueen ruudut
    void add_tile(int x, int y, QBrush color, QString value, QFont f);

    // hidastus funktio, jolla uuden ruudun lisäämisen voidaan porrastaa
    inline void delay(int millisecondsWait);



private slots:
    // pelin aloitus -> ensimmäiset ruudut ja aika alkaa
    void on_pushbutton_start_clicked();

    // tyhjennetään pelilauta ja nollataan kello
    void on_pushbutton_restart_clicked();

    // pelin säännöt ja muu apu
    void on_pushbutton_help_clicked();

    // ajan tarkistus sekuntikelloa varten
    void check_time();

    // Pysäyttää pelin ja kellon
    void on_pushbutton_stop_clicked();

    // Jatkaa peliä ja kelloa
    void on_pushbutton_continue_clicked();

private:
    Ui::MainWindow *ui;

    QGraphicsScene* scene;
    QGraphicsRectItem* square;
    GameBoard board;
    QTimer* timer;


    int win_value = 0;
    int seed_value = 0;
    bool restart = false;
    bool key_commands = false;

};
#endif // MAINWINDOW_HH
