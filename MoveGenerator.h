//
//  MoveGenerator.h
//  ChineseChess
//
//  Created by 杨子健 on 15/5/14.
//  Copyright (c) 2015年 Young. All rights reserved.
//

#ifndef __ChineseChess__MoveGenerator__
#define __ChineseChess__MoveGenerator__
#include "define.h"

class CMoveGenerator
{
public:
    CMoveGenerator();
    ~CMoveGenerator();
    //用以检查一个走法是否合法的静态函数
    static bool IsValidMove(BYTE position[10][9],int nFromX,int nFromY, int nToX,int nToY);
    //产生给定棋盘上的所有合法的走法
    int CreatePossibleMove(BYTE position[10][9],int nPly,int nSide);
    //存放 CreatePosiibleMove 产生的所有走法的队列
    CHESSMOVE m_MoveList[8][80];
protected:
    //在m_MoveList中插入一个走法
    int AddMove(int nFromX,int nToX,int nFromY,int nToY,int nPly);
    //产生给定棋盘上的给定位置上的将/帅的走法
    void Gen_KingMove(BYTE position[10][9],int i,int j,int nPly);
    //产生给定棋盘上的给定位置上的红仕的走法
    void Gen_RBishopMove(BYTE position[10][9],int i,int j,int nPly);
    //产生给定棋盘上的给定位置上的黑士的走法
    void Gen_BBishopMove(BYTE position[10][9],int i,int j,int nPly);
    //产生给定棋盘上的给定位置上的相/象的走法
    void Gen_ElephantMove(BYTE position[10][9],int i,int j,int nPly);
    //产生给定棋盘上的给定位置上的马的走法
    void Gen_HorseMove(BYTE position[10][9],int i,int j,int nPly);
    //产生给定棋盘上的给定位置上的车的走法
    void Gen_CarMove(BYTE position[10][9],int i,int j,int nPly);
    //产生给定棋盘上的给定位置上的红卒的走法
    void Gen_RPawnMove(BYTE position[10][9],int i,int j,int nPly);
    //产生给定棋盘上的给定位置上的黑兵的走法
    void Gen_BPawnMove(BYTE position[10][9],int i,int j,int nPly);
    //产生给定棋盘上的给定位置上的炮的走法
    void Gen_CanonMove(BYTE position[10][9],int i,int j,int nPly);
    int m_nMoveCount;//记录 m_nMoveList中走法的数量
};

#endif /* defined(__ChineseChess__MoveGenerator__) */
