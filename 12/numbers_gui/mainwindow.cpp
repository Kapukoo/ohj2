/*
*  Kasper Kivistö
*  50302871
*  kasper.kivisto@tuni.fi
*/
#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QKeyEvent>

const Coords DEFAULT_DIR = {0, 0};
const Coords LEFT = {0, -1};
const Coords UP = {-1, 0};
const Coords RIGHT = {0, 1};
const Coords DOWN = {1, 0};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // pelialue
    scene = new QGraphicsScene(this);
    ui->graphicsView->setGeometry(150, 150, 500, 500);
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0, 0, 498, 498);

    // ajastin
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT( check_time() ));

    // GUI tyyli asettelua
    QString button_style = "background-color: white;"
                           "border-style: outset;"
                           "border-width: 2px;"
                           "border-radius: 6px;"
                           "border-color: black;"
                           "font: bold 12px;"
                           "padding: 1px;";

    QString spinbox_style = "background-color: white;"
                           "border-style: outset;"
                           "border-width: 2px;"
                           "border-color: black;"
                           "font: bold 12px;"
                           "padding-right: 10px;";

    this->setStyleSheet("background-color: rgb(0, 176, 161)");
    ui->pushbutton_start->setStyleSheet(button_style);
    ui->pushbutton_restart->setStyleSheet(button_style);
    ui->pushbutton_quit->setStyleSheet(button_style);
    ui->pushbutton_stop->setStyleSheet(button_style);
    ui->pushbutton_continue->setStyleSheet(button_style);
    ui->pushbutton_help->setStyleSheet(button_style);
    ui->lcdnumber_time->setStyleSheet(button_style);
    ui->spinbox_seedvalue->setStyleSheet(spinbox_style);
    ui->spinbox_winvalue->setStyleSheet(spinbox_style);
    scene->setBackgroundBrush( Qt::white );

    // näppäinten asettelua
    ui->pushbutton_restart->setEnabled(false);
    ui->pushbutton_continue->setEnabled(false);
    ui->pushbutton_stop->setEnabled(false);
    ui->label_gamepaused->setVisible(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::check_time()
{
    int seconds = ui->lcdnumber_time->intValue();
    seconds += 1;
    ui->lcdnumber_time->display(seconds);
    return;
}

void MainWindow::add_tile(int x, int y, QBrush color, QString value, QFont f)
{
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);

    scene->addRect(x*125, y*125, 125, 125, blackPen, color);
    QGraphicsTextItem *text = scene->addText(value);

    // Riippuen arvosta. keskitetään arvo.
    int Value = value.toInt();
    if ( Value < 10){
        text->setPos(x*125+45, y*125+30);
    }
    else if ( Value < 100 ){
        text->setPos(x*125+30, y*125+30);
    }
    else if ( Value < 1000 ){
        text->setPos(x*125+10, y*125+30);
    }

    text->setFont(f);

    return;
}

void MainWindow::delay(int millisecondsWait)
{
    key_commands = false;
    QEventLoop loop;
    QTimer timer;
    timer.connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    timer.start(millisecondsWait);
    loop.exec();
    key_commands = true;
}

