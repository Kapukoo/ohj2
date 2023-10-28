#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

int main()
{
    string input_file = "";
    string line = "";
    map<string, int> score;


    cout << "Input file: ";
    getline(cin, input_file);

    ifstream input(input_file);


    if ( not input )
    {
        cout << "Error! The file " << input_file << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    else
    {
        while ( getline(input, line) )
        {

            string name;
            string numero;
            int num;
            unsigned int y;

            for (unsigned int i = 0; i < line.size(); ++i){

                if (line.at(i) == ':'){
                    y = i+1;

                    for (unsigned int j = y; j < line.size(); ++j) {
                        numero.push_back(line.at(j));
                    }

                    break;
                }
                name.push_back(line.at(i));
            }

            num = stoi(numero);

            if ( score.find(name) == score.end())
            {
                score.insert( {name, num} );
            }
            else
            {
                score.at(name) += num;
            }
        }
        input.close();

        cout << "Final scores:" << endl;

        for (auto mm : score)
        {
            cout << mm.first << ": " << mm.second << endl;
        }
    }
    return 0;
}
