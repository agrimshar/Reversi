#include "playGame.h"
#include "../constants/constants.h"
#include "../logic/game.h"
#include "../logic/pregame.h"
#include "gameFlow.h"
#include "welcome.h"

#include <iostream>
#include <cstdlib>
#include <limits>

void playGame()
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
            std::cout << "\n";
            printBoard(gameBoard);
            switchPlayerTurn(&playerOne, &playerTwo);
        }
        else if (playerTwo && isPlayerMovePossible(gameBoard, constants::WHITE))
        {
            makeMove(gameBoard, constants::WHITE);
            std::cout << "\n";
            printBoard(gameBoard);
            switchPlayerTurn(&playerOne, &playerTwo);
        }
    } while (!isGameOver(gameBoard) && (isPlayerMovePossible(gameBoard, constants::WHITE) || isPlayerMovePossible(gameBoard, constants::BLACK)));

    int blackScore{getScore(gameBoard, constants::BLACK)};
    int whiteScore{getScore(gameBoard, constants::WHITE)};

    std::cout << "Black score is " << blackScore << "\n";
    std::cout << "White score is " << whiteScore << "\n";

    if (blackScore > whiteScore)
    {
        std::cout << "Black wins!\n";
    }
    else if (whiteScore > blackScore)
    {
        std::cout << "White wins!\n";
    }
    else
    {
        std::cout << "It's a tie!\n";
    }

    std::cout << "\nDo you want to play again? (y/n): ";

    char replay{};
    std::cin >> replay;

    while (replay != 'y' && replay != 'Y' && replay != 'n' && replay != 'N')
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Wrong input. Please select an option (y/n): ";
        std::cin >> replay;
    }

    system("CLS");
    if (replay == 'y' || replay == 'Y')
    {
        playGame();
    }
    else
    {
        mainScreen();
    }
}