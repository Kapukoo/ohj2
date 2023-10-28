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


void MainWindow::on_countPushButton_clicked()
{
    unsigned int N = ui->spinBoxN->text().toInt();;
    unsigned int G = ui->spinBoxG->text().toInt();;
    unsigned int P = ui->spinBoxP->text().toInt();;
    unsigned int E = ui->spinBoxE->text().toInt();;

    int grade = count_final_grade(N, G, P, E);

    QString end_text = "Total grade: ";
    end_text.push_back(QString::number(grade));

    ui->textBrowser->setText(end_text);
}

