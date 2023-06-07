#pragma once

void printBoard(char board[constants::BOARD_SIZE][constants::BOARD_SIZE]);

void printLegalMove(char board[constants::BOARD_SIZE][constants::BOARD_SIZE], int row, int col);

void placeTile(char board[constants::BOARD_SIZE][constants::BOARD_SIZE], char playerColor, int *row, int *col);

void flipTiles(char gameBoard[constants::BOARD_SIZE][constants::BOARD_SIZE], char player, int row, int col);

void makeMove(char board[constants::BOARD_SIZE][constants::BOARD_SIZE], char player);