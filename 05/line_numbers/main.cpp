#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string input_file = "";
    string output_file = "";

    cout << "Input file: ";
    getline(cin, input_file);

    cout << "Output file: ";
    getline(cin, output_file);

    ifstream input(input_file);


    if ( not input )
    {
        cout << "Error! The file " << input_file << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    else
    {
        ofstream output(output_file);

        string line = "";
        int num = 1;
        while ( getline(input, line) )
        {
            output << num << " " << line << endl;
            num += 1;
        }

        input.close();
        output.close();


    }

    return 0;
}
