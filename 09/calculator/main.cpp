#include "calculations.hh"
#include <iostream>
#include <iomanip>
#include <sstream>  // for implementing function string_to_double
#include <string>
#include <vector>

using namespace std;

const string GREETING_AT_END = "Thanks and see you later!";

// Utility function to sections a string at delimiters
vector< string > split(const string& s,
                       const char delimiter,
                       bool ignore_empty = false);

// Function string_to_double changes a string comprising a real number
// into a float type value for calculations.
// It returns true, if parameter s comprised a real.
// It returns false, if s was not a valid real number.
// The converted float will be assigned into reference parameter result.
// The implementation of the function uses stringstream for the sake of example.
bool string_to_double(const string& s, double& result);


// TODO: Explore the following data structures!
struct Command {
    string str;
    vector<string>::size_type parameter_number;
    bool is_exit;
    double(*action)(double, double);
};

const vector<Command> COMMANDS = {
    {"+", 2, false, addition},
    {"-", 2, false, subtraction},
    {"*", 2, false, multiplication},
    {"/", 2, false, division},
    {"PLUS", 2, false, addition},
    {"MINUS", 2, false, subtraction},
    {"TIMES", 2, false, multiplication},
    {"DIVIDED", 2, false, division},
    {"ADDITION", 2, false, addition},
    {"SUBTRACTION", 2, false, subtraction},
    {"MULTIPLICATION", 2, false, multiplication},
    {"DIVISION", 2, false, division},
    {"SUM", 2, false, addition},
    {"DIFFERENCE", 2, false, subtraction},
    {"PRODUCT", 2, false, multiplication},
    {"QUOTIENT", 2, false, division},
    {"ADD", 2, false, addition},
    {"INCREASE", 2, false, addition},
    {"SUBTRACT", 2, false, subtraction},
    {"DECREASE", 2, false, subtraction},
    {"MULTIPLY", 2, false, multiplication},
    {"DIVIDE", 2, false, division},
    {"STOP", 0, true, nullptr},
    {"QUIT", 0, true, nullptr},
    {"EXIT", 0, true, nullptr},
    {"Q", 0, true, nullptr},
    {"^", 2, false, exponentiation},
    {"POWER", 2, false, exponentiation},
    {"EXP", 2, false, exponentiation},
};


