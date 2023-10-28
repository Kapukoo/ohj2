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

void MainWindow::on_closePushButton_clicked()
{
    QApplication::quit();
}


void MainWindow::on_findPushButton_clicked()
{
    QString file_name = ui->fileLineEdit->text();
    //ui->textBrowser->setText(file_name);
    QString key = ui->keyLineEdit->text();

    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly)){
        ui->textBrowser->setText("File not found");
        return;
    }
    else{
        if ( key == "" ){
            ui->textBrowser->setText("File found");
            return;
        }

        QTextStream in(&file);

        QString line;
        do {
            line = in.readLine();

            if ( ui->matchCheckBox->isChecked() ){
                if (line.contains(key, Qt::CaseSensitive)) {
                    ui->textBrowser->setText("Word found");
                    break;
                }
            }
            else {
                if ( line.contains(key,Qt::CaseInsensitive)){
                    ui->textBrowser->setText("Word found");
                    break;
                }
            }

            ui->textBrowser->setText("Word not found");


        } while (!line.isNull());

    }
    file.close();
}



