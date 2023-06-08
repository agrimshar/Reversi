#include "../constants/constants.h"
#include "../logic/game.h"
#include "gameFlow.h"

#include <iostream>
#include <limits>

void printBoard(char board[constants::BOARD_SIZE][constants::BOARD_SIZE])
{
    /*Prints out array*/
    std::cout << " ";

    for (int i = -1; i < constants::BOARD_SIZE; i++)
    {
        for (int j = -1; j < constants::BOARD_SIZE; j++)
        {
            // Prints out column numbers
            if (i == -1)
            {
                // Fixes bug of printing out 1 - 9 instead of 1 - 8
                if (j == constants::BOARD_SIZE - 1)
                {
                    continue;
                }
                std::cout << "   " << j + 2;
            }
            // Prints out row numbers and grid style
            else if (j == -1)
            {
                std::cout << "  +---+---+---+---+---+---+---+---+\n";
                std::cout << i + 1 << " |";
            }
            // Prints out board pieces with grid formatting
            else
            {
                std::cout << " " << board[i][j] << " |";
            }
        }
        std::cout << "\n"; // New line after each row is printed
    }
    std::cout << "  +---+---+---+---+---+---+---+---+\n"; // Last grid row formatting
}

void printLegalMove(char board[constants::BOARD_SIZE][constants::BOARD_SIZE], int row, int col)
{
    board[row][col] = constants::VALID;
}

void placeTile(char board[constants::BOARD_SIZE][constants::BOARD_SIZE], char playerColor, int *row, int *col)
{
    /*Places tile onto the game board*/

    // Get input from user
    std::cout << "Where do you want to place your " << playerColor << " tile ([row] [col]): ";
    std::cin >> *row >> *col;

    // Subracting by 1 to account for user input from 1 - 8, not 0 - 7
    *row = *row - 1;
    *col = *col - 1;

    // Check if input is in bounds (-1 because player enters number from 1 - 8, not 0 - 7)
    while (!isValidMoveEmptyTile(board, playerColor, *row, *col))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Invalid move. Where do you want to place your tile ([row] [col]): ";
        std::cin >> *row >> *col;

        // Subracting by 1 to account for user input from 1 - 8, not 0 - 7
        *row = *row - 1;
        *col = *col - 1;
    }

    board[*row][*col] = playerColor;
}

void flipTiles(char gameBoard[constants::BOARD_SIZE][constants::BOARD_SIZE], char player, int row, int col)
{
    // BROKEN
    for (int i = 0; i < 8; i++)
    {
        if (isEmptyTileLegalInDirection(gameBoard, player, row, col, constants::DIRECTIONS[i][0], constants::DIRECTIONS[i][1]))
        {
            int switchRow{row};
            int switchCol{col};

            switchRow += constants::DIRECTIONS[i][1];
            switchCol += constants::DIRECTIONS[i][0];

            while (gameBoard[switchRow][switchCol] != player && isPositionInBounds(switchRow, switchCol))
            {
                gameBoard[switchRow][switchCol] = player;

                switchRow += constants::DIRECTIONS[i][1];
                switchCol += constants::DIRECTIONS[i][0];
            }
        }
    }
}

void makeMove(char board[constants::BOARD_SIZE][constants::BOARD_SIZE], char player)
{
    int row{};
    int col{};

    placeTile(board, player, &row, &col);
    flipTiles(board, player, row, col);
}
