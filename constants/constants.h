#pragma once

namespace constants
{
    const int BOARD_SIZE = 8;
    const char WHITE{'W'};
    const char BLACK{'B'};
    const char EMPTY{' '};
    const char VALID{'O'};
    const int DIRECTIONS[8][2]{{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};
}