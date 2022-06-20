#pragma once

#include <iostream>
#include "player.h"
#include "game.h"

struct Node
{
    Game board;
};

struct Result
{
    int score;
    int row;
    int column;
};

class ComputerPlayer : public Player
{
private:
    Result minimax(Node previousBoard, int row, int column, int depth, int alpha, int beta, bool maximizingPlayer);
    int depth;

public:
    ComputerPlayer();
    ComputerPlayer(bool is_your_turn, Game &game, Character players_character, int depth);
    ~ComputerPlayer(){};
    int make_turn();
    bool get_is_your_turn();
    void set_is_your_turn(bool new_is_your_turn);
    Character get_character();
};

#include "../src/computer.cpp"