void MainWindow::board_update(bool add_new)
{
    // tyhjenetään koko kenttä
    scene->clear();
    ui->graphicsView->items().clear();

    if ( add_new ){
        // päivitetään ensin jo olevat ruudut
        board_update(false);
        // odotetaan hetki ja päivitetään kaikki ruudut
        delay(80);
        board.new_value(false);
    }

    QFont* f= new QFont;
    f->setPointSize(35);
    QBrush* brush = new QBrush;

    for( auto y = 0; y < SIZE; ++y )
    {
        for( auto x = 0; x < SIZE; ++x )
        {
            QString value = QString::number(board.get_item({y, x})->return_value());
            int i = value.toInt();

            // värit määriteltynä
            if ( i == 2 ){
                *brush = QColor(200, 200, 200);
            }
            if ( i == 4 ){
                *brush = QColor(150, 150, 150);
            }
            if ( i == 8 ){
                *brush = QColor(110, 150, 110);
            }
            if ( i == 16 ){
                *brush = QColor(120, 200, 120);
            }
            if ( i == 32 ){
                *brush = QColor(100, 150, 200);
            }
            if ( i == 64 ){
                *brush = QColor(100, 120, 250);
            }
            if ( i == 128 ){
                *brush = QColor(200, 100, 200);
            }
            if ( i == 256 ){
                *brush = QColor(200, 50, 200);
            }
            if ( i == 512 ){
                *brush = QColor(200, 0, 200);
            }
            if ( i == 1024 ){
                *brush = QColor(200, 100, 100);
            }
            if ( i == 2048 ){
                *brush = QColor(200, 100, 0);
            }
            if ( i > 2048 ){
                *brush = QColor(200, 200, 0);
            }
            // piirretään värilliset ruudut
            if ( i > 0){
                add_tile(x, y, *brush, value, *f);
            }
            // Muodostetaan ruudukko piirätmällä valkoisia neliöitä
            else if ( i == 0){
                add_tile(x, y, Qt::white, "", *f);
            }
        }
    }
    delete brush;
    delete f;
    return;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    Coords dir = DEFAULT_DIR;
    if ( key_commands ){

        if (event->key() == Qt::Key_W) {
            dir = UP;
        }
        if (event->key() == Qt::Key_A) {
            dir = LEFT;
        }
        if (event->key() == Qt::Key_S) {
            dir = DOWN;
        }
        if (event->key() == Qt::Key_D) {
            dir = RIGHT;
        }

        QFont* f= new QFont;
        f->setPointSize(40);

        // voitto
        if ( board.move(dir, win_value) ){
            key_commands = false;
            ui->pushbutton_continue->setEnabled(false);
            ui->pushbutton_stop->setEnabled(false);
            timer->stop();
            board_update();

            this->setStyleSheet("background-color:green");

            QGraphicsTextItem *text = scene->addText("Voitit pelin!");
            text->setPos(100, 180);
            text->setFont(*f);
            delete f;

            return;
        }

        // häviö
        else if( board.is_full() ){
            key_commands = false;
            ui->pushbutton_continue->setEnabled(false);
            ui->pushbutton_stop->setEnabled(false);
            timer->stop();
            board_update();

            this->setStyleSheet("background-color:red");

            QGraphicsTextItem *text = scene->addText("Hävisit pelin!");
            text->setPos(100, 180);
            text->setFont(*f);
            delete f;

            return;
        }
        board_update(true);

    }
    return;
}

void MainWindow::on_pushbutton_start_clicked()
{
    // napit oikein ja lukujen haku
    ui->pushbutton_restart->setEnabled(true);
    ui->pushbutton_start->setEnabled(false);
    ui->pushbutton_stop->setEnabled(true);
    ui->pushbutton_continue->setEnabled(false);
    key_commands = true;
    win_value = ui->spinbox_winvalue->value();
    seed_value = ui->spinbox_seedvalue->value();

    // ajastimen käynnistys
    timer->start(1000);

    // lasketaan annetun arvon lähin 2 potenssi
    // alaspäin pyöristäen
    if ( win_value != 0 ){
        int test_value = log2(win_value);
        win_value = pow(2, test_value);
    }
    if ( win_value == 0 ){
        win_value = DEFAULT_GOAL;
    }
    if ( seed_value == 0){
        seed_value = 5689;
    }

    // näytetään arvot boksissa
    ui->spinbox_winvalue->setValue(win_value);
    ui->spinbox_seedvalue->setValue(seed_value);

    // pelilogiikan alotus tapauksesta riippuen
    if ( !restart ){
        board.init_empty();
        board.fill(seed_value);
    }
    else if ( restart ){
        board.fill(seed_value, true);
    }

    board_update();
    return;
}

void MainWindow::on_pushbutton_restart_clicked()
{

    this->setStyleSheet("background-color: rgb(0, 176, 161)");
    timer->stop();
    ui->lcdnumber_time->display(0);

    ui->pushbutton_restart->setEnabled(false);
    ui->pushbutton_start->setEnabled(true);
    ui->pushbutton_continue->setEnabled(false);
    ui->pushbutton_stop->setEnabled(false);

    key_commands = false;
    scene->clear();
    ui->graphicsView->items().clear();
    ui->label_gamepaused->setVisible(false);
    restart = true;

}

void MainWindow::on_pushbutton_help_clicked()
{
    QMessageBox help;
    help.setText("2048\n"
                 "\n"
                 "-Pelin ideana on yhdistellä samanarvoisia laatikoita"
                 "kunnes saavutetaan voittoluku.\n"
                 "-Voit liikuttaa latikoita wasd -näppäimillä.\n"
                 "-Aloita peli painamalla start -näppäintä\n"
                 "-Voit aloittaa pelin alusta milloin vain painamalla restart -näppäintä.\n"
                 "-Pelin voi sulkea milloin vain painamalla quit -näppäintä.");
    help.exec();
}

void MainWindow::on_pushbutton_stop_clicked()
{
    timer->stop();
    key_commands = false;
    ui->pushbutton_stop->setEnabled(false);
    ui->pushbutton_continue->setEnabled(true);
    ui->label_gamepaused->setVisible(true);
}

void MainWindow::on_pushbutton_continue_clicked()
{
    key_commands = true;
    timer->start(1000);
    ui->pushbutton_stop->setEnabled(true);
    ui->pushbutton_continue->setEnabled(false);
    ui->label_gamepaused->setVisible(false);
}

