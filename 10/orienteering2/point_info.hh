
// uusi toteutettu luokka, jonka avulla tallennetaan jokaisen pisteet tiedot.

#ifndef POINT_INFO_HH
#define POINT_INFO_HH
#include <string>

class Point_info
{
public:
    Point_info();

    std::string name_;
    int x_;
    int y_;
    int height_;
    char marker_;
};

#endif // POINT_INFO_HH
