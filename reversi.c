/**
 * @file reversi.c
 * @author Agrim Sharma
 * @brief This file is used for APS105 Lab 8. 2023W version
 * @date 2023-03-14
 *
 */

// DO NOT REMOVE THE FOLLOWING LINE
#if !defined(TESTER_P1) && !defined(TESTER_P2)
// DO NOT REMOVE THE ABOVE LINE
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// DO NOT REMOVE THE FOLLOWING LINE
#endif
// DO NOT REMOVE THE ABOVE LINE

void initializeBoard(char board[][26], int n)
{
    board[n / 2][n / 2] = 'W';
    board[n / 2][n / 2 - 1] = 'B';
    board[n / 2 - 1][n / 2 - 1] = 'W';
    board[n / 2 - 1][n / 2] = 'B';
}

void printBoard(char board[][26], int n)
{
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (i == 0 && j == 0)
            {
                printf("  ");
            }
            else if (i == 0)
            {
                printf("%c", 96 + j);
            }
            else if (j == 0)
            {
                printf("%c ", 96 + i);
            }
            else
            {
                printf("%c", board[i - 1][j - 1]);
            }
        }
        printf("\n");
    }
}

bool positionInBounds(int n, int row, int col)
{
    // Checks if row and col is within the size of grid
    if (row < 0 || row > n - 1 || col < 0 || col > n - 1)
    {
        return false;
    }

    return true;
}

bool playerLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol)
{
    int currentRow = row + deltaRow;
    int currentCol = col + deltaCol;

    // if opposite  colour is found adjacent to input, potential valid move
    if (board[currentRow][currentCol] != colour && board[currentRow][currentCol] != 'U' && positionInBounds(n, currentRow, currentCol))
    {
        currentRow += deltaRow;
        currentCol += deltaCol;

        while (positionInBounds(n, currentRow, currentCol))
        {
            // if sees an opposite colour, function will continue looping
            // if 'U' is found, potential move
            if (board[currentRow][currentCol] == 'U')
            {
                return true;
            } // if colour  is found, move is not valid
            else if (board[currentRow][currentCol] == colour)
            {
                return false;
            }

            // keeps looping until condition is met, or search goes out of bounds
            currentRow += deltaRow;
            currentCol += deltaCol;
        }
    }

    return false;
}

bool emptyLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol)
{
    int currentRow = row + deltaRow;
    int currentCol = col + deltaCol;

    // if opposite  colour is found adjacent to input, potential valid move
    if (board[currentRow][currentCol] != colour && board[currentRow][currentCol] != 'U' && positionInBounds(n, currentRow, currentCol))
    {
        currentRow += deltaRow;
        currentCol += deltaCol;

        while (positionInBounds(n, currentRow, currentCol))
        {
            // if sees an opposite colour, function will continue looping
            // if 'U' is found, not valid move
            if (board[currentRow][currentCol] == 'U')
            {
                return false;
            } // if colour  is found, move is valid
            else if (board[currentRow][currentCol] == colour)
            {
                return true;
            }

            // keeps looping until condition is met, or search goes out of bounds
            currentRow += deltaRow;
            currentCol += deltaCol;
        }
    }

    return false;
}

bool isValidMove(char board[][26], int n, int row, int col, char player)
{
    if (!positionInBounds(n, row, col))
    {
        return false;
    }

    if (board[row][col] != 'U')
    {
        return false;
    }

    if (emptyLegalInDirection(board, n, row, col, player, -1, -1))
    {
        return true;
    }
    if (emptyLegalInDirection(board, n, row, col, player, -1, 0))
    {
        return true;
    }
    if (emptyLegalInDirection(board, n, row, col, player, -1, 1))
    {
        return true;
    }
    if (emptyLegalInDirection(board, n, row, col, player, 0, -1))
    {
        return true;
    }
    if (emptyLegalInDirection(board, n, row, col, player, 0, 1))
    {
        return true;
    }
    if (emptyLegalInDirection(board, n, row, col, player, 1, -1))
    {
        return true;
    }
    if (emptyLegalInDirection(board, n, row, col, player, 1, 0))
    {
        return true;
    }
    if (emptyLegalInDirection(board, n, row, col, player, 1, 1))
    {
        return true;
    }

    return false;
}

