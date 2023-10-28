/* Peli nimeltä 2048
 *
 * Kuvaus:
 *      Ohjelma toteuttaa peliä 2048, jonka pelilogiikka on annettu erikseen.
 *  Pelissä 4X4 ruudukkoon ilmestuu neliöitä, joita ohjataan wasd -näppäimillä.
 *  Kun kaksi saman arvoista neliöä törmää, ne yhdistyvät yhdeksi neliöksi,
 *  jonka arvo on yhdistyneiden neliöiden summa.
 *      Pelaajalle annetaan mahdollisuus muuttaa voitto- ja siemearvoa ennen
 *  pelin aloittamista. Lisäksi pelin yhteideydessä on sekuntikello, joka
 *  mittaa kulunutta aikaa. Kello ohjautuu itsestään riippuen pelin
 *  tapahtumista.
 *      Projektin idea on muodostaa pelille graafinen käyttöliittymä.
 *  Käyttöliittymä on rakennettu MainWindow -luokkaan.
 *
 *  Kasper Kivistö
 *  50302871
 *  kasper.kivisto@tuni.fi
 *
 */

#include "mainwindow.hh"
#include "gameboard.hh"
#include "numbertile.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
