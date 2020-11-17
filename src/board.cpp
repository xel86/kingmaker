#include <stdio.h>
#include <iostream>
#include "board_defs.hpp"
#include "debug_helper.hpp"

int parseFEN(char *fen, BOARD *bb){
    ASSERT(fen!=NULL);
    ASSERT(bb!=NULL);

    int rank = RANK_8;
    int file = FILE_A;
    int piece = 0;
    int count = 0;
    int i =0;
    int sq64 = 0;
    int sq120 = 0;
    ResetBoard(bb);

    while((rank >= RANK_1) && *fen){
        count = 1;
        switch(*fen) {
            case 'p': piece = bP; break;
            case 'r': piece = bR; break;
            case 'n': piece = bN; break;
            case 'b': piece = bB; break;
            case 'k': piece = bK; break;
            case 'q': piece = bQ; break;
            case 'P': piece = wP; break;
            case 'R': piece = wR; break;
            case 'N': piece = wN; break;
            case 'B': piece = wB; break;
            case 'K': piece = wK; break;
            case 'Q': piece = wK; break;

            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                piece = EMPTY;
                count = *fen - '0';
                break;
            
            case '/':
            case ' ':
                rank--;
                file = FILE_A;
                fen++;
                continue;
            
            default:
                std::cout << "error parsing FEN" << std::endl;
                return -1;
        }

        for(i = 0; i < count; i++){
            sq64 = rank * 8 + file;
            sq120 = SQ120(sq64);
            if(piece != EMPTY){
                bb->pieces[sq120] = piece;
            }
            file++;
        }
        fen++;
    }

    ASSERT(*fen == 'w' || *fen == 'b');
    
    bb->side = (*fen == 'w') ? WHITE : BLACK;
    fen+=2;

    for(i = 0; i < 4; i++){
        if(*fen == ' ') {
            break;
        }
        switch(*fen){
            case 'K': bb->castleState |= WKCastle; break;
            case 'Q': bb->castleState |= WQCastle; break;
            case 'k': bb->castleState |= BKCastle; break;
            case 'q': bb->castleState |= BQCastle; break;
            default: break;
        }
        fen++;
    }
    fen++;

    ASSERT(bb->castleState>= 0 && bb->castleState <= 15);
    if(*fen != '-'){
        file = fen[0] - 'a';
        rank = fen[1] - '1';

        ASSERT(file>=FILE_A && file <= FILE_H);
        ASSERT(rank>=RANK_1 && rank <= RANK_8);

        bb->enPassant = FR2SQ(file,rank);
    }

    bb->boardState = generateBoardState(bb);
    return 0;
}

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

void printBoard(const BOARD *bb){
    int sq,file,rank,piece;
    std::cout << "\nGame Board:" << std::endl << std::endl;
    
    for(rank = RANK_8; rank >= RANK_1; rank--){
        std::cout << rank+1 << " ";
        for(file = FILE_A; file <= FILE_H; file++){
            sq = FR2SQ(file,rank);
            piece = bb->pieces[sq];
            printf("%3c", PieceChar[piece]);
        }
        std::cout << "\n";
    }
    std::cout << "\n  ";
    for(file = FILE_A; file <= FILE_H; file++){
        printf("%3c", 'a'+file);
    }
    std::cout << "\n";
    std::cout << "side: " << SideChar[bb->side] << std::endl;
    std::cout << "enPassant: " << bb->enPassant << std::endl;
    printf("castle: %c%c%c%c\n",
        bb->castleState & WKCastle?'K':'-',
        bb->castleState & WQCastle?'Q':'-',
        bb->castleState & BKCastle?'k':'-',
        bb->castleState & BQCastle?'q':'-'
        );
    std::cout << "BoardState Key: " << bb->boardState << std::endl;
}