#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <sstream>

using namespace std;

int main()
{
    map<string, pair<int, string> > words;



    string input_file = "";
    cout << "Input file: ";
    getline(cin, input_file);

    ifstream input(input_file);

    if ( not input ) {
        cout << "Error! The file " << input_file << " cannot be opened." << endl;
        return EXIT_FAILURE;

    } else {

        int num = 0;
        string line = "";

        while ( getline(input, line) ) {

            num += 1;
            string word = "";
            istringstream iss(line);

            while ( getline(iss, word, ' ') ) {

                pair<int, string> count_rows;
                string snum = to_string(num);

                if ( words.find(word) != words.end() ) {
                    // löytyy

                    if ( words.at(word).second.find(snum) == string::npos ) {

                        words.at(word).first += 1;
                        words.at(word).second.append(", ");
                        words.at(word).second.append(snum);
                    }

                } else {
                    // ei löydy

                    count_rows.first = 1;
                    count_rows.second = snum;

                    words.insert( {word, count_rows} );

                }
            }
        }

        input.close();

        for ( pair<string, pair<int, string> > m : words) {
            cout << m.first
                 << " "
                 << m.second.first
                 << ": "
                 << m.second.second
                 << endl;
        }
    }
    return 0;
}
