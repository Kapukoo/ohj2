#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_closeButton_clicked()
{
    close();
}


void MainWindow::on_countButton_clicked()
{
    double heightDouble = 0;
    double weightDouble = 0;

    QString weight = ui->weightLineEdit->text();
    QString height = ui->heightLineEdit->text();

    if ( weight.toDouble() ){
        weightDouble = weight.toDouble();
    }
    if ( height.toDouble() ){
        heightDouble = height.toDouble();
    }

    if ( heightDouble == 0 ){
        ui->resultLabel->setText("Cannot count");
        return;
    }

    heightDouble /= 100;
    long double BMI = weightDouble / heightDouble / heightDouble;

    QString result = QString::number(BMI,'B',4);
    ui->resultLabel->setText(result);

    if ( BMI < 18.5 ){
        ui->infoTextBrowser->setText("You are underweight.");
    }
    else if ( BMI > 25.0 ){
        ui->infoTextBrowser->setText("You are overweight.");
    }
    else {
        ui->infoTextBrowser->setText("Your weight is normal.");
    }

}

