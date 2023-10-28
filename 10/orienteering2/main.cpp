/* COMP.CS.100 Projekti 3: Suunnistusta
 * Kasper Kivistö, kasper.kivisto@tuni.fi, 50302871
 *
 * Koodi kysyy enimmäiseksi tiedoston nimen, jossa suunnistuspisteet ovat.
 * Seuraavaksi, jos tiedoston avaaminen onnisutui, kysytään komentoa.
 * Komennot ovat seuraavat:
 * -map: printtaa kuvan kartasta, jossa pisteet ovat koordinaatistossa
 * -routes: printtaa kaikki tallennetut reitit.
 * -route "reitin_nimi": printtaa tietyn reitin pisteet järjestyksessä.
 * -points: printtaa kaikkien tallennettujen pisteiden nimet ja merkit.
 * -lenght "reitin_nimi": printtaa tietyn reitin koko pituuden.
 * -rise "pisteen_nimi": laskee suurimman yhtäjaksoisen nousun pisteen jälkeen
 * ja printtaa sen.
 *
 * Jos reittiä, pistettä tai komentoa ei löydy, niin koodi tulostaa
 * virheilmoituksen sen mukaan.
 *
 * Koodi lopetetaan komennolla "q" tai "quit".
 **/
#include "orienteeringmap.hh"
#include "parser.hh"
#include "cli.hh"
#include <iostream>


int main()
{
    std::shared_ptr<OrienteeringMap> routes(new OrienteeringMap);
    std::cout << "Input> ";
    std::string input;
    getline(std::cin, input);
    if( not read_input_from_file(input, routes) )
    {
        return EXIT_FAILURE;
    }

    Cli cli(routes);
    while( cli.exec_prompt() ){ }
    return EXIT_SUCCESS;
}


