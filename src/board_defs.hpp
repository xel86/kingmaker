#pragma once

typedef unsigned long long U64;

#define NAME "KINGMAKER 1.0"
#define BRD_SQ_NUM 120
#define MAXMOVES 2048
#define ORIGIN_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

enum PieceType { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK };
enum File : int { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE };
enum Rank : int { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE };

enum PawnType { WHITE, BLACK, BOTH };

enum Square : int {
    A1 = 21, B1, C1, D1, E1, F1, G1, H1, 
    A2 = 31, B2, C2, D2, E2, F2, G2, H2, 
    A3 = 41, B3, C3, D3, E3, F3, G3, H3, 
    A4 = 51, B4, C4, D4, E4, F4, G4, H4, 
    A5 = 61, B5, C5, D5, E5, F5, G5, H5, 
    A6 = 71, B6, C6, D6, E6, F6, G6, H6, 
    A7 = 81, B7, C7, D7, E7, F7, G7, H7, 
    A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ, OFFBOARD
};

//4 bits representing possible castles
enum CastleState { WKCastle = 1, WQCastle = 2, BKCastle = 4, BQCastle = 8 };

struct BOARD_HISTORY {
    unsigned move;
    unsigned castleAllowed;
    unsigned enPassant;
    unsigned fiftyMove;
    U64 boardState;
};

struct BOARD {
    int pieces[BRD_SQ_NUM];

    U64 pawns[3];
    unsigned KingSq[2];

    unsigned side;
    unsigned enPassant;
    unsigned fiftyMove; //if fifty moves have occured with no captures, draw game
    unsigned ply;
    unsigned plyCount; //total half moves played
    unsigned castleState;

    //state of the board represented by the XOR's of different hash keys for 
    //pieces, white/black move, and castle state for each square
    U64 boardState;
    
    unsigned pieceNum[13];
    unsigned nonpawnPieces[3];
    unsigned majorPieces[3]; //rook, queen
    unsigned minorPieces[3]; //bishop, knight

    BOARD_HISTORY history[MAXMOVES];

    //piece list (pList[wR][0] = A1; pList[wR][1] = H1)
    int pList[13][10];

};

//macro to give file and rank and returns index of square for the 120sq board
#define FR2SQ(f,r) ( (21 + (f) ) + ( (r) * 10) )
#define SQ64(sq120) Sq120ToSq64[(sq120)]
#define SQ120(sq64) Sq64ToSq120[(sq64)]
#define CLEARBIT(bb,sq) ((bb) &= ClearMask[(sq)])
#define SETBIT(bb,sq) ((bb) |= SetMask[(sq)])

extern int Sq120ToSq64[BRD_SQ_NUM];
extern int Sq64ToSq120[64];
extern U64 SetMask[64];
extern U64 ClearMask[64];
extern U64 PieceKeys[13][120];
extern U64 SideKey;
extern U64 CastleKeys[16];
extern char PieceChar[];
extern char SideChar[];
extern char RankChar[];
extern char FileChar[];


extern void AllInit();
extern void printBitBoard(U64 bb);
extern int popBit(U64 *bb);
extern int countBits(U64 bb);
extern U64 generateBoardState(const BOARD *bb);
extern void ResetBoard(BOARD *bb);
extern int parseFEN(char *fen, BOARD *bb);
extern void printBoard(const BOARD *bb);