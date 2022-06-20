#include "../headers/humanPlayer.h"

HumanPlayer::HumanPlayer()
{
    this->is_your_turn = true;
    this->game = nullptr;
    this->players_character = PLAYER_ONE_CHARACTER;
}

HumanPlayer::HumanPlayer(bool is_your_turn, Game &game, Character players_character)
{
    this->is_your_turn = is_your_turn;
    this->game = &game;
    this->players_character = players_character;
}

bool HumanPlayer::get_is_your_turn()
{
    return this->is_your_turn;
}

void HumanPlayer::set_is_your_turn(bool new_is_your_turn)
{
    this->is_your_turn = new_is_your_turn;
}

Character HumanPlayer::get_character()
{
    return this->players_character;
}

int HumanPlayer::make_turn()
{

    int row, column;
    std::cout << "Choose position (row column): ";
    std::cin >> row >> column;

    while (row - 1 >= this->game->get_amount_of_rows() || row < 1 || column - 1 >= this->game->get_amount_of_rows() || column < 1 || this->game->check_if_taken(row - 1, column - 1))
    {
        std::cout << "Choose another position, the previous one is not avaible (row column): ";
        std::cin >> row >> column;
    }

    int result_of_turn = this->game->put_in_place(row - 1, column - 1, this->players_character);

    return result_of_turn;
}