int main() {

    // Using precision of two decimals in printing
    cout.precision(2);
    cout << fixed;

    while ( true ) {
        cout << "calculator> ";

        string line = "";
        getline(cin, line);

        if ( line.empty() ) {
            // By inputting an empty line, the user can make the program end.
            cout << GREETING_AT_END << endl;
            break;
        }

        vector<string> pieces = split(line, ' ', true);

        if(pieces.size() == 0){
            continue;
        }

        string command_to_be_executed = pieces.at(0);

        // TODO: Implement command execution here!
        string new_command = "";

        // isoiksi kirjaimiksi
        for ( auto character : command_to_be_executed ) {
            char x = toupper(character);
            new_command.push_back(x);
        }
        // korvataan vanha
        command_to_be_executed = new_command;

        bool command_found = true;

        for ( auto command : COMMANDS) {
            if( command_to_be_executed == command.str ) {
                // komento löytyy
                command_found = true;

                // EXIT komento
                if ( command.is_exit and
                     pieces.size()-1 == command.parameter_number ) {
                    cout << GREETING_AT_END << endl;
                    return 0;
                }

                // summaus
                if ( command.action == addition and
                     pieces.size()-1 == command.parameter_number) {

                    double x;
                    double y;
                    if ( not string_to_double(pieces.at(1), x) ) {
                        cout << "Error: a non-number operand." << endl;
                        break;
                    }
                    if ( not string_to_double(pieces.at(2), y) ) {
                        cout << "Error: a non-number operand." << endl;
                        break;
                    }

                    cout << command.action(x, y) << endl;
                    break;
                }

                // vähennys
                if ( command.action == subtraction and
                     pieces.size()-1 == command.parameter_number) {

                    double x;
                    double y;
                    if ( not string_to_double(pieces.at(1), x) ) {
                        cout << "Error: a non-number operand." << endl;
                        break;
                    }
                    if ( not string_to_double(pieces.at(2), y) ) {
                        cout << "Error: a non-number operand." << endl;
                        break;
                    }

                    cout << command.action(x, y) << endl;
                    break;
                }

                // kertominen
                if ( command.action == multiplication and
                     pieces.size()-1 == command.parameter_number) {

                    double x;
                    double y;
                    if ( not string_to_double(pieces.at(1), x) ) {
                        cout << "Error: a non-number operand." << endl;
                        break;
                    }
                    if ( not string_to_double(pieces.at(2), y) ) {
                        cout << "Error: a non-number operand." << endl;
                        break;
                    }

                    cout << command.action(x, y) << endl;
                    break;
                }

                // jakaminen
                if ( command.action == division and
                     pieces.size()-1 == command.parameter_number) {

                    double x;
                    double y;
                    if ( not string_to_double(pieces.at(1), x) ) {
                        cout << "Error: a non-number operand." << endl;
                        break;
                    }
                    if ( not string_to_double(pieces.at(2), y) ) {
                        cout << "Error: a non-number operand." << endl;
                        break;
                    }

                    cout << command.action(x, y) << endl;
                    break;
                }

                // potenssi
                if ( command.action == exponentiation and
                     pieces.size()-1 == command.parameter_number) {

                    double x;
                    double y;
                    if ( not string_to_double(pieces.at(1), x) ) {
                        cout << "Error: a non-number operand." << endl;
                        break;
                    }
                    if ( not string_to_double(pieces.at(2), y) ) {
                        cout << "Error: a non-number operand." << endl;
                        break;
                    }

                    cout << command.action(x, y) << endl;
                    break;
                }

                // väärä määärä parametrejä
                else {
                    cout << "Error: wrong number of parameters." << endl;
                    command_found = true;
                    break;
                }

            } else {
                // kometo ei löydy
                command_found = false;
            }

        }
        // löytyikö komento
        if ( not command_found ) {
            cout << "Error: unknown command." << endl;
        }


    }
}


// This function exemplifies istringstreams.
// It would be possible to use function stod of string to convert a string to
// a double, but to recognize all error cases would be more complicated with it
// at this phase of education.
// It is easier to use the boolean type return value that can be
// examined at calling point as done in the implementation below.
bool string_to_double(const string& s, double& result) {
    // Initializing input stream of istringstream type the string that will
    // scanned with ">>" or getline.
    istringstream stream(s);

    double tmp;

    // Reading input value in a normal way with ">>" operator.
    // You can operate istringstreams with the same operations as cin
    // and other ifstreams.
    stream >> tmp;

    if ( not stream ) {
        return false;
    }

    // ws is special operator that skips all the word delimiters (such as spaces)
    // until it meets something else
    stream >> ws;

    // If parameter s is a string comprising a valid real number, it cannot
    // succeed other characters than spaces.
    // Since previous ">> ws" operation threw the spaces away, at this point
    // the input stream should contain nothing.
    // If it does, then it is erroneous.
    // Let's try to read a character from the input stream.
    // If this fails, because the input stream has no characters left,
    // then all is right.
    // If it succeeds, then string s has something that it should not have.
    stream.get();

    if ( stream ) {
        return false;
    } else {
        result = tmp;
        return true;
    }
}

// Model implementation of good old split function
vector< string > split(const string& s,
                       const char delimiter,
                       bool ignore_empty){
    vector<string> result;
    string tmp = s;

    while(tmp.find(delimiter) != string::npos)
    {
        string word = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and word.empty()))
        {
            result.push_back(word);
        }

    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}
