#pragma once
#define AMOUNT_OF_ROWS 3
#define AMOUNT_OF_CHARS_TO_WIN 3

#include <iostream>

enum Character
{
    DEFAULT_CHARACTER = '\0',
    PLAYER_ONE_CHARACTER = 'X',
    PLAYER_TWO_CHARACTER = 'O'
};

class Game
{
private:
    Character **tic_tac_toe_plane;

    int amount_of_rows;
    int amount_of_chars_to_win;
    int free_places_left;
    Character winner;
    Character last_played;
    int current_streak;

    int check_if_win_row(int row, int column, Character players_character);
    int check_if_win_column(int row, int column, Character players_character);
    int check_if_win_diagonal(int row, int column, Character players_character);
    int check_if_win_antidiagonal(int row, int column, Character players_character);

public:
    Game();
    Game(int amount_of_rows, int amount_of_chars_to_win);
    Game(const Game &other);
    ~Game();

    bool check_if_taken(int row, int column);
    int put_in_place(int row, int column, Character players_character);
    int check_if_win(int row, int column, Character players_character);
    int score(Character players_character, int depth);

    void show_plane();

    int get_amount_of_rows();
    int get_free_places_left();
    Character **get_plane() const;
};

#include "../src/game.cpp"
