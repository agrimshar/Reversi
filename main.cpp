#include "constants/constants.h"
#include "logic/game.h"
#include "logic/pregame.h"
#include "ui/gameFlow.h"
#include "debug/debug.h"

#include <iostream>
#include <cstdlib>

int main()
{
    char gameBoard[constants::BOARD_SIZE][constants::BOARD_SIZE]{};
    bool playerOne = true;
    bool playerTwo = false;

    std::cout << "Black makes the first move.\n";
    initializeBoard(gameBoard);
    printBoard(gameBoard);

    do
    {
        if (playerOne && isPlayerMovePossible(gameBoard, constants::BLACK))
        {
            makeMove(gameBoard, constants::BLACK);
            printBoard(gameBoard);
            switchPlayerTurn(&playerOne, &playerTwo);
        }
        else if (playerTwo && isPlayerMovePossible(gameBoard, constants::WHITE))
        {
            makeMove(gameBoard, constants::WHITE);
            printBoard(gameBoard);
            switchPlayerTurn(&playerOne, &playerTwo);
        }
    } while (!isGameOver(gameBoard) && (isPlayerMovePossible(gameBoard, constants::WHITE) || isPlayerMovePossible(gameBoard, constants::BLACK)));

    std::cout << "BLACK: " << getScore(gameBoard, constants::BLACK) << "\n";
    std::cout << "WHITE: " << getScore(gameBoard, constants::WHITE) << "\n";

    return 0;
}