#include "../constants/constants.h"
#include "pregame.h"

void initializeBoard(char gameBoard[constants::BOARD_SIZE][constants::BOARD_SIZE])
{
    /*Initializing the games starting board in an array*/

    // Looping through the game board to populate it
    for (int i = 0; i < constants::BOARD_SIZE; i++)
    {
        for (int j = 0; j < constants::BOARD_SIZE; j++)
        {
            // Empty tiles on board is filled with a space
            gameBoard[i][j] = constants::EMPTY;

            // The center tiles start with 2 white and black pieces diagonal from eachother
            if ((i == 3 && j == 3) || (i == 4 && j == 4))
            {
                gameBoard[i][j] = constants::WHITE;
            }
            else if ((i == 3 && j == 4) || (i == 4 && j == 3))
            {
                gameBoard[i][j] = constants::BLACK;
            }
        }
    }
}