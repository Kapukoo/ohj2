#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT( check_values() ));

    ui->lcdNumberMin->setAutoFillBackground(true);
    ui->lcdNumberMin->setPalette(Qt::blue);


    ui->lcdNumberSec->setPalette(Qt::red);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_closeButton_clicked()
{

    close();
}


void MainWindow::on_startButton_clicked()
{

    timer->start(1000);

}


void MainWindow::on_stopButton_clicked()
{
    timer->stop();
}


void MainWindow::on_resetButton_clicked()
{
    timer->stop();
    ui->lcdNumberSec->display(0);
    ui->lcdNumberMin->display(0);
}

void MainWindow::check_values()
{
    int seconds = ui->lcdNumberSec->intValue();
    int minutes = ui->lcdNumberMin->intValue();

    if ( seconds == 60 ){
        minutes += 1;
        seconds = 0;
    }

    seconds += 1;

    ui->lcdNumberSec->display(seconds);
    ui->lcdNumberMin->display(minutes);


}

