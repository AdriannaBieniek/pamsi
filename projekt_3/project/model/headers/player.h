#pragma once
#include "game.h"

class Player
{
protected:
    bool is_your_turn;
    Game *game;
    Character players_character;

public:
    virtual ~Player(){};
    virtual int make_turn() = 0;

    virtual bool get_is_your_turn() = 0;
    virtual void set_is_your_turn(bool new_is_your_turn) = 0;
    virtual Character get_character() = 0;
};
