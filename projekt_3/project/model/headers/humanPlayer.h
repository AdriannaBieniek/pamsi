#pragma once

#include <iostream>
#include "player.h"
#include "game.h"

class HumanPlayer : public Player
{
private:
public:
    HumanPlayer();
    HumanPlayer(bool is_your_turn, Game &game, Character players_character);
    ~HumanPlayer(){};
    int make_turn();
    bool get_is_your_turn();
    void set_is_your_turn(bool new_is_your_turn);
    Character get_character();
};

#include "../src/humanPlayer.cpp"
