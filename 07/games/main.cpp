/*  COMP.CS.100 Project 2: GAME STATISTICS
 * ===============================
 * EXAMPLE SOLUTION
 * ===============================
 *
 *  Acts as a game statistics with n commands:
 * ALL_GAMES - Prints all known game names
 * GAME <game name> - Prints all players playing the given game
 * ALL_PLAYERS - Prints all known player names
 * PLAYER <player name> - Prints all games the given player plays
 * ADD_GAME <game name> - Adds a new game
 * ADD_PLAYER <game name> <player name> <score> - Adds a new player with the
 * given score for the given game, or updates the player's score if the player
 * already playes the game
 * REMOVE_PLAYER <player name> - Removes the player from all games
 *
 *  The data file's lines should be in format game_name;player_name;score
 * Otherwise the program execution terminates instantly (but still gracefully).
 *
 * Kasper Kivistö, kasper.kivisto@tuni.fi, 50302871
 * Elmeri Kivipato, elmeri.kivipato@tuni.fi, 50320219
 *
 * */
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <set>

using namespace std;
// Casual split func, if delim char is between "'s, ignores it.
std::vector<std::string> split( const std::string& str, char delim = ';' )
{
    std::vector<std::string> result = {""};
    bool inside_quatation = false;
    for ( auto current_char : str )
    {
        if ( current_char == '"' )
        {
            inside_quatation = not inside_quatation;
        }
        else if ( current_char == delim and not inside_quatation )
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    if ( result.back() == "" )
    {
        result.pop_back();
    }
    return result;
}

// Tulostaa kaikki pelit aakkosjärjestyksessä.
void ALL_GAMES(map< string, map<string, int> > games) {

    cout << "All games in alphabetical order:" << endl;
    for (auto game_name : games) {
        cout << game_name.first << endl;
    }
}

// Tulostaa halutun pelin pelaajat ja heidän pisteet.
void GAME(vector<string> command, map< string, map<string, int> > games) {

    map<int, string> players_by_points;

    if ( command.size() < 2) {
        cout << "Error: Invalid input." << endl;
        return;
    }
    if ( games.find(command.at(1)) == games.end() ) {
        // peliä ei löydy.
        cout << "Error: Game could not be found." << endl;
        return;
    }
    else {
        for ( auto p : games[command.at(1)] ) {
            if (players_by_points.find(p.second) != players_by_points.end() ) {

                // peli löytyy. Lisätään pelaaja.
                string k = ", " + p.first;
                players_by_points[p.second].append(k);

            } else {
                // peliä ei löydy, joten se lisätään.
                players_by_points[p.second].append(p.first);
            }
        }
    }

    cout << "Game "
         << command.at(1)
         << " has these scores and players, "
            "listed in ascending order:" << endl;

    for (auto k : players_by_points) {
        cout << k.first << " : " << k.second << endl;
    }
}

// Tulostaa kaikki pelaajat aakkosjärjestyksessä.
void ALL_PLAYERS(map< string, map<string, int> > games) {

    set<string> players;

    for ( auto k : games) {
        for ( auto l : k.second) {
            players.insert(l.first);
        }
    }

    cout << "All players in alphabetical order:" << endl;

    for ( auto e : players) {
        cout << e << endl;
    }
}

// Tulostaa kaikki pelit, joita tietty plejaaja pelaa.
void PLAYER(vector<string> command, map< string, map<string, int> > games) {
    set<string> ingames;

    for (auto k : games) {
        for ( auto l : k.second) {
            if (command.at(1) == l.first) {
                ingames.insert(k.first);
            }
        }
    }

    if (ingames.size() == 0) {
        cout << "Error: Player could not be found." << endl;
        return;
    }

    cout << "Player " << command.at(1) << " playes the following games:" << endl;

    for (auto i : ingames) {
        cout << i << endl;
    }
}

// Lisää uuden pelin.
map< string, map<string, int> > ADD_GAME(vector<string> command,
                                         map< string, map<string, int> > games) {

    if ( command.size() < 2) {
        cout << "Error: Invalid input." << endl;
        return games;
    }

    if ( games.find(command.at(1)) != games.end() ) {
        // peli löytyy
        cout << "Error: Already exists." << endl;
    }

    if ( games.find(command.at(1)) == games.end() ) {
        // peliä ei löydy
        games[command.at(1)];
        cout << "Game was added." << endl;
    }

    return games;
}

// Lisää uuden pelaajan tai päivittää olemassa olevan pelaajan pisteet.
map< string, map<string, int> > ADD_PLAYER(vector<string> command,
                                         map< string, map<string, int> > games) {

    if (command.size() != 4) {
        // väärä inputti
        cout << "Error: Invalid input." << endl;
        return games;
    }
    else if (games.find(command.at(1)) == games.end() ) {
        // peliä ei ole
        cout << "Error: Game could not be found." << endl;

    } else {
        // Pelaajan pisteet uudistetaan tai muutetaan.
    games[command.at(1)][command.at(2)] = stoi(command.at(3));
    cout << "Player was added." << endl;

    }

    return games;
}

// Poistaa halutun pelaajan.
map< string, map<string, int> > REMOVE(vector<string> command,
                                         map< string, map<string, int> > games) {

    int remove_counter = 0;

    if ( command.size() < 2) {
        cout << "Error: Invalid input." << endl;
        return games;
    }

    for ( auto g : games) {
        for ( auto p : g.second ) {
            if ( p.first == command.at(1) ) {
                games[g.first].erase(p.first);
                remove_counter += 1;
            }
        }
    }
    if ( remove_counter == 0) {
        cout << "Error: Player could not be found." << endl;
    } else {
        cout << "Player was removed from all games." << endl;
    }
    return games;
}

int main()
{

   map< string, map<string, int> > games;

    string file_name = "";
    cout << "Give a name for input file: ";
    getline(cin, file_name);

    ifstream file(file_name);
    if (not file) {
        cout << "Error: File could not be read." << endl;
        return EXIT_FAILURE;

    } else {
        string row;

        while ( getline(file, row) ) {
            vector<string> split_row = split(row);

            if (split_row.size() != 3 ) {
                cout << "Error: Invalid format in file." << endl;
                return EXIT_FAILURE;
            }
            string game_name = split_row.at(0);
            string player_name = split_row.at(1);
            string points_string = split_row.at(2);
            int points = stoi(points_string);

            if ( games.find(game_name) == games.end() ) {
                // peliä ei löydy. Lisätään se.
                games[game_name][player_name] = points;
            }
            if ( games.find(game_name) != games.end() ) {
                // peli löytyy.
                games[game_name].insert( {player_name, points} );
            }
        }
       file.close();
    }

    while (true) {

        cout << "games> ";
        string command_string;
        getline (cin, command_string);

        vector<string> command = split(command_string, ' ');

        if (command.at(0) == "quit") {
            return EXIT_SUCCESS;
        }

        if (command.at(0) == "all_games") {
            ALL_GAMES(games);
        }

        if (command.at(0) == "game") {
            GAME(command, games);
        }

        if (command.at(0) == "all_players") {
            ALL_PLAYERS(games);
        }

        if (command.at(0) == "player") {
            PLAYER(command, games);
        }

        if (command.at(0) == "add_game") {
            games = ADD_GAME(command, games);
        }

        if (command.at(0) == "remove") {
            games = REMOVE(command, games);
        }

        if (command.at(0) == "add_player") {
            games = ADD_PLAYER(command, games);
        }

        if ( command.at(0) != "quit"
             and
             command.at(0) != "all_games"
             and
             command.at(0) != "game"
             and
             command.at(0) != "all_players"
             and
             command.at(0) != "player"
             and
             command.at(0) != "add_game"
             and
             command.at(0) != "remove"
             and
             command.at(0) != "add_player") {

            cout << "Error: Invalid input." << endl;
        }
    }
    return EXIT_SUCCESS;
}
