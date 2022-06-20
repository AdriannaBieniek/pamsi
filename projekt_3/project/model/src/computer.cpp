#include "../headers/computer.h"
#include <limits.h>

ComputerPlayer::ComputerPlayer()
{
    this->is_your_turn = true;
    this->game = nullptr;
    this->players_character = PLAYER_ONE_CHARACTER;
    this->depth = 10;
}

ComputerPlayer::ComputerPlayer(bool is_your_turn, Game &game, Character players_character, int depth)
{
    this->is_your_turn = is_your_turn;
    this->game = &game;
    this->players_character = players_character;
    this->depth = depth;
}

bool ComputerPlayer::get_is_your_turn()
{
    return this->is_your_turn;
}

void ComputerPlayer::set_is_your_turn(bool new_is_your_turn)
{
    this->is_your_turn = new_is_your_turn;
}

Character ComputerPlayer::get_character()
{
    return this->players_character;
}

Result ComputerPlayer::minimax(Node previousBoard, int row, int column, int depth, int alpha,
                               int beta, bool maximizingPlayer)
{
    Node board = Node{Game(previousBoard.board)};

    Character minimizingPlayerCharacter = this->get_character() == PLAYER_ONE_CHARACTER
                                              ? PLAYER_ONE_CHARACTER
                                              : PLAYER_TWO_CHARACTER;

    Character maximizingPlayerCharacter = this->get_character() != PLAYER_ONE_CHARACTER
                                              ? PLAYER_ONE_CHARACTER
                                              : PLAYER_TWO_CHARACTER;

    int row_result = row, column_result = column;
    int result_of_move = board.board.put_in_place(row, column, maximizingPlayer ? maximizingPlayerCharacter : minimizingPlayerCharacter);

    if (result_of_move != 0 || depth == 0)
    {

        return Result{
            board.board.score(this->players_character, depth),
            row_result,
            column_result,
        };
    }
    if (maximizingPlayer)
    {
        int maxScore = INT_MIN;
        int do_stop = false;
        for (int index_row = 0; index_row < board.board.get_amount_of_rows(); ++index_row)
        {

            if (do_stop)
                break;
            for (int index_column = 0; index_column < board.board.get_amount_of_rows(); ++index_column)
            {
                if (board.board.get_plane()[index_row][index_column] == '\0')
                {
                    Result child_result = this->minimax(board, index_row, index_column, depth - 1, alpha, beta, false);

                    if (maxScore < child_result.score)
                    {
                        row_result = index_row;
                        column_result = index_column;
                    }
                    maxScore = maxScore > child_result.score ? maxScore : child_result.score;

                    alpha = alpha > child_result.score ? alpha : child_result.score;
                    if (beta <= alpha)
                    {
                        do_stop = true;
                        break;
                    }
                }
            }
        }
        return Result{maxScore, row_result, column_result};
    }
    else
    {
        int minScore = INT_MAX;
        int do_stop = false;

        for (int index_row = 0; index_row < board.board.get_amount_of_rows(); ++index_row)
        {
            if (do_stop)
                break;
            for (int index_column = 0; index_column < board.board.get_amount_of_rows(); ++index_column)
            {
                if (board.board.get_plane()[index_row][index_column] == '\0')
                {
                    Result child_result = this->minimax(board, index_row, index_column, depth - 1, alpha, beta, true);

                    minScore = minScore < child_result.score ? minScore : child_result.score;

                    beta = beta < child_result.score ? beta : child_result.score;
                    if (beta <= alpha)
                    {
                        do_stop = true;
                        break;
                    }
                }
            }
        }
        return Result{minScore, row_result, column_result};
    }
}

int ComputerPlayer::make_turn()
{
    Result row_column = this->minimax(Node{Game(*this->game)}, -1, -1, this->depth, INT_MIN, INT_MAX, true);
    std::cout << row_column.row << " " << row_column.column << "\n";

    int result_of_turn = this->game->put_in_place(row_column.row, row_column.column, this->players_character);

    return result_of_turn;
}
