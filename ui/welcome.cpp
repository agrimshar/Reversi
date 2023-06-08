#include "welcome.h"
#include "playGame.h"

#include <iostream>
#include <cstdio>
#include <limits>

void welcome()
{
    std::cout << "______                        _\n";
    std::cout << "| ___ \\                      (_)\n";
    std::cout << "| |_/ /_____   _____ _ __ ___ _ \n";
    std::cout << "|    // _ \\ \\ / / _ \\ '__/ __| |\n";
    std::cout << "| |\\ \\  __/\\ V /  __/ |  \\__ \\ |\n";
    std::cout << "\\_| \\_\\___| \\_/ \\___|_|  |___/_|\n\n";
}

void introMessage()
{
    int selection;

    std::cout << "Welcome to Reversi! Reversi is a strategy board game for two players, played on an 8x8 uncheckered board. This is a recreation of the game coded in C++\n\n";

    std::cout << "Please choose one of the following options:\n";
    std::cout << "1. Play Game (2 Players)\n";
    std::cout << "2. Play Against AI (unavailable)\n";
    std::cout << "3. How to Play\n";
    std::cout << "4. Credits\n";
    std::cout << "5. Quit\n";

    std::cout << "\n";

    std::cout << "Please select an option (1-5): ";
    std::cin >> selection;

    while (selection < 1 || selection > 5)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Wrong input. Please select an option (1-5): ";
        std::cin >> selection;
    }

    system("CLS");

    switch (selection)
    {
    case 1:
        playGame();
        break;
    case 2:
        // playAi();
        break;
    case 3:
        // instructions();
        break;
    case 4:
        // credits();
        break;
    case 5:
        exit(0);
    }
}

void mainScreen()
{
    welcome();
    introMessage();
}