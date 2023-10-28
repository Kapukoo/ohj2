/* Hitori
 *
 * Kuvaus:
 *   Ohjelma toteuttaa Hitori-pelin. Pelissä on peliruudukko kooltaan
 * 5 x 5. Kukin ruutu sisältää jonkin numeroista 1-5. Vaaka- ja
 * pystyriveillä voi aluksi olla useita samoja numeroita, mutta
 * tarkoituksena on poistaa numeroita niin, että kullakin vaaka- ja
 * pystyrivillä on kutakin numeroa vain yksi tai ei yhtään. Kuitenkaan
 * vierekkäisten ruutujen numeroita ei saa poistaa, eikä mikään jäljelle
 * jäävä numero (ruutu) saa jäädä irralleen muista, eli sen ympäriltä
 * (yläpuolelta, alapuolelta, vasemmalta, oikealta) ei saa poistaa
 * kaikkia numeroita.
 *   Aluksi käyttäjältä kysytään, täytetäänkö peliruudukko satunnaisesti
 * arvottavilla luvuilla 1-5 vai käyttäjän valitsemilla 25 luvulla.
 * Ensimmäisessä vaihtoehdossa käyttäjältä kysytään satunnaisluku-
 * generaattorin siemenlukua ja jälkimmäisessä häntä pyydetään syöttämään
 * 25 lukua.
 *   Joka kierroksella käyttäjältä kysytään poistettavan numeron
 * koordinaatteja eli kahta lukua. Peli päättyy pelaajan voittoon,
 * jos peliruudukon kaikilla vaaka- ja pystyriveillä esiintyy kukin
 * numero 1-5 korkeintaan kerran. Peli päättyy pelaajan häviöön,
 * jos hän poistaa jo poistetun numeron viereisen numeron tai jos
 * jokin numero jää irralleen muista.
 *   Ohjelma tarkistaa annetut koordinaatit. Koordinaattien pitää olla
 * peliruudukon sisällä, ja niiden osoittaman ruudun pitää sisältää
 * numero, eli jo poistettua numeroa ei voi poistaa toiseen kertaan.
 *   Pelin päättyessä kerrotaan, voittiko vai hävisikö pelaaja.
 *
 * Ohjelman kirjoittaja ( Täytä omilla tiedoillasi )
 * Nimi: Kasper Kivistö
 * Opiskelijanumero: 50302871
 * Käyttäjätunnus: knkaki ( Git-repositorion hakemistonimi. )
 * E-Mail: kasper.kivisto@tuni.fi
 *
 * Ohjelman kirjoittaja ( Täytä omilla tiedoillasi )
 * Nimi: Elmeri Kivipato
 * Opiskelijanumero: 50320219
 * Käyttäjätunnus: vrelki ( Git-repositorion hakemistonimi. )
 * E-Mail: elmeri.kivipato@tuni.fi
 * Huomioita ohjelmasta ja sen toteutuksesta:
 *
 * */
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

const unsigned int BOARD_SIDE = 5;
const unsigned char EMPTY = ' ';

// Muuttaa annetun numeerisen merkkijonon vastaavaksi kokonaisluvuksi
// (kutsumalla stoi-funktiota).
// Jos annettu merkkijono ei ole numeerinen, palauttaa nollan.
//
// Converts the given numeric string to the corresponding integer
// (by calling stoi).
// If the given string is not numeric, returns zero.
unsigned int stoi_with_check( string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
        if (isdigit(str.at(i))) {
            if ( str.at(i) - 48 > 5 or str.at(i)-48 < 1) {

                is_numeric = false;
                break;
            }
        }
    }
    if(is_numeric)
    {
        //cout << stoi(str) << endl;
        return stoi(str);
    }
    else
    {
        return 0;
    }
}

// Tulostaa pelilaudan rivi- ja sarakenumeroineen.
//
// Prints the game board with row and column numbers.
void print(const std::vector < std::vector < int > >& gameboard)
{
    cout << "=================" << endl;
    cout << "|   | 1 2 3 4 5 |" << endl;
    cout << "-----------------" << endl;
    for(unsigned int i = 0; i < BOARD_SIDE; ++i)
    {
        cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < BOARD_SIDE; ++j)
        {
            if(gameboard.at(i).at(j) == 0)
            {
                cout << EMPTY << " ";
            }
            else
            {
                cout << gameboard.at(i).at(j) << " ";
            }
        }
        cout << "|" << endl;
    }
    cout << "=================" << endl;
}

