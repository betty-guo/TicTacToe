#include <iostream>
#include <array>

class TicTacToe
{
    enum PLAYER
    {
        NONE    = 0,
        PLAYER1 = 1,  // 'O'
        PLAYER2 = -1, // 'X'
    };

    union //only one data structure being held at one time
    {
        PLAYER    _dim1[9] = {NONE};//1d array for board
        PLAYER    _dim2[3][3];//2d array for board
    };

    typedef std::array<std::string, 2> strarr2_t;//sets the variable to represent an array of 2 strings
    strarr2_t  _name;//creates an array of two strings called name

    bool _player1_turn;

    inline std::string get_player_name(std::size_t player)//inline function to get player name
    {
        std::string name;

        std::cout << "Player " << player << " name: ";
        if (not (std::cin >> name).good())
            throw std::runtime_error("Input error");
        return name;
    }

public:
    TicTacToe(void) : //automatically run at launch
        _name{{get_player_name(1u), get_player_name(2u)}}, //gets 2 names at launch
        _player1_turn(true)//starts with player 1
    {
    }

    int loop(void)
    {
        do
        {
            display_board();//print board
            player_input();//use input
        } while (not game_finished());
        return display_board(), 0;//if game didn't end, print board
    }

private:
    void display_board(void) //prints board
    {
        for (std::size_t i(0) ; i < 3 ; ++i)
        {
            std::cout << "+---+---+---+\n";
            for (std::size_t j(0) ; j < 3 ; ++j)
            {
                switch (_dim2[i][j])//board array
                {
                case PLAYER1:
                    std::cout << "| O ";
                    break ;
                case PLAYER2:
                    std::cout << "| X ";
                    break ;
                default:
                    std::cout << "|(" << 3 * i + j + 1 << ")";
                }
            }
            std::cout << "|\n";
        }
        std::cout << "+---+---+---+\n";
    }

    void player_input(void)
    {
        std::string   input;
        int choice;

        do
        {
            std::cout << _name[_player1_turn ? 0 : 1] << "'s turn ("
                    << (_player1_turn ? 'O' : 'X') << ") : " << std::flush; //if statememt
            if (not (std::cin >> input).good())
                throw std::runtime_error("Input error");
            choice = std::stoi(input);
        } while (choice < 1 or choice > 9 or _dim1[choice - 1] != NONE);
        _dim1[choice - 1] = (_player1_turn ? PLAYER1 : PLAYER2);
        _player1_turn = not _player1_turn;
    }

    bool winner(void)
    {
        // Check horizontally and vertically
        for (std::size_t i(0) ; i < 3 ; ++i)
        {
            if ((_dim2[0][i] + _dim2[1][i] + _dim2[2][i]) / 3 or
                    (_dim2[i][0] + _dim2[i][1] + _dim2[i][2]) / 3)
                return true;
        }
        // Check for diagonals
        if ((_dim2[0][0] + _dim2[1][1] + _dim2[2][2]) / 3 or
                (_dim2[2][0] + _dim2[1][1] + _dim2[0][2]) / 3)
            return true;
        // Draw
        return false;
    }

    bool game_finished(void)
    {
        /* If there is a winner, the game has finished */
        if (winner())
        {
            std::cout << _name[_player1_turn ? 1 : 0] << " won:\n";
            return true;
        }
        /* If there is a free cell, the game must continue */
        for (std::size_t i(0) ; i < 9 ; ++i)
            if (_dim1[i] == NONE)
                return false;
        /* There are no more free cells: this is a draw */
        std::cout << "Draw:\n";
        return true;
    }
};

int main(void)
{
    std::cout << "This program is a games of TicTacToe" << std::endl;
    return TicTacToe().loop();
}
