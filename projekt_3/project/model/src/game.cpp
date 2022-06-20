#include "../headers/game.h"
#include <math.h>

Game::Game()
{
    this->amount_of_rows = AMOUNT_OF_ROWS;
    this->amount_of_chars_to_win = AMOUNT_OF_CHARS_TO_WIN;
    this->free_places_left = AMOUNT_OF_ROWS * AMOUNT_OF_ROWS;
    this->winner = DEFAULT_CHARACTER;

    this->tic_tac_toe_plane = new Character *[AMOUNT_OF_ROWS];

    for (int index = 0; index < AMOUNT_OF_ROWS; ++index)
    {
        this->tic_tac_toe_plane[index] = new Character[AMOUNT_OF_ROWS];

        for (int index_column = 0; index_column < AMOUNT_OF_ROWS; ++index_column)
        {
            this->tic_tac_toe_plane[index][index_column] = DEFAULT_CHARACTER;
        }
    }
}

Game::Game(int amount_of_rows, int amount_of_chars_to_win)
{
    this->amount_of_rows = amount_of_rows;
    this->amount_of_chars_to_win = amount_of_chars_to_win;
    this->free_places_left = amount_of_rows * amount_of_rows;
    this->winner = DEFAULT_CHARACTER;

    this->tic_tac_toe_plane = new Character *[amount_of_rows];

    for (int index = 0; index < amount_of_rows; ++index)
    {
        this->tic_tac_toe_plane[index] = new Character[amount_of_rows];

        for (int index_column = 0; index_column < amount_of_rows; ++index_column)
        {
            this->tic_tac_toe_plane[index][index_column] = DEFAULT_CHARACTER;
        }
    }
}

Game::Game(const Game &other)
{
    this->amount_of_rows = other.amount_of_rows;
    this->amount_of_chars_to_win = other.amount_of_chars_to_win;
    this->free_places_left = other.free_places_left;
    this->winner = other.winner;

    this->tic_tac_toe_plane = new Character *[this->amount_of_rows];
    for (int index_row = 0; index_row < this->amount_of_rows; ++index_row)
    {
        this->tic_tac_toe_plane[index_row] = new Character[this->amount_of_rows];

        for (int index_column = 0; index_column < this->amount_of_rows; ++index_column)
        {
            this->tic_tac_toe_plane[index_row][index_column] = other.get_plane()[index_row][index_column];
        }
    }
}

Game::~Game()
{
    for (int index = 0; index < this->amount_of_rows; index++)
    {
        delete[] this->tic_tac_toe_plane[index];
    }

    delete[] this->tic_tac_toe_plane;
}

bool Game::check_if_taken(int row, int column)
{
    return this->tic_tac_toe_plane[row][column] != '\0';
}

int Game::put_in_place(int row, int column, Character players_character)
{

    if (row == -1 || column == -1)
        return 0;

    this->tic_tac_toe_plane[row][column] = players_character;

    this->free_places_left--;

    return this->check_if_win(row, column, players_character);
}

int Game::check_if_win_row(int row, int column, Character players_character)
{
    int current_streak = 1;

    for (int index_row = row + 1; index_row < this->amount_of_rows; ++index_row)
    {
        if (this->tic_tac_toe_plane[index_row][column] == players_character)
            current_streak++;
        else
            break;

        if (current_streak == this->amount_of_chars_to_win)
            return current_streak;
    }

    for (int index_row = row - 1; index_row >= 0; --index_row)
    {
        if (this->tic_tac_toe_plane[index_row][column] == players_character)
            current_streak++;
        else
            break;

        if (current_streak == this->amount_of_chars_to_win)
            return current_streak;
    }

    return current_streak;
}

int Game::check_if_win_column(int row, int column, Character players_character)
{
    int current_streak = 1;

    for (int index_column = column + 1; index_column < this->amount_of_rows; ++index_column)
    {
        if (this->tic_tac_toe_plane[row][index_column] == players_character)
            current_streak++;
        else
            break;

        if (current_streak == this->amount_of_chars_to_win)
            return current_streak;
    }

    for (int index_column = column - 1; index_column >= 0; --index_column)
    {
        if (this->tic_tac_toe_plane[row][index_column] == players_character)
            current_streak++;
        else
            break;

        if (current_streak == this->amount_of_chars_to_win)
            return current_streak;
    }

    return current_streak;
}

