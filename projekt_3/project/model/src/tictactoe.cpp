#include "../headers/tictactoe.h"
#include <chrono>
#include <thread>

void TICTACTOE::start_game(Player &player_one, Player &player_two, Game &game)
{
#ifdef linux
    std::cout << "\033[2J\033[1;1H";
#endif
#ifdef __APPLE__
    std::cout << "\033[2J\033[1;1H";
#endif
    std::cout << "X's TURN:\n";
    game.show_plane();

    int is_done = 0;
    while (is_done == 0)
    {
        Player *current_player = player_one.get_is_your_turn() == true ? &player_one : &player_two;
        Player *other_player = player_one.get_is_your_turn() == false ? &player_one : &player_two;

        is_done = current_player->make_turn();
#ifdef linux
        std::cout << "\033[2J\033[1;1H";
#endif
#ifdef __APPLE__
        std::cout << "\033[2J\033[1;1H";
#endif
        current_player->set_is_your_turn(false);
        other_player->set_is_your_turn(true);

        std::cout << char(other_player->get_character()) << "'s TURN:\n";
        game.show_plane();
    }

    if (is_done == 3)
        std::cout << "DRAW!"
                  << "\nWait 3 seconds to return to the menu\n";
    else
        std::cout << "Player " << is_done << " won!\nWait 3 seconds to return to the menu\n";

    std::chrono::milliseconds timespan(3000);
    std::this_thread::sleep_for(timespan);
}

void TICTACTOE::two_players_session(int rows, int amount_to_win)
{
    Player **players = new Player *[2];
    Game *game = new Game(rows, amount_to_win);

    players[0] = new HumanPlayer(true, *game, PLAYER_ONE_CHARACTER);
    players[1] = new HumanPlayer(false, *game, PLAYER_TWO_CHARACTER);

    TICTACTOE::start_game(*players[0], *players[1], *game);

    delete[] players;
    delete game;
}

void TICTACTOE::player_comp_session(int rows, int amount_to_win, bool human_start, int depth)
{
    Game *game = new Game(rows, amount_to_win);
    Player *player_human = new HumanPlayer(human_start, *game, human_start ? PLAYER_ONE_CHARACTER : PLAYER_TWO_CHARACTER);
    Player *player_computer = new ComputerPlayer(!human_start, *game, !human_start ? PLAYER_ONE_CHARACTER : PLAYER_TWO_CHARACTER, depth);

    TICTACTOE::start_game(*player_human, *player_computer, *game);

    delete player_human;
    delete player_computer;
    delete game;
}

void options(int &rows, int &amount_to_win, int &depth)
{
    int option;

    std::cout << "1.Change amount of rows\n2.Change amount of characters in a row to win\n3.Change depth of AI\n4.Go back\n:";
    std::cin >> option;

    while (option > 4 || option < 1)
    {
        std::cout << "Not valid option:";
        std::cin >> option;
    }

    switch (option)
    {
    case 1:
        int new_value;
        std::cout << "Pass new value of rows:";
        std::cin >> new_value;
        while (new_value < 3)
        {
            std::cout << "Not valid value of rows:";
            std::cin >> new_value;
        }

        rows = new_value;
        break;
    case 2:
        int new_value_amount_to_win;
        std::cout << "Pass new value of amount of characters in a row to win (not smaller than rows):";
        std::cin >> new_value_amount_to_win;
        while (new_value_amount_to_win > rows || new_value_amount_to_win < 3)
        {
            std::cout << "Not valid value of characters:";
            std::cin >> new_value_amount_to_win;
        }
        amount_to_win = new_value_amount_to_win;
        break;
    case 3:
        int new_value_depth;
        std::cout << "Pass new value of AI depth:";
        std::cin >> new_value_depth;
        while (new_value_depth < 2)
        {
            std::cout << "Not valid value of depth:";
            std::cin >> new_value_depth;
        }
        depth = new_value_depth;
        break;
    case 4:
        return;
        break;

    default:
        std::cout << "Not valid option:";
        std::cin >> option;
        break;
    }
}

void TICTACTOE::menu_game()
{
#ifdef linux
    std::cout << "\033[2J\033[1;1H";
#endif
#ifdef __APPLE__
    std::cout << "\033[2J\033[1;1H";
#endif
    int option, rows = 3, amount_to_win = 3, depth = 10;
    std::cout << "TICTACTOE\n"
              << "Depth of AI: " << depth << "\n1.Player vs player\n2.Player vs Computer\n3.Options\n4.Exit\n\n:";

    std::cin >> option;

    while (option != 4)
    {
        switch (option)
        {
        case 1:
            TICTACTOE::two_players_session(rows, amount_to_win);
            break;
        case 2:
            char start_option;
            std::cout << "Shall you start? (Y/N):";
            std::cin >> start_option;
            std::cout << start_option << "\n";
            while (start_option != 'Y' && start_option != 'y' && start_option != 'N' && start_option != 'n')
            {
                std::cout << "Not valid option (Y/N):";
                std::cin >> start_option;
            }

            TICTACTOE::player_comp_session(rows, amount_to_win, start_option == 'Y' || start_option == 'y' ? true : false, depth);
            break;
        case 3:
            options(rows, amount_to_win, depth);
            break;
        case 4:
            exit(0);
            break;
        default:
            std::cout << "Not valid option:";
            std::cin >> option;
            break;
        }
#ifdef linux
        std::cout << "\033[2J\033[1;1H";
#endif
#ifdef __APPLE__
        std::cout << "\033[2J\033[1;1H";
#endif
        std::cout << "TICTACTOE\n"
                  << "Depth of AI: " << depth << "\n1.Player vs player\n2.Player vs Computer\n3.Options\n4.Exit\n\n:";
        std::cin >> option;
    }
}
