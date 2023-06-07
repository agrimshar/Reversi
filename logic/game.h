#pragma once

bool isPositionInBounds(int row, int col);

bool isTileEmpty(char gameBoard[constants::BOARD_SIZE][constants::BOARD_SIZE], int row, int col);

bool isGameOver(char board[constants::BOARD_SIZE][constants::BOARD_SIZE]);

bool isEmptyTileLegalInDirection(char board[constants::BOARD_SIZE][constants::BOARD_SIZE], char player, int row, int col, int dx, int dy);

bool isNotEmptyTileLegalInDirection(char board[constants::BOARD_SIZE][constants::BOARD_SIZE], char player, int row, int col, int dx, int dy);

bool isValidMoveEmptyTile(char gameBoard[constants::BOARD_SIZE][constants::BOARD_SIZE], char player, int row, int col);

bool isValidMoveNotEmptyTile(char gameBoard[constants::BOARD_SIZE][constants::BOARD_SIZE], char player, int row, int col);

bool isPlayerMovePossible(char board[constants::BOARD_SIZE][constants::BOARD_SIZE], char player);

int getScore(char board[constants::BOARD_SIZE][constants::BOARD_SIZE], char player);

void switchPlayerTurn(bool *playerOneTurn, bool *playerTwoTurn);