// luodaan vektri joka sisältää rivit, jotka toimivat pelilautana.
std::vector < std::vector < int > > vector_vector(string& pelilauta)
{

    std::vector <int> rivi1;
    std::vector <int> rivi2;
    std::vector <int> rivi3;
    std::vector <int> rivi4;
    std::vector <int> rivi5;

    for ( unsigned int i = 0; i < pelilauta.length(); ++i) {

        if (i <= 4) {
            int str = pelilauta.at(i)-48;
            rivi1.push_back(str);

        }
        if ( 5 <= i and i <= 9) {
            int str = pelilauta.at(i)-48;
            rivi2.push_back(str);

        }
        if ( 10 <= i and i <= 14) {
            int str = pelilauta.at(i)-48;
            rivi3.push_back(str);

        }
        if ( 15 <= i and i <= 19) {
            int str = pelilauta.at(i)-48;
            rivi4.push_back(str);

        }
        if ( 20 <= i and i <= 24) {
            int str = pelilauta.at(i)-48;
            rivi5.push_back(str);
        }
    }
    std::vector < std::vector < int > > iso_vektori;
    iso_vektori.push_back(rivi1);
    iso_vektori.push_back(rivi2);
    iso_vektori.push_back(rivi3);
    iso_vektori.push_back(rivi4);
    iso_vektori.push_back(rivi5);

    return iso_vektori;
}

// poistetaan annettu koordinaatti sekä virhetarkastelu.
bool remove(std::vector < std::vector < int > >& iso_vektori, int x, int y) {
    // tarkistaa onko koordinaatti jo poistettu
    if (iso_vektori.at(x-1).at(y-1) == 0) {
        return false;
    }
    // poistaa kyseisen koordinaatin
    else {
        iso_vektori.at(x-1).at(y-1) = 0;
        return true;
    }
}

// tarkistetaan onko peli hävitty.
bool game_lost(std::vector < std::vector < int > >& iso_vektori) {

    // Tarkistaa onko vierekkäsisiä tyhjiä ruutuja
    for(unsigned int i = 0; i < BOARD_SIDE-1; ++i)
    {
        for(unsigned int j = 0; j < BOARD_SIDE-1; ++j)
        {
            if(iso_vektori.at(i).at(j) == 0 and iso_vektori.at(i+1).at(j)==0)
            {
                return true;
            } else if (iso_vektori.at(i).at(j) == 0 and iso_vektori.at(i).at(j+1)==0) {
                return true;
            }
        }

    // Tarkistaa vasemmanpuolimmaisimmman pystyrivin, että onko vierekkäsiä tyhjiä ruutuja
    } for (unsigned int x = 0; x < BOARD_SIDE-1; ++x) {

        if (iso_vektori.at(4).at(x)==0 and iso_vektori.at(4).at(x+1)==0) {
            return true;
        }

    // Tarkistaa onko alimmanlla rivillä vierekkäisiä tyhjiä ruutuja
    } for(unsigned int y = 0; y < BOARD_SIDE-1; ++y) {

        if (iso_vektori.at(y).at(4)==0 and iso_vektori.at(y+1).at(4)==0) {
            return true;
        }
    }

    // tarkistaa jääkö vasen yläkulma erikseen muista numeroista
    if (iso_vektori.at(1).at(0)==0 and iso_vektori.at(0).at(1)==0) {
        return true;
    }
    // tarkistaa jääkö oikea yläkulma erikseen muista numeroista
    if (iso_vektori.at(3).at(0)==0 and iso_vektori.at(4).at(1)==0) {
        return true;
    }
    // tarkistaa jääkö vasen alakulma erikseen muista numeroista
    if (iso_vektori.at(0).at(3)==0 and iso_vektori.at(1).at(4)==0) {
        return true;
    }
    // tarkistaa jääkö oikea alakulma erikseen muista numeroista
    if (iso_vektori.at(4).at(3)==0 and iso_vektori.at(3).at(4)==0) {
        return true;
    }

    // tarkistaa jääkö luku erilleen muista
    for(unsigned int i = 1; i < BOARD_SIDE-1; ++i) {
        for(unsigned int j = 1; j < BOARD_SIDE-1; ++j)
        {
            if(iso_vektori.at(i).at(j+1) == 0 and
                    iso_vektori.at(i+1).at(j)==0 and
                    iso_vektori.at(i-1).at(j)==0 and
                    iso_vektori.at(i).at(j-1)==0) {

                return true;
            }
        }
   }

    // tarkistaa ylimmän ja alimman rivin, että jääkö jokin luku erilleen muista
    for(unsigned int i = 1; i < BOARD_SIDE-1; ++i) {
        if(iso_vektori.at(i).at(1) == 0 and
                iso_vektori.at(i+1).at(0)==0 and
                iso_vektori.at(i-1).at(0)==0) {
            return true;

        } else if (iso_vektori.at(i).at(3) == 0 and
                   iso_vektori.at(i+1).at(4)==0 and
                   iso_vektori.at(i-1).at(4)==0) {
            return true;
        }

    // tarkistaa vasemmanpuolimmaisimman ja oikeanpuolimmaisimman rivin, että jääkö luku erilleen muista
    } for(unsigned int i = 1; i < BOARD_SIDE-1; ++i) {
        if(iso_vektori.at(1).at(i) == 0 and
           iso_vektori.at(0).at(i+1)==0 and
            iso_vektori.at(0).at(i-1)==0) {
            return true;

        } else if (iso_vektori.at(3).at(i) == 0 and
                   iso_vektori.at(4).at(i-1)==0 and
                   iso_vektori.at(4).at(i+1)==0) {
            return true;
        }
    }
return false;
}

