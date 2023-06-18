#include "credits.h"
#include "welcome.h"

#include <iostream>

void printCredits()
{
    printf("Made by @agrimshar\n\n");
}

void backToMainScreenCredits()
{
    printf("Back to home screen. ");
    system("pause");
    system("CLS");
    mainScreen();
}

void credits()
{
    printCredits();
    backToMainScreenCredits();
}