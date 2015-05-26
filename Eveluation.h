#ifndef __ChineseChess__Eveluation__
#define __ChineseChess__Eveluation__

typedef char BYTE;
#include <stdio.h>
//这一组宏定义了每种棋子的基本价值
//兵100，士250，象250，车500，马350，炮350，将10000
#define BASEVALUE_PAWN 100
#define BASEVALUE_BISHOP 250
#define BASEVALUE_ELEPHANT 250
#define BASEVALUE_CAR 500
#define BASEVALUE_HORSE 350
#define BASEVALUE_CANON 350
#define BASEVALUE_KING 10000
//这一组宏定义了各种棋子灵活性
//也就是每多一个可走位置应加上的分值
//兵15，士1，象1，车6，马12，炮6，将0
#define FLEXIBILITY_PAWN 15
#define FLEXIBILITY_BISHOP 1
#define FLEXIBILITY_ELEPHANT 1
#define FLEXIBILITY_CAR 6
#define FLEXIBILITY_HORSE 12
#define FLEXIBILITY_CANON 6
#define FLEXIBILITY_KING 0
class CEveluation  //估值类
{
public:
    CEveluation();
    virtual ~CEveluation();
    //估值函数，对传入的棋盘打分，BIsRedTurn标明轮到谁走棋
    virtual int Eveluat(BYTE position[10][9], bool BIsRedTurn);
protected:
    //列举与指定位置的棋子相关的棋子
    int GetRelatePiece(BYTE position[10][9], int j, int i);
    //判断位置From的棋子是否能走到位置To
    bool CanTouch(BYTE position[10][9], int nFromX, int nFromY, int nToX, int nToY);
    //将一个位置加入相关位置的队列
    int AddPiont(int x, int y);
    int m_BaseValue[15];//存放棋子基本价值的数组
    int m_FlexValue[15];//存放棋子灵活性分数的数组
    short m_AttackPos[10][9];//存放每一位置被威胁的信息
    BYTE m_GuardPos[10][9];//存放每一位置被保护的信息
    BYTE m_FlexibilityPos[10][9];//存放每一位置上的棋子的灵活性分数
    int m_ChessValue[10][9];//存放每一位置上的棋子的总价值
    int m_nPosCount;//记录一个棋子的相关位置个数
    int RelatePos[20];//记录一个棋子相关位置的数组
};
#endif /* defined(__ChineseChess__Eveluation__) */
