#include "../constants/constants.h"
#include "debug.h"

char getTileState(char board[constants::BOARD_SIZE][constants::BOARD_SIZE], int row, int col)
{
    /*Checking if a tile is empty or occupied by a black/white piece*/

    return board[row][col];
}
