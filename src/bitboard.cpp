#include <iostream>
#include "board_defs.hpp"

const int BitTable[64] = {
    63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29,
    51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5,
    26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 58,
    20, 37, 17, 36, 8
};

//returns index of first activated bit starting at the least significant bit, then turns it to 0
int popBit(U64 *bb){
    U64 b = *bb ^ (*bb - 1);
    unsigned fold = (unsigned) ((b & 0xffffffff) ^ (b >> 32));
    *bb &= (*bb - 1);
    return BitTable[(fold * 0x783a9b23) >> 26];
}

int countBits(U64 bb) {
    int r;
    for(r = 0; bb; r++, bb &= bb-1);
    return r;
}

void printBitBoard(U64 bb){
    U64 shifter = 1ULL;
    int rank = 0;
    int file = 0;
    int sq = 0;
    int sq64 = 0;
    
    std::cout << "\n";
    for(rank = RANK_8; rank >= RANK_1; --rank){
        for(file = FILE_A; file <= FILE_H; ++file){
            sq = FR2SQ(file, rank); //120 based index
            sq64 = SQ64(sq); //64 based index

            //shifts 1ULL bit to 64 based index to check if bit is activated, meaning a piece is present
            if((shifter << sq64) & bb) std::cout << "X";
            else std::cout << "-";
        }
        std::cout << "\n";
    }
    std::cout << "\n\n";
}