// tarkistaa onko peli voitettu.
bool game_won(std::vector < std::vector < int > > iso_vektori) {

    // tarkistaa pystyrivit voitolle.
    for ( unsigned int indx = 0; indx <= 4; ++indx )
    {
        vector < int > testaus = {};
        for ( auto vektori : iso_vektori)
        {
            testaus.push_back(vektori.at(indx));
        }

        sort(testaus.begin(), testaus.end());
        int vertaus = -1;

        for (int luku : testaus)
        {
            if (luku == 0) {
                continue;
            }
            if ( vertaus < luku) {
                vertaus = luku;
            }
            else {
                return false;
            }
        }
    }

    // tarkistaa vaakarivit voitolle.
    for(unsigned int i = 0; i < BOARD_SIDE; ++i)
    {
        sort(iso_vektori.at(i).begin(), iso_vektori.at(i).end());
        int vertaus = -1;

        for (int luku : iso_vektori.at(i)) {

            if (luku == 0) {
                continue;
            }
            if ( vertaus < luku) {
                vertaus = luku;
            }
            else {
                return false;
            }
        }
    }
    return true;
}


int main()
{
    string input = "";

    while ( true) {
        cout << "Select start (R for random, I for input): ";
        string rane;
        getline(cin, rane);

        if ( rane == "i" or rane == "I")
        {
            cout << "Input: ";

            char new_integer;

            for(int i = 0; i < 25; ++i)
            {
                std::cin >> new_integer;
                input.push_back(new_integer);
            }
            break;
        }

        if ( rane == "r" or rane == "R" ) {
            cout << "Enter seed value: ";
            int seed;
            cin >> seed;

            default_random_engine gen(seed);
            uniform_int_distribution<int> distr(1, 5);

            for ( int i=0; i < 25; ++i) {
                input.push_back(distr(gen)+48);
            }
            break;
        }
    }

    std::vector < std::vector < int > > iso_vektori;
    iso_vektori = vector_vector(input);

    print(iso_vektori);


    while ( true ) {
        int x=0;
        int y=0;

        cout << "Enter removable element (x, y): ";
        string coord = "";

        for (int i=0; i < 2; ++i) {
            char komponentti;
            cin >> komponentti;

            if (komponentti == 'Q' or komponentti == 'q') {
                cout << "Quitting" << endl;
                return 0;
            }

            if ( !cin ) {
                continue;
            }

            else {
                coord.push_back(komponentti);
            }
        }

        int testi = stoi_with_check(coord);

        if (testi != 0) {
            x = coord.at(1)-48;
            y = coord.at(0)-48;
            bool poistettu;
            poistettu = remove(iso_vektori, x, y);

            if (poistettu == true) {
                print(iso_vektori);
            } else {
                cout << "Already removed" << endl;
                continue;
            }

        } else {
            cout << "Out of board" << endl;
        }

        bool game_over;
        game_over = game_lost(iso_vektori);

        if (game_over == true) {
            cout << "You lost" << endl;
            return 0;
        }

        bool game_win;
        game_win = game_won(iso_vektori);

        if ( game_win) {
            cout << "You won" << endl;
            return 0;
        }
    }
    return 0;
}
