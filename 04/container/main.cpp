#include <cstdlib>
#include <iostream>
#include <vector>


void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;

        // std::cout << new_integer << std::endl;

        ints.push_back(new_integer);
        // TODO: Implement your solution here
    }
}



bool same_values(std::vector < int > ints) {
    for ( int alkio: ints) {
        if ( alkio != ints.front()) {
            return false;
        }

    }
    return true;
}

bool is_ordered_non_strict_ascending(std::vector < int > ints) {
    int j = 0;
    for ( unsigned int i = 1; i < ints.size(); ++i) {
        j = i-1;

        if ( ints.at(j) <= ints.at(i) ) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}

bool is_arithmetic_series(std::vector < int > ints) {
    int j = 0;

    int e = ints.at(1) - ints.at(0);

    for ( unsigned int i = 1; i < ints.size(); ++i) {
        j = i-1;

        if ( ints.at(i) - ints.at(j) == e ) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}

bool is_geometric_series(std::vector < int > ints) {

    for ( int alkio: ints) {
        if ( alkio == 0) {
            return false;
        }
    }
    int j = 0;

    if ( ints.at(0) and ints.at(1) == 0) {
        std::cout << "vittu" << std::endl;
        return false;
    }

    double e = ints.at(1) / ints.at(0);

    for ( unsigned int i = 1; i < ints.size(); ++i) {
        j = i-1;

        if ( ints.at(i) / ints.at(j) != e ) {
            return false;
        }
    }

    return true;
}


int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