int Game::check_if_win_diagonal(int row, int column, Character players_character)
{
    int current_streak = 1;

    int max = row > column ? row : column;
    int min = row < column ? row : column;

    for (int index = 1; index < this->amount_of_rows - max; ++index)
    {
        if (this->tic_tac_toe_plane[row + index][column + index] == players_character)
            current_streak++;
        else
            break;

        if (current_streak == this->amount_of_chars_to_win)
            return current_streak;
    }

    for (int index = 1; index <= min; ++index)
    {
        if (this->tic_tac_toe_plane[row - index][column - index] == players_character)
            current_streak++;
        else
            break;

        if (current_streak == this->amount_of_chars_to_win)
            return current_streak;
    }

    return current_streak;
}

int Game::check_if_win_antidiagonal(int row, int column, Character players_character)
{
    int current_streak = 1;

    int new_row = row - 1;
    int new_col = column + 1;
    while (new_row >= 0 && new_col < this->amount_of_rows)
    {
        if (this->tic_tac_toe_plane[new_row][new_col] == players_character)
            current_streak++;
        else
            break;

        if (current_streak == this->amount_of_chars_to_win)
            return current_streak;

        new_row--;
        new_col++;
    }

    new_row = row + 1;
    new_col = column - 1;
    while (new_row < this->amount_of_rows && new_col >= 0)
    {
        if (this->tic_tac_toe_plane[new_row][new_col] == players_character)
            current_streak++;
        else
            break;

        if (current_streak == this->amount_of_chars_to_win)
            return current_streak;

        new_row++;
        new_col--;
    }

    return current_streak;
}

int Game::check_if_win(int row, int column, Character players_character)
{
    int result = 0;

    result = this->check_if_win_row(row, column, players_character);
    if (result < this->amount_of_chars_to_win)
        result = this->check_if_win_column(row, column, players_character);
    if (result < this->amount_of_chars_to_win)
        result = this->check_if_win_diagonal(row, column, players_character);
    if (result < this->amount_of_chars_to_win)
        result = this->check_if_win_antidiagonal(row, column, players_character);

    if (result < this->amount_of_chars_to_win && this->free_places_left == 0)
        return 3;

    if (result >= this->amount_of_chars_to_win)
        this->winner = players_character;

    this->current_streak = result;
    this->last_played = players_character;

    return result == this->amount_of_chars_to_win ? (players_character == PLAYER_ONE_CHARACTER ? 1 : 2) : 0;
}

int Game::score(Character players_character, int depth)
{
    int additions = depth;

    if (this->winner == DEFAULT_CHARACTER)
        if (this->free_places_left == 0)
            return 0;
        else
            return players_character == this->last_played ? this->current_streak : -this->current_streak;

    else if (this->winner == players_character)
        return 10 + additions;
    else
        return -10 - additions;
}

void Game::show_plane()
{
    int index_row = 0;
    for (int index = -1; index < this->amount_of_rows * 2; ++index)
    {
        for (int index_column = -1; index_column < this->amount_of_rows; ++index_column)
        {
            if (index == -1 || index % 2 != 0)
            {
                if (index == -1)
                    std::cout << "" << (index_column == -1 ? '\0' : index_column + 1) << " | ";

                else
                {
                    if (index_column == -1)
                        std::cout << "" << index_row + 1 << " |";
                    else
                    {
                        if (this->tic_tac_toe_plane[index_row][index_column] == DEFAULT_CHARACTER)
                            std::cout << " - |";
                        else if (this->tic_tac_toe_plane[index_row][index_column] == PLAYER_ONE_CHARACTER)
                        {
                            std::cout << " ";
#ifdef linux
                            std::cout << "\x1b[32m";
#endif
#ifdef __APPLE__
                            std::cout << "\x1b[32m";
#endif
                            std::cout << char(this->tic_tac_toe_plane[index_row][index_column]);
#ifdef linux
                            std::cout << "\x1b[0m";
#endif
#ifdef __APPLE__
                            std::cout << "\x1b[0m";
#endif
                            std::cout << " |";
                        }
                        else
                        {
                            std::cout << " ";
#ifdef linux
                            std::cout << "\x1b[31m";
#endif
#ifdef __APPLE__
                            std::cout << "\x1b[31m";
#endif

                            std::cout << char(this->tic_tac_toe_plane[index_row][index_column]);
#ifdef linux
                            std::cout << "\x1b[0m";
#endif
#ifdef __APPLE__
                            std::cout << "\x1b[0m";
#endif
                            std::cout << " |";
                        }
                    }
                }
            }
            else
            {
                std::cout << "----";
            }
        }
        if (index != -1 && index % 2 != 0)
            index_row++;
        std::cout << "\n";
    }
}

int Game::get_amount_of_rows()
{
    return this->amount_of_rows;
}

int Game::get_free_places_left()
{
    return this->free_places_left;
}

Character **Game::get_plane() const
{
    return this->tic_tac_toe_plane;
}
