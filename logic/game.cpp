#include "../constants/constants.h"
#include "game.h"

bool isPositionInBounds(int row, int col)
{
    /*Checks if the inputted value is within the game board*/

    // Game array counts from 0 to BOARD_SIZE - 1
    if (row < 0 || row > constants::BOARD_SIZE - 1 || col < 0 || col > constants::BOARD_SIZE - 1)
    {
        return false;
    }

    return true;
}

bool isTileEmpty(char gameBoard[constants::BOARD_SIZE][constants::BOARD_SIZE], int row, int col)
{
    /*Checks if specific tile is empty*/

    if (gameBoard[row][col] == constants::BLACK || gameBoard[row][col] == constants::WHITE)
    {
        return false;
    }

    return true;
}

bool isGameOver(char board[constants::BOARD_SIZE][constants::BOARD_SIZE])
{
    for (int i = 0; i < constants::BOARD_SIZE; i++)
    {
        for (int j = 0; j < constants::BOARD_SIZE; j++)
        {
            if (isTileEmpty(board, i, j))
            {
                return false;
            }
        }
    }

    return true;
}

bool isEmptyTileLegalInDirection(char board[constants::BOARD_SIZE][constants::BOARD_SIZE], char player, int row, int col, int dx, int dy)
{
    /*Checking if legal move is available in direction from an empty tile*/

    // Increment in change of direction to get off of current tile
    row += dy;
    col += dx;

    // If out of bounds, move not valid
    if (!isPositionInBounds(row, col))
    {
        return false;
    }

    // If adacent tile is empty or the same color, move not valid
    if (board[row][col] == constants::EMPTY || board[row][col] == player)
    {
        return false;
    }

    // Move onto the next tile
    row += dy;
    col += dx;

    // Keep checking through tiles until board boarder is reached
    // This loop only checks for tiles with current player color or empty
    while (isPositionInBounds(row, col))
    {
        // If player color is found, the move is available
        if (board[row][col] == player)
        {
            return true;
        }
        // If empty tile is found, move is not available
        else if (board[row][col] == constants::EMPTY)
        {
            return false;
        }

        // If opponent color is found, increment row and col
        row += dy;
        col += dx;
    }

    // If out of bounds, move is not available
    return false;
}

bool isNotEmptyTileLegalInDirection(char board[constants::BOARD_SIZE][constants::BOARD_SIZE], char player, int row, int col, int dx, int dy)
{
    /*Checking if legal move is available in direction from an non empty tile*/

    // Increment in change of direction to get off of current tile
    row += dy;
    col += dx;

    // If out of bounds, move not valid
    if (!isPositionInBounds(row, col))
    {
        return false;
    }

    // If adacent tile is empty or the same color, move not valid
    if (board[row][col] == constants::EMPTY || board[row][col] == player)
    {
        return false;
    }

    // Move onto the next tile
    row += dy;
    col += dx;

    // Keep checking through tiles until board boarder is reached
    // This loop only checks for tiles with current player color or empty
    while (isPositionInBounds(row, col))
    {
        // If player color is found, the move is not available
        if (board[row][col] == player)
        {
            return false;
        }
        // If empty tile is found, move is available
        else if (board[row][col] == constants::EMPTY)
        {
            return true;
        }

        // If opponent color is found, increment row and col
        row += dy;
        col += dx;
    }

    // If out of bounds, move is not available
    return false;
}

bool isValidMoveEmptyTile(char gameBoard[constants::BOARD_SIZE][constants::BOARD_SIZE], char player, int row, int col)
{
    /*Checks if an empty tile has legal moves*/

    for (int i = 0; i < 8; i++)
    {
        if (isPositionInBounds(row, col) && isTileEmpty(gameBoard, row, col) && isEmptyTileLegalInDirection(gameBoard, player, row, col, constants::DIRECTIONS[i][0], constants::DIRECTIONS[i][1]))
        {
            return true;
        }
    }

    return false;
}

bool isValidMoveNotEmptyTile(char gameBoard[constants::BOARD_SIZE][constants::BOARD_SIZE], char player, int row, int col)

{
    /*Checks if non-empty tile creates legal moves*/

    for (int i = 0; i < 8; i++)
    {
        if (isPositionInBounds(row, col) && !isTileEmpty(gameBoard, row, col) && isNotEmptyTileLegalInDirection(gameBoard, player, row, col, constants::DIRECTIONS[i][0], constants::DIRECTIONS[i][1]))
        {
            return true;
        }
    }

    return false;
}

bool isPlayerMovePossible(char board[constants::BOARD_SIZE][constants::BOARD_SIZE], char player)
{
    for (int i = 0; i < constants::BOARD_SIZE; i++)
    {
        for (int j = 0; j < constants::BOARD_SIZE; j++)
        {
            if (board[i][j] == player)
            {
                if (isValidMoveNotEmptyTile(board, player, i, j))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

int getScore(char board[constants::BOARD_SIZE][constants::BOARD_SIZE], char player)
{
    int score{};

    for (int i = 0; i < constants::BOARD_SIZE; i++)
    {
        for (int j = 0; j < constants::BOARD_SIZE; j++)
        {
            if (board[i][j] == player)
            {
                score++;
            }
        }
    }

    return score;
}

void switchPlayerTurn(bool *playerOneTurn, bool *playerTwoTurn)
{
    /*Switches the player turn by passing in  booleans by reference*/

    if (*playerOneTurn)
    {
        *playerTwoTurn = true;
        *playerOneTurn = false;
    }
    else if (*playerTwoTurn)
    {
        *playerOneTurn = true;
        *playerTwoTurn = false;
    }
}
