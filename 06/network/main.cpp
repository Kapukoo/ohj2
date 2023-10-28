#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

void print(std::map <std::string, std::vector<std::string> > book, std::string id, int x = 0) {

    if ( x == 0) {
        std::cout << id << std::endl;
    }

    std::string dots(2*(x+1), '.');

    if ( book.find(id) != book.end() and book[id].size() != 0) {
        // löytyy
        for (auto name : book.at(id) ) {
            std::cout << dots << name << std::endl;

            if ( book.find(name) != book.end() and book[name].size() != 0) {
                // löytyy
                print(book, name, x+1);

            }
            // mahdollisesti turhaa koodia, mutta en uskalla poistaakkaan
            if ( book.find(name) != book.end() and book[name].size() == 0) {
                std::string dots(2*(x+1)+2, '.');
                std::cout << dots << name << std::endl;
            }
        }
    }
}

int count(std::map <std::string, std::vector<std::string> > book, std::string id, int num = 0) {



    if ( book.find(id) != book.end() ) {
        // löytyy
        num += book.at(id).size();

        for (auto name : book.at(id) ) {

            if ( book.find(name) != book.end() ) {
                // löytyy
                int y = count(book, name);
                num += y;
            }

        }
    }
    return num;
}

void depth(std::map <std::string, std::vector<std::string> > book, std::string id, int x = 0) {


    if ( book.find(id) != book.end() ) {
        // löytyy
        for (auto name : book.at(id) ) {

            if ( book.find(name) != book.end() ) {
                // löytyy
                return depth(book, name, x+1);
            } else {
                std::cout << x+2 << std::endl;

                return;
            }
        }

    } else {
        std::cout << "1" << std::endl;
    }

}

int main()
{
    // TODO: Implement the datastructure here
    std::map <std::string, std::vector<std::string> > book;

    while(true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!
            if ( book.find(id1) == book.end() ) {
                // ei löydy
                std::vector<std::string> v;
                v = {id2};
                book[id1] = v;
            } else {
                book[id1].push_back(id2);
            }


        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            print(book, id);

        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            std::cout << count(book, id) << std::endl;

        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            depth(book, id);


        }
        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
