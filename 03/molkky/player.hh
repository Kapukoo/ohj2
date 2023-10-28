#ifndef PLAYER_HH
#define PLAYER_HH
#include <string>


class Player
{
public:
    Player();

    Player(std::string player_name);

    std::string get_name() const;

    void add_points(int points);

    int get_points() const;

    bool has_won();

private:

    std::string player_name_;
    int player_points_ = 0;
};

#endif // PLAYER_HH
