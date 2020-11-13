#include <stdio.h>
#include "board_defs.hpp"

void ResetBoard(BOARD *bb){
    int index = 0;
    for(index = 0; index < BRD_SQ_NUM; ++index){
        bb->pieces[index] = OFFBOARD;
    }
    for(index = 0; index < 64; ++index){
        bb->pieces[SQ120(index)] = EMPTY;
    }

    for(index = 0; index < 3; ++index){
        bb->nonpawnPieces[index] = 0;
        bb->majorPieces[index] = 0;
        bb->minorPieces[index] = 0;
        bb->pawns[index] = 0ULL;
    }

    for(index = 0; index < 13; ++index){
        bb->pieceNum[index] = 0;
    }

    bb->KingSq[WHITE] = bb->KingSq[BLACK] = NO_SQ;
    bb->side = BOTH;
    bb->enPassant = NO_SQ;
    bb->fiftyMove = 0;
    bb->ply = 0;
    bb->plyCount = 0;
    bb->castleState = 0;
    bb->boardState = 0ULL;
}