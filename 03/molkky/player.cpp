#include "player.hh"
#include <iostream>


Player::Player(std::string player_name):
    player_name_(player_name)
{

}

std::string Player::get_name() const{
    // std::cout << player_name_ << std::endl;
    return player_name_;
}

void Player::add_points(int points) {
    player_points_ += points;

    if ( player_points_ > 50) {
        player_points_ = 25;
    }

}


int Player::get_points() const{
    // std::cout << player_points_ << std::endl;
    return player_points_;
}

bool Player::has_won() {
    if ( player_points_ == 50) {
        return true;
    } else {
        return false;
    }
}
