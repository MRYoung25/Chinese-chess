#ifndef ChineseChess_define_h
#define ChineseChess_define_h

typedef char BYTE;
#define NOCHESS 0   //There is no chess
#define B_KING      1//B_KING
#define B_CAR       2//B_CAR
#define B_HORSE     3//B_HORSE
#define B_CANON     4//B_CANON
#define B_BISHOP    5//B_BISHOP
#define B_ELEPHANT 6//B_ELEPHANT
#define B_PAWN      7//B_PAWN
#define B_BEGIN     B_KING
#define B_END       B_PAWN
#define R_KING      8//R_KING
#define R_CAR       9//R_CAR 
#define R_HORSE     10//R_HORSE
#define R_CANON     11//R_CANON
#define R_BISHOP    12//R_BISHOP
#define R_ELEPHANT 13//R_ELEPHANT 
#define R_PAWN      14//R_PAWN 
#define R_BEGIN     R_KING
#define R_END       R_PAWN
#define IsBlack(x)  ( (x) >= B_BEGIN && (x) <= B_END)  //judge the chess is black or not
#define IsRed(x)  ( (x) >= R_BEGIN && (x) <= R_END)  //judge the chess is red or not
//judge the two chess is the same color or not
#define IsSameSide(x,y)  ((IsBlack(x) && IsBlack(y)) || ( IsRed(x) && IsRed(y)))
//define the structure of chess position 
typedef struct _chessmanposition
{
    BYTE       x;
    BYTE       y;
}CHESSMANPOS;
//the structure of chess move

typedef struct _chessmove
{
    short             ChessID;  //mark the type of chess
    CHESSMANPOS From;           //origin location
    CHESSMANPOS To;             //destination
    int               Score;    //value
}CHESSMOVE;
#endif//
