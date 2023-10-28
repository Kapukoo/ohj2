#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here
// Do not change main function
const std::vector < std::string > split(std::string line, char separator, bool skip = false) {
    std::string erkki = "";
    std::vector < std::string > sirpa = {};
    if ( not skip) {
        for ( auto part : line) {
            if ( part != separator) {
                erkki.push_back(part);

            }
            if ( part == separator) {
                sirpa.push_back(erkki);
                erkki = "";
                }

        }
        sirpa.push_back(erkki);
    }
    if (skip) {
        for ( auto part : line) {
            if ( part != separator) {
                erkki.push_back(part);

            }
            if ( part == separator) {
                if ( erkki == "") {
                    continue;
                }
                sirpa.push_back(erkki);
                erkki = "";
                }
            }
        sirpa.push_back(erkki);
        }
    return sirpa;
}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
