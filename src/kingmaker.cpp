#include <iostream>
#include <iomanip>
#include "board_defs.hpp"
#include "debug_helper.hpp"

int main(){
    AllInit();
    BOARD board[1];

    parseFEN(ORIGIN_FEN, board);
    printBoard(board);
    return 0;
}