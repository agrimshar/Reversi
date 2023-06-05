#define n

#include <iostream>

const int BOARD_SIZE = 8;
const char WHITE{'W'};
const char BLACK{'B'};
const char EMPTY{'-'};
const char VALID{'O'};
const int DIRECTIONS[8][2]{{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};

#ifndef n
void printGraphicalBoard()
{
    /*Prints out game board*/

    printf("    1   2   3   4   5   6   7   8\n");
    printf("  +---+---+---+---+---+---+---+---+\n");
    printf("1 |   |   |   |   |   |   |   |   |\n");
    printf("  +---+---+---+---+---+---+---+---+\n");
    printf("2 |   |   |   |   |   |   |   |   |\n");
    printf("  +---+---+---+---+---+---+---+---+\n");
    printf("3 |   |   |   |   |   |   |   |   |\n");
    printf("  +---+---+---+---+---+---+---+---+\n");
    printf("4 |   |   |   |   |   |   |   |   |\n");
    printf("  +---+---+---+---+---+---+---+---+\n");
    printf("5 |   |   |   |   |   |   |   |   |\n");
    printf("  +---+---+---+---+---+---+---+---+\n");
    printf("6 |   |   |   |   |   |   |   |   |\n");
    printf("  +---+---+---+---+---+---+---+---+\n");
    printf("7 |   |   |   |   |   |   |   |   |\n");
    printf("  +---+---+---+---+---+---+---+---+\n");
    printf("8 |   |   |   |   |   |   |   |   |\n");
    printf("  +---+---+---+---+---+---+---+---+\n");
}
#endif

void printBoard(char board[BOARD_SIZE][BOARD_SIZE])
{
    /*Prints out array*/
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            std::cout << board[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void initializeBoard(char gameBoard[BOARD_SIZE][BOARD_SIZE])
{
    /*Initializing the games starting board in an array*/

    // Looping through the game board to populate it
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            // Empty tiles on board is filled with a space
            gameBoard[i][j] = EMPTY;

            // The center tiles start with 2 white and black pieces diagonal from eachother
            if ((i == 3 && j == 3) || (i == 4 && j == 4))
            {
                gameBoard[i][j] = WHITE;
            }
            else if ((i == 3 && j == 4) || (i == 4 && j == 3))
            {
                gameBoard[i][j] = BLACK;
            }
        }
    }
}

char getTileState(char board[BOARD_SIZE][BOARD_SIZE], int row, int col)
{
    /*Checking if a tile is empty or occupied by a black/white piece*/

    return board[row][col];
}

void printLegalMove(char board[BOARD_SIZE][BOARD_SIZE], int row, int col)
{
    board[row][col] = VALID;
}

bool isPositionInBounds(int row, int col)
{
    /*Checks if the inputted value is within the game board*/

    // Game array counts from 0 to BOARD_SIZE - 1
    if (row < 0 || row > BOARD_SIZE - 1 || col < 0 || col > BOARD_SIZE - 1)
    {
        return false;
    }

    return true;
}

bool isTileEmpty(char gameBoard[BOARD_SIZE][BOARD_SIZE], int row, int col)
{
    /*Checks if specific tile is empty*/

    if (gameBoard[row][col] == BLACK || gameBoard[row][col] == WHITE)
    {
        return false;
    }

    return true;
}

bool isGameOver(char board[BOARD_SIZE][BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (isTileEmpty(board, i, j))
            {
                return false;
            }
        }
    }

    return true;
}

bool isEmptyTileLegalInDirection(char board[BOARD_SIZE][BOARD_SIZE], char player, int row, int col, int dx, int dy)
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
    if (board[row][col] == EMPTY || board[row][col] == player)
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
        else if (board[row][col] == EMPTY)
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

bool isNotEmptyTileLegalInDirection(char board[BOARD_SIZE][BOARD_SIZE], char player, int row, int col, int dx, int dy)
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
    if (board[row][col] == EMPTY || board[row][col] == player)
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
        else if (board[row][col] == EMPTY)
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

bool isValidMoveEmptyTile(char gameBoard[BOARD_SIZE][BOARD_SIZE], char player, int row, int col)
{
    /*Checks if an empty tile has legal moves*/

    for (int i = 0; i < 8; i++)
    {
        if (isPositionInBounds(row, col) && isTileEmpty(gameBoard, row, col) && isEmptyTileLegalInDirection(gameBoard, player, row, col, DIRECTIONS[i][0], DIRECTIONS[i][1]))
        {
            return true;
        }
    }

    return false;
}

bool isValidMoveNotEmptyTile(char gameBoard[BOARD_SIZE][BOARD_SIZE], char player, int row, int col)
{
    /*Checks if non-empty tile creates legal moves*/

    for (int i = 0; i < 8; i++)
    {
        if (isPositionInBounds(row, col) && !isTileEmpty(gameBoard, row, col) && isNotEmptyTileLegalInDirection(gameBoard, player, row, col, DIRECTIONS[i][0], DIRECTIONS[i][1]))
        {
            return true;
        }
    }

    return false;
}

void placeTile(char board[BOARD_SIZE][BOARD_SIZE], char playerColor)
{
    /*Places tile onto the game board*/

    int row{}; // From row 0 - 7
    int col{}; // From col 0 - 7

    // Get input from user
    std::cout << "Where do you want to place your " << playerColor << " tile ([row] [col]): ";
    std::cin >> row >> col;

    // Check if input is in bounds
    while (!isValidMoveEmptyTile(board, playerColor, row, col))
    {
        std::cout << "Invalid move. Where do you want to place your tile ([row] [col]): ";
        std::cin >> row >> col;
    }

    board[row][col] = playerColor;
}

bool isPlayerMovePossible(char board[BOARD_SIZE][BOARD_SIZE], char player)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
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

int getScore(char board[BOARD_SIZE][BOARD_SIZE], char player)
{
    int score{};

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
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

int main()
{
    char gameBoard[BOARD_SIZE][BOARD_SIZE]{};
    bool playerOne = true;
    bool playerTwo = false;

    std::cout << "Black makes the first move.\n";
    initializeBoard(gameBoard);
    printBoard(gameBoard);
    std::cout << isGameOver(gameBoard) << "\n";

    do
    {
        if (playerOne && isPlayerMovePossible(gameBoard, BLACK))
        {
            placeTile(gameBoard, BLACK);
            printBoard(gameBoard);
            switchPlayerTurn(&playerOne, &playerTwo);
        }
        else if (playerTwo && isPlayerMovePossible(gameBoard, WHITE))
        {
            placeTile(gameBoard, WHITE);
            printBoard(gameBoard);
            switchPlayerTurn(&playerOne, &playerTwo);
        }
        std::cout << isGameOver(gameBoard) << "\n";
    } while (!isGameOver(gameBoard));

    std::cout << getScore(gameBoard, EMPTY) << "\n";

    return 0;
}