bool isLeafNode(char board[][26], char player, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (isValidMove(board, n, i, j, player))
            {
                return false;
            }
        }
    }
    return true;
}

int max(int a, int b) { return a > b ? a : b; }

int min(int a, int b) { return a < b ? a : b; }

int evaluateBoard(char board[][26], char player, int n)
{
    int maxEvaluation = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] == player)
            {
                if ((i == 0 || i == n - 1) && (j == 0 || j == n - 1))
                {
                    maxEvaluation += 63;
                }
                else if ((i == 0 || i == n - 1) && (j == 1 || j == n - 2))
                {
                    maxEvaluation -= 1;
                }
                else if ((i == 0 || i == n - 1) && (j == 2 || j == n - 3))
                {
                    maxEvaluation += 15;
                }
                else if ((i == 0 || i == n - 1) && (j == 3 || j == n - 4))
                {
                    maxEvaluation += 13;
                }
                else if ((i == 1 || i == n - 2) && (j == 0 || j == n - 1))
                {
                    maxEvaluation += 0;
                }
                else if ((i == 1 || i == n - 2) && (j == 1 || j == n - 2))
                {
                    maxEvaluation -= 7;
                }
                else if ((i == 1 || i == n - 2) && (j == 2 || j == n - 3))
                {
                    maxEvaluation += 2;
                }
                else if ((i == 1 || i == n - 2) && (j == 3 || j == n - 4))
                {
                    maxEvaluation += 3;
                }
                else if ((i == 2 || i == n - 3) && (j == 0 || j == n - 1))
                {
                    maxEvaluation += 1;
                }
                else if ((i == 2 || i == n - 3) && (j == 1 || j == n - 2))
                {
                    maxEvaluation -= 1;
                }
                else if ((i == 2 || i == n - 3) && (j == 2 || j == n - 3))
                {
                    maxEvaluation += 14;
                }
                else if ((i == 2 || i == n - 3) && (j == 3 || j == n - 4))
                {
                    maxEvaluation += 10;
                }
                else if ((i == 3 || i == n - 4) && (j == 0 || j == n - 1))
                {
                    maxEvaluation += 12;
                }
                else if ((i == 3 || i == n - 4) && (j == 1 || j == n - 2))
                {
                    maxEvaluation -= 1;
                }
                else if ((i == 3 || i == n - 4) && (j == 0 || j == n - 1))
                {
                    maxEvaluation += 10;
                }
                else if ((i == 3 || i == n - 4) && (j == 0 || j == n - 1))
                {
                    maxEvaluation += 8;
                }
                else if ((i == 0 || i == n - 1) || (j == 0 || j == n - 1))
                {
                    maxEvaluation += 7;
                }
                else
                {
                    maxEvaluation += 6;
                }

                if (playerLegalInDirection(board, n, i, j, player, -1, -1))
                {
                    maxEvaluation += 2;
                }
                if (playerLegalInDirection(board, n, i, j, player, -1, 0))
                {
                    maxEvaluation += 2;
                }
                if (playerLegalInDirection(board, n, i, j, player, -1, 1))
                {
                    maxEvaluation += 2;
                }
                if (playerLegalInDirection(board, n, i, j, player, 0, -1))
                {
                    maxEvaluation += 2;
                }
                if (playerLegalInDirection(board, n, i, j, player, 0, 1))
                {
                    maxEvaluation += 2;
                }
                if (playerLegalInDirection(board, n, i, j, player, 1, -1))
                {
                    maxEvaluation += 2;
                }
                if (playerLegalInDirection(board, n, i, j, player, 1, 0))
                {
                    maxEvaluation += 2;
                }
                if (playerLegalInDirection(board, n, i, j, player, 1, 1))
                {
                    maxEvaluation += 2;
                }
            }
        }
    }

    return maxEvaluation;
}

