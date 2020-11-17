#include "board_defs.hpp"
#include "debug_helper.hpp"

U64 generateBoardState(const BOARD *bb){
    int sq = 0;
    U64 stateKey = 0;
    int piece = EMPTY;

    for(sq = 0; sq < BRD_SQ_NUM; ++sq){
        piece = bb->pieces[sq];
        if(piece != NO_SQ && piece != EMPTY && piece != OFFBOARD){
            ASSERT(piece >= wP && piece <= bK);
            stateKey ^= PieceKeys[piece][sq];
        }
    }

    if(bb->side == WHITE){
        stateKey ^= SideKey;
    }

    if(bb->enPassant != NO_SQ){
        ASSERT(bb->enPassant >= 0 && bb->enPassant<BRD_SQ_NUM);
        stateKey ^= PieceKeys[EMPTY][bb->enPassant];
    }

    ASSERT(bb->castleState >= 0 && bb->castleState<=15);
    stateKey ^= CastleKeys[bb->castleState];
    return stateKey;
}