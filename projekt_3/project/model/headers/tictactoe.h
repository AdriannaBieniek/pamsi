#pragma once
#include <iostream>
#include "game.h"
#include "player.h"
#include "humanPlayer.h"
#include "computer.h"

namespace TICTACTOE
{
    void start_game(Player &player_one, Player &player_two, Game &game);
    void two_players_session(int rows, int amount_to_win);
    void player_comp_session(int rows, int amount_to_win, bool human_start, int depth);
    void menu_game();
}

#include "../src/tictactoe.cpp"