int flip(char board[][26], int row, int col, int n, char player)
{
    int flips = 0;
    board[row][col] = player;

    for (int adjacentRow = row - 1; adjacentRow <= row + 1; adjacentRow++) // checking all the squares adjacent to potential square
    {
        for (int adjacentCol = row - 1; adjacentCol <= col + 1; adjacentCol++)
        {
            if (emptyLegalInDirection(board, n, row, col, player, adjacentRow - row, adjacentCol - col)) // if legal move
            {
                int currentRow = adjacentRow;
                int currentCol = adjacentCol;

                while (board[currentRow][currentCol] != player)
                {
                    board[currentRow][currentCol] = player;
                    currentRow += adjacentRow - row;
                    currentCol += adjacentCol - col;
                    flips++;
                }
            }
        }
    }
    return flips;
}

int minimax(char board[][26], char player, int depth, int n, int alpha, int beta, bool maximimizedPlayer)
{
    if (depth == 0 || isLeafNode(board, player, n))
    {
        return evaluateBoard(board, player, n);
    }

    if (maximimizedPlayer)
    {
        int temp = -1;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (isValidMove(board, n, i, j, player))
                {
                    char tempBoard[26][26];
                    memcpy(tempBoard, board, 26 * 26 * sizeof(char));
                    int flips = flip(tempBoard, i, j, n, player);
                    temp = max(temp, minimax(tempBoard, player, depth - 1, n, alpha, beta, false));
                    alpha = max(alpha, temp);
                    if (beta <= alpha)
                    {
                        break;
                    }
                }
            }
        }
        return temp;
    }
    else
    {
        int temp = 99999;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (isValidMove(board, n, i, j, player))
                {
                    char tempBoard[26][26];
                    memcpy(tempBoard, board, 26 * 26 * sizeof(char));
                    int flips = flip(tempBoard, i, j, n, player);
                    temp = min(temp, minimax(tempBoard, player, depth - 1, n, alpha, beta, true));
                    beta = min(beta, temp);
                    if (beta <= alpha)
                    {
                        break;
                    }
                }
            }
        }
        return temp;
    }
}

int makeMove(char board[][26], int n, char turn, int *row, int *col)
{
    int maximumPoints = 0;
    *row = -1;
    *col = -1;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (isValidMove(board, n, i, j, turn))
            {
                char temp[26][26];
                memcpy(temp, board, 26 * 26 * sizeof(char));
                int points = flip(temp, i, j, n, turn);
                points = minimax(temp, turn, 4, n, -1, 99999, true);

                if (points > maximumPoints)
                {
                    maximumPoints = points;
                    *row = i;
                    *col = j;
                }
            }
        }
    }

    return 0;
}

// REMOVE
bool search(char board[][26], int n, char turn)
{
    for (int boardRow = 0; boardRow < n; boardRow++) // looping through main grid
    {
        for (int boardCol = 0; boardCol < n; boardCol++)
        {
            if (board[boardRow][boardCol] == 'U') // Potential legal move square
            {
                for (int adjacentRow = boardRow - 1; adjacentRow <= boardRow + 1; adjacentRow++) // checking all the squares adjacent to potential square
                {
                    for (int adjacentCol = boardCol - 1; adjacentCol <= boardCol + 1; adjacentCol++)
                    {
                        if (emptyLegalInDirection(board, n, boardRow, boardCol, turn, adjacentRow - boardRow, adjacentCol - boardCol))
                        {
                            return true;
                        } // if legal move
                    }
                }
            }
        }
    }
    return false;
}
bool isValidPlayerMove(char board[][26], int n, char colour, int row, int col)
{
    for (int adjacentRow = row - 1; adjacentRow <= row + 1; adjacentRow++) // checking all the squares adjacent to potential square
    {
        for (int adjacentCol = col - 1; adjacentCol <= col + 1; adjacentCol++)
        {
            if (board[row][col] != colour)
            {
                if (emptyLegalInDirection(board, n, row, col, colour, adjacentRow - row, adjacentCol - col))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

int getScore(char board[][26], char colour, int n)
{
    int score = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] == colour)
            {
                score++;
            }
        }
    }

    return score;
}

void searchAI(char board[][26], int n, char turn, int *row, int *col)
{
    // Find best move using score AI
    int maxFlips = 0;
    for (int boardRow = 0; boardRow < n; boardRow++) // looping through main grid
    {
        for (int boardCol = 0; boardCol < n; boardCol++)
        {
            if (board[boardRow][boardCol] == 'U') // Potential legal move square
            {
                int flips = 0;
                for (int adjacentRow = boardRow - 1; adjacentRow <= boardRow + 1; adjacentRow++) // checking all the squares adjacent to potential square
                {
                    for (int adjacentCol = boardCol - 1; adjacentCol <= boardCol + 1; adjacentCol++)
                    {
                        if (emptyLegalInDirection(board, n, boardRow, boardCol, turn, adjacentRow - boardRow, adjacentCol - boardCol)) // if legal move
                        {
                            int currentRow = adjacentRow;
                            int currentCol = adjacentCol;

                            while (board[currentRow][currentCol] != turn)
                            {
                                currentRow += adjacentRow - boardRow;
                                currentCol += adjacentCol - boardCol;
                                flips++;
                            }
                        }
                    }
                }

                if (flips > maxFlips)
                {
                    maxFlips = flips;
                    *row = boardRow;
                    *col = boardCol;
                }
            }
        }
    }
}

//*******************************************************
// Note: Please only put your main function below
// DO NOT REMOVE THE FOLLOWING LINE
#ifndef TESTER_P2
// DO NOT REMOVE THE ABOVE LINE

int main(void)
{
    int boardDimension;
    char computerColour, playerColour;

    char board[][26] = {{'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'}, {'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'}, {'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'}, {'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'}, {'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'}, {'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'}, {'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'}, {'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'}, {'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'}, {'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'}, {'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'}, {'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'}, {'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'}, {'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'}, {'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'}, {'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'}, {'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'}, {'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'}, {'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'}, {'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'}, {'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'}, {'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'}, {'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'}, {'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'}, {'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'}, {'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'}};

    printf("Enter the board dimension: ");
    scanf("%d", &boardDimension);
    while (boardDimension < 2 || boardDimension > 26 || boardDimension % 2 == 1)
    {
        printf("Enter the board dimension: ");
        scanf(" %d", &boardDimension);
    }

    printf("Computer plays (B/W): ");
    scanf(" %c", &computerColour);
    while (computerColour != 'W' && computerColour != 'B')
    {
        printf("Computer plays (B/W): ");
        scanf(" %c", &computerColour);
    }

    initializeBoard(board, boardDimension);

    printBoard(board, boardDimension);

    if (computerColour == 'W')
    {
        char computer = 'W';
        char human = 'B';

        bool one = search(board, boardDimension, human);
        bool two = search(board, boardDimension, computer);

        int computerScore = getScore(board, computer, boardDimension);
        int humanScore = getScore(board, human, boardDimension);

        while (one || two)
        {
            one = search(board, boardDimension, human);
            two = search(board, boardDimension, computer);
            char cRow, cCol;
            int dRow, dCol, AiRow, AiCol;

            if (one)
            {
                printf("Enter move for colour %c (RowCol): ", human);
                scanf(" %c%c", &cRow, &cCol);

                dRow = cRow - 'a';
                dCol = cCol - 'a';
                if (isValidPlayerMove(board, boardDimension, human, dRow, dCol))
                {
                    board[dRow][dCol] = human;
                    int score = flip(board, dRow, dCol, boardDimension, human);
                    humanScore += score + 1;
                    computerScore -= score;
                    printBoard(board, boardDimension);
                }
                else
                {
                    printf("Invalid move.\n%c player wins.", computer);
                    return 0;
                }
            }
            else
            {
                if ((humanScore + computerScore != boardDimension * boardDimension) && (getScore(board, human, boardDimension) != 0) && (one || two))
                {
                    printf("%c player has no valid move.\n", human);
                }
            }

            one = search(board, boardDimension, human);
            two = search(board, boardDimension, computer);

            if (two)
            {
                int score = makeMove(board, boardDimension, computer, &AiRow, &AiCol);
                board[AiRow][AiCol] = computer;
                int garbage = flip(board, AiRow, AiCol, boardDimension, computer);
                humanScore -= score;
                computerScore += score + 1;
                printf("Computer places %c at %c%c.\n", computer, AiRow + 97, AiCol + 97);
                printBoard(board, boardDimension);
            }
            else
            {
                if ((humanScore + computerScore != boardDimension * boardDimension) && (getScore(board, computer, boardDimension) != 0) && (one || two))
                {
                    printf("%c player has no valid move.\n", computer);
                }
            }
        }

        if (computerScore > humanScore)
        {
            printf("%c player wins.", computer);
        }
        else if (humanScore > computerScore)
        {
            printf("%c player wins.", human);
        }
        else
        {
            printf("Draw!");
        }
    }
    else if (computerColour == 'B')
    {
        char computer = 'B';
        char human = 'W';

        bool one = search(board, boardDimension, human);
        bool two = search(board, boardDimension, computer);

        int computerScore = getScore(board, computer, boardDimension);
        int humanScore = getScore(board, human, boardDimension);

        while (one || two)
        {
            one = search(board, boardDimension, human);
            two = search(board, boardDimension, computer);
            char cRow, cCol;
            int dRow, dCol, AiRow, AiCol;

            if (two)
            {
                int score = makeMove(board, boardDimension, computer, &AiRow, &AiCol);
                board[AiRow][AiCol] = computer;
                int garbage = flip(board, AiRow, AiCol, boardDimension, computer);
                humanScore -= score;
                computerScore += score + 1;
                printf("Computer places %c at %c%c.\n", computer, AiRow + 97, AiCol + 97);
                printBoard(board, boardDimension);
            }
            else
            {
                if ((humanScore + computerScore != boardDimension * boardDimension) && (getScore(board, computer, boardDimension) != 0) && (one || two))
                {
                    printf("%c player has no valid move.\n", computer);
                }
            }

            one = search(board, boardDimension, human);
            two = search(board, boardDimension, computer);

            if (one)
            {

                printf("Enter move for colour %c (RowCol): ", human);
                scanf(" %c%c", &cRow, &cCol);

                dRow = cRow - 'a';
                dCol = cCol - 'a';
                if (isValidPlayerMove(board, boardDimension, human, dRow, dCol))
                {
                    board[dRow][dCol] = human;
                    int score = flip(board, dRow, dCol, boardDimension, human);
                    humanScore += score + 1;
                    computerScore -= score;
                    printBoard(board, boardDimension);
                }
                else
                {
                    printf("Invalid move.\n%c player wins.", computer);
                    return 0;
                }
            }
            else
            {
                if ((humanScore + computerScore != boardDimension * boardDimension) && (getScore(board, human, boardDimension) != 0) && (one || two))
                {
                    printf("%c player has no valid move.\n", human);
                }
            }
        }

        if (computerScore > humanScore)
        {
            printf("%c player wins.", computer);
        }
        else if (humanScore > computerScore)
        {
            printf("%c player wins.", human);
        }
        else
        {
            printf("Draw!");
        }
    }

    return 0;
}

// DO NOT REMOVE THE FOLLOWING LINE
#endif
// DO NOT REMOVE THE ABOVE LINE
//*******************************************************
