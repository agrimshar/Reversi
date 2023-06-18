#include "instructions.h"
#include "welcome.h"

#include <iostream>

void printInstructions()
{
    printf("Reversi Rules\n\n");
    printf("1. The two colours are (B)lack and (W)hite, and black always plays first.\n\n");
    printf("2. The four squares in the middle of the board start with four counters already placed - white top left and bottom right; black top right and bottom left.\n\n");
    printf("3. A player without a move simply passes, and the other player keeps playing pieces until the first player can make a move again.\n\n");
    printf("4. The game is over when neight player has a legal move, or when the board is full.\n\n");
}

void backToMainScreenInstructions()
{
    printf("Back to home screen. ");
    system("pause");
    system("CLS");
    mainScreen();
}

void instructions()
{
    printInstructions();
    backToMainScreenInstructions();
}