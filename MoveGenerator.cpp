//
//  MoveGenerator.cpp
//  ChineseChess
//
//  Created by MRYoung on 15/5/14.
//  Copyright (c) 2015 Young. All rights reserved.
//

#include "MoveGenerator.h"
#include <cstdlib>

CMoveGenerator::CMoveGenerator()
{
}
//destructor
CMoveGenerator::~CMoveGenerator()
{
}



//判断局面position上，从From到To的走法是个否合法
//if legal，return TRUE，else return false
bool CMoveGenerator::IsValidMove(BYTE position[10][9],int nFromX,int nFromY, int nToX,int nToY)
{
    int i,j;
    int nMoveChessID,nTargetID;


    if(nFromY == nToY && nFromX == nToX)
        return false;//目的与源相同，非法
    nMoveChessID = position[nFromY][nFromX];
    nTargetID = position[nToY][nToX];
    
    if(IsSameSide(nMoveChessID,nTargetID))
        return false;//吃自己的棋，非法
    
    switch(nMoveChessID)
    {
        case B_KING:
            if(nTargetID == R_KING)  //判断是否老将见面
            {
                if(nFromX != nToX)  //横坐标相等否
                    return false;
                for(nFromY + 1; i < nToY; i++)
                    if(position[i][nFromX] != NOCHESS)
                        return false;//中间隔有棋子，返回false
            }
            else
            {
                if(nToY > 2||nToX > 5||nToX < 3)
                    return false;//目标点在九宫格之外
                if(abs(nFromY - nToY) + abs(nToX - nFromX) > 1)
                    return false;//将帅只走一步直线
            }
            break;
        case R_KING:       //红将
            if(nTargetID == B_KING)  //判断是否老将见面
            {
                if(nFromX != nToX)
                    return false;//两个不在同一列
                for(i = nFromY - 1;i > nToY;i--)
                    if(position[i][nFromX] != NOCHESS)
                        return false;//中间隔有棋子，返回false
            }
            else
            {
                if(nToY < 7||nToX > 5||nToX < 3)
                    return false;//目标点在九宫之外
                if(abs(nFromY - nToY) + abs(nToX - nFromX) > 1)
                    return false;//将帅只走一步直线
            }
            break;
        case R_BISHOP://红仕
            if(nToY < 7||nToX < 3)
                return false;//仕出九宫
            if(abs(nFromY - nToY) != 1||abs(nToX - nFromX) != 1)
                return false;//仕走斜线
            break;
        case B_BISHOP://黑士
            if(nToY > 2||nToX > 5||nToX < 3)
                return false;//士出九宫
            if(abs(nFromY - nToY) != 1||abs(nToX - nFromX) != 1)
                return false;//士走斜线
        case R_ELEPHANT://红相
            if(nToY < 5)
                return false;//象不能过河
            if(abs(nFromY - nToX) != 2||abs(nFromY - nToY) != 2)
                return false;//相走田字
            if(position[(nFromY + nToY) / 2][(nFromX + nToX) / 2] != NOCHESS)
                return false;//象眼被塞住了
            break;
        case B_ELEPHANT://黑象
            if(nToY > 4)
                return false;//象不能过河
            if(abs(nFromX - nToX) != 2||abs(nFromY - nToY) != 2)
                return false;//象走田字
            if(position[(nFromY + nToY) / 2][(nFromX + nToX) / 2] != NOCHESS)
                return false;//象眼被塞住了
            break;
        case B_PAWN://黑兵
            if(nToY < nFromY)
                return false;//兵不回头
            if(nFromY < 5 && nFromY == nToY)
                return false;//兵过河前只能直走
            if(nToY - nFromY +abs(nToX - nFromX) > 1)
                return false;//兵只走一步直线
            break;
        case R_PAWN://红卒
            if(nToY > nFromY)
                return false;//卒不回头
            if(nFromY > 4 && nFromY == nToY)
                return false;//卒过河前只能直走
            if(nFromY - nToY + abs(nToX - nFromX) > 1)
                return false;//卒只走一步直线
            break;
        case B_CAR://黑车
        case R_CAR://红车
            if(nFromY != nToY && nFromX != nToX)
                return false;//车走直线
            if(nFromY == nToY)
            {
                if(nFromX < nToX)
                {
                    for(i = nFromX + 1; i < nToX; i++)
                        if(position[nFromY][i] != NOCHESS)
                            return false;
                }
                else
                {
                    for(i = nToX + 1; i < nFromX; i++)
                        if(position[nFromY][i] != NOCHESS)
                            return false;
                }
            }
            else
            {
                if(nFromY < nToY)
                {
                    for(j = nFromY + 1; j < nToY; j++)
                        if(position[j][nFromX] != NOCHESS)
                            return false;
                }
                else
                {
                    for(j = nToY + 1; j < nFromY; j++)
                        if(position[j][nFromX] != NOCHESS)
                            return false;
                }
            }
            break;
        case B_HORSE://黑马
        case R_HORSE://红马
            if(!((abs(nToX - nFromX) == 1 && abs(nToY - nFromY) == 2)||(abs(nToX - nFromX) ==2&&abs(nToY - nFromY) == 1)))
                return false;//马走日字
            if(nToX - nFromX == 2)
            {
                i = nFromX + 1;
                j = nFromY;
            }
            else if (nFromX - nToX == 2)
            {
                i = nFromX - 1;
                j = nFromY;
            }
            else if (nToY - nFromY == 2)
            {
                i = nFromX;
                j = nFromY + 1;
            }
            else if (nFromY = nToY == 2)
            {
                i = nFromX;
                j = nFromY - 1;
            }
            if(position[j][i] != NOCHESS)
                return false;//绊马腿
            break;
        case B_CANON://黑炮
        case R_CANON://红炮
            if(nFromY != nToY && nFromX != nToX)
                return false;//炮走直线
            //炮不吃子时经过的路线中不能有棋子
            if(position[nToY][nToX] == NOCHESS)
            {
                if(nFromY == nToY)
                {
                    if(nFromX < nToX)
                    {
                        for(i = nFromX + 1; i < nToX; i++)
                            if(position[nFromY][i] != NOCHESS)
                                return false;
                    }
                    else
                    {
                        for(i = nToX + 1; i < nFromX; i++)
                            if(position[nFromY][i] != NOCHESS)
                                return false;
                    }
                }
                else
                {
                    if(nFromY > nToY)
                    {
                        for(j = nFromY + 1; j < nToY; j++)
                            if(position[j][nFromX] != NOCHESS)
                                return false;
                    }
                    else
                    {
                        for(j = nToY + 1; j < nFromY; j++)
                            if(position[j][nFromX] != NOCHESS)
                                return false;
                    }
                }
            }
            //炮吃子时
            else
            {
                int count = 0;
                if(nFromY == nToY)
                {
                    if(nFromX < nToX)
                    {
                        for(i = nFromX + 1; i < nToX; i++)
                            if(position[nFromY][i] != NOCHESS)
                                count++;
                        if(count != 1)
                            return false;
                    }
                    else
                    {
                        for(i = nToX + 1; i < nFromX; i++)
                            if(position[nFromY][i] != NOCHESS)
                                count++;
                        if(count != 1)
                            return false;
                    }
                }
                else
                {
                    if(nFromY < nToY)
                    {
                        for(j = nFromY + 1; j < nToY; j++)
                            if(position[j][nFromX] != NOCHESS)
                                count++;
                        if(count != 1)
                            return false;
                    }
                    else
                    {
                        for(j = nToY + 1; j < nFromY; j++)
                            if(position[j][nFromX] != NOCHESS)
                                count++;
                        if(count != 1)
                            return false;
                    }
                }
            }
            break;
         default:
            return false;
    }
    return true;//合法的走法，返回TRUE
}


//在m_MoveList中插入一个走法
//nFromX是起始位置横坐标
//nFromY是起始位置纵坐标
//nToX是目标位置横坐标
//nToY是目标位置纵坐标
//nPly是走法所在的层次

    
int CMoveGenerator::AddMove(int nFromX,int nFromY,int nToX,int nToY,int nPly)
{
    m_MoveList[nPly][m_nMoveCount].From.x = nFromX;
    m_MoveList[nPly][m_nMoveCount].From.y = nFromY;
    m_MoveList[nPly][m_nMoveCount].To.x = nToX;
    m_MoveList[nPly][m_nMoveCount].To.y = nToY;
    m_nMoveCount++;
    return m_nMoveCount;
    
}
//以上是AddMove
//用以产生局面position中所有可能的走法
//position是包含所有棋子位置信息的二维数组
//nPly指明当前搜索的层数，每层走法将存在不同的位置，以免覆盖
//nSide指明产生哪一方的走法，TRUE为红方，FALSE为黑房
int CMoveGenerator::CreatePossibleMove(BYTE position[10][9],int nPly, int nSide)
{
    int x, y, nChessID;
    bool flag;
    int i,j;
    m_nMoveCount = 0;
    for(j = 0; j < 9; j++)
        for(i = 0; i < 10; i++)
        {
            if(position[i][j] != NOCHESS)
            {
                nChessID = position[i][j];
                if(! nSide && IsRed(nChessID))
                    continue;//如果要产生黑棋走法，跳过红棋
                if(nSide && IsBlack(nChessID))
                    continue;//如果要产生红棋走法，跳过黑棋
                switch(nChessID)
                {
                    case R_KING://红将
                    case B_KING://黑帅
                        Gen_KingMove(position,i,j,nPly);
                        break;
                    case R_BISHOP://红仕
                        Gen_RBishopMove(position,i,j,nPly);
                        break;
                    case B_BISHOP://黑士
                        Gen_BBishopMove(position,i,j,nPly);
                        break;
                    case R_ELEPHANT://红相
                    case B_ELEPHANT://黑象
                        Gen_ElephantMove(position,i,j,nPly);
                        break;
                    case R_HORSE://红马
                    case B_HORSE://黑马
                        Gen_HorseMove(position,i,j,nPly);
                        break;
                    case R_CAR://红车
                    case B_CAR://黑车
                        Gen_CarMove(position,i,j,nPly);
                        break;
                    case R_PAWN://红卒
                        Gen_RPawnMove(position,i,j,nPly);
                        break;
                    case B_PAWN://黑兵
                        Gen_BPawnMove(position,i,j,nPly);
                        break;
                    case R_CANON://红炮
                    case B_CANON://黑炮
                        Gen_CanonMove(position,i,j,nPly);
                        break;
                    default:
                        break;
                }//end of switch
            }
        }
    return m_nMoveCount;//返回总的走法数
}
//以上是CreatePossibleMove
//产生王的合法走步
//i,j表明棋子的位置
//nPly表明插入到List第几层
void CMoveGenerator::Gen_KingMove(BYTE position[10][9],int i,int j,int nPly)
{
    int x, y ;
    for(y = 0; y < 3; y++)
        for(x = 3; x < 6; x++)
            if(IsValidMove(position,j,i,x,y))//走步是否合法
                AddMove(j, i, x, y, nPly);//将这个走法插入m_MoveList
    for(y = 7; y < 10; y++)
        for(x = 3; x < 6; x++)
            if(IsValidMove(position,j,i,x,y))//走步是否合法
                AddMove(j, i, x, y, nPly);//将这个走法插入m_MoveList
}
//产生红仕的合法走步
//i，j表明棋子的位置
//nPly表明插入到第几层
void CMoveGenerator::Gen_RBishopMove(BYTE position[10][9],int i,int j,int nPly)
{
    int x, y;
    for(y = 7; y < 10; y++)
        for(x = 3; x < 6; x++)
            if(IsValidMove(position,j,i,x,y))//走步是否合法
                AddMove(j, i, x, y, nPly);//将这个走法插入m_MoveList
}
//产生黑士的合法走步
//i，j表明棋子的位置
//nPly表明插入到第几层
void CMoveGenerator::Gen_BBishopMove(BYTE position[10][9],int i,int j,int nPly)
{
    int x, y;
    for(y = 0; y < 3; y++)
        for(x = 3; x < 6; x++)
            if(IsValidMove(position,j,i,x,y))//走步是否合法
                AddMove(j, i, x, y, nPly);//将这个走法插入m_MoveList
}
//产生象/相的合法走步
//i，j表明棋子的位置
//nPly表明插入到第几层
void CMoveGenerator::Gen_ElephantMove(BYTE position[10][9],int i,int j,int nPly)
{
    int x, y;
    //插入右下方的有效走法
    x = j + 2;
    y = i + 2;
    if(x < 9 && y < 10 && IsValidMove(position, j, i, x, y))
        AddMove(j, i, x, y, nPly);
    //插入右上方的有效走法
    x = j + 2;
    y = i - 2;
    if(x < 9 && y >= 0 && IsValidMove(position, j, i, x, y))
        AddMove(j, i, x, y, nPly);
    //插入左下方的有效走法
    x = j - 2;
    y = i + 2;
    if(x >= 0 && y < 10 && IsValidMove(position, j, i, x, y))
        AddMove(j, i, x, y, nPly);
    //插入左上方的有效方法
    x = j - 2;
    y = i - 2;
    if(x >= 0 && y >= 0 && IsValidMove(position, j, i, x, y))
        AddMove(j, i, x, y, nPly);
}
//产生马的合法走步
//i,j表明棋子的位置
//nPly表示插入到List第几层
void CMoveGenerator::Gen_HorseMove(BYTE position[10][9], int i, int j, int nPly)
{
    int x, y;
    //插入右下方的有效走法
    x = j + 2;//右2
    y = i + 1;//下1
    if((x < 9 && y < 10) && IsValidMove(position, j, i, x, y))
        AddMove(j, i, x, y, nPly);
    //插入右上方的有效走法
    x = j + 2;//右2
    y = i - 1;//上1
    if((x < 9 && y >= 0) && IsValidMove(position, j, i, x, y))
        AddMove(j, i, x, y, nPly);
    //插入左下方的有效走法
    x = j - 2;//左2
    y = i + 1;//下1
    if((x >= 0 && y < 10) && IsValidMove(position, j, i, x, y))
        AddMove(j, i, x, y, nPly);
    //插入左上方的有效方法
    x = j - 2;//左2
    y = i - 1;//上1
    if((x >= 0 && y >= 0) && IsValidMove(position, j, i, x, y))
        AddMove(j, i, x, y, nPly);
    //插入右下方的有效方法
    x = j + 1;//右1
    y = i + 2;//下
    if((x < 9 && y < 10) && IsValidMove(position, j, i, x, y))
        AddMove(j, i, x, y, nPly);
    //插入左下方的有效方法
    x = j - 1;//左1
    y = i + 2;//下2
    if((x >= 0 && y < 10) && IsValidMove(position, j, i, x, y))
        AddMove(j, i, x, y, nPly);
    //插入右下方的有效方法
    x = j + 1;//右1
    y = i - 2;//左2
    if((x < 9 && y >= 0) && IsValidMove(position, j, i, x, y))
        AddMove(j, i, x, y, nPly);
    //插入左上方的有效方法
    x = j - 1;//左1
    y = i - 2;//上2
    if((x >= 0 && y >= 0) && IsValidMove(position, j, i, x, y))
        AddMove(j, i, x, y, nPly);
}
//产生红卒的合法走步
//i,j表明棋子的位置
//nPly表明插入到List第几层
void CMoveGenerator::Gen_RPawnMove(BYTE position[10][9], int i, int j , int nPly)
{
    int x, y;
    int nChessID;
    nChessID = position[i][j];
    y = i - 1;//向前
    x = j;
    if(y > 0 && ! IsSameSide(nChessID, position[y][x]))
        AddMove(j, i, x, y, nPly);//前方无阻碍，插入走法
    if(i < 5)//是否已过河
    {
        y = i;
        x = j + 1;//右边
        if(x < 9 && ! IsSameSide(nChessID, position[y][x]))
            AddMove(j, i, x, y, nPly);//插入向右的方法
        x = j - 1;//左边
        if(x >= 0 && ! IsSameSide(nChessID, position[y][x]))
            AddMove(j, i, x, y, nPly);//插入向左的方法
    }
}
//产生黑兵的走法
//i,j表明棋子的位置
//nPly表明插入到List第几层
void CMoveGenerator::Gen_BPawnMove(BYTE position[10][9], int i, int j , int nPly)
{
    int x, y;
    int nChessID;
    nChessID = position[i][j];
    y = i + 1;//向前
    x = j;
    if(y < 10 && ! IsSameSide(nChessID, position[y][x]))
        AddMove(j, i, x, y, nChessID);
    if(i > 4)//是否已过河
    {
        y = i;
        x = j + 1;
        if(x < 9 && ! IsSameSide(nChessID, position[y][x]))
            AddMove(j, i, x, y, nPly);//插入向右的走法
        x = j - 1;
        if(x >= 0 && ! IsSameSide(nChessID, position[y][x]))
            AddMove(j, i, x, y, nPly);//插入向左的走法
    }
}
//产生车的合法走步
//i，j表明棋子的位置
//nply表明插入到第几层
void CMoveGenerator::Gen_CarMove(BYTE position[10][9], int i, int j, int nPly)
{
    int x, y;
    int nChessID;
    nChessID = position[i][j];
    //插入右边的可走位置
    x = j + 1;
    y = i;
    while (x < 9)
    {
        if(NOCHESS == position[y][x])
            AddMove(j, i, x, y, nPly);
        else
        {
            if( ! IsSameSide(nChessID, position[y][x]))
                AddMove(j, i, x, y, nPly);
            break;
        }
        x++;
    }
    //插入左边的可走位置
    x = j - 1;
    y = i;
    while (x >= 0)
    {
        if(NOCHESS == position[y][x])
            AddMove(j, i, x, y, nPly);
        else
        {
            if( ! IsSameSide(nChessID, position[y][x]))
                AddMove(j, i, x, y, nPly);
            break;
        }
        x--;
    }
    //插入向下的可走位置
    x = j;
    y = i + 1;
    while (y < 10)
    {
        if(NOCHESS == position[y][x])
            AddMove(j, i, x, y, nPly);
        else
        {
            if( ! IsSameSide(nChessID, position[y][x]))
                AddMove(j, i, x, y, nPly);
            break;
        }
        y++;
    }
    //插入向上的可走位置
    x = j;
    y = i - 1;
    while (y >= 0)
    {
        if(NOCHESS == position[y][x])
            AddMove(j, i, x, y, nPly);
        else
        {
            if( ! IsSameSide(nChessID, position[y][x]))
                AddMove(j, i, x, y, nPly);
            break;
        }
        y--;
    }
}
//产生炮的合法走步
//i，j表明棋子的位置
//nPly表明插入到List第几层
void CMoveGenerator::Gen_CanonMove(BYTE position[10][9], int i, int j, int nPly)
{
    int x, y;
    bool   flag;
    int nChessID;
    nChessID = position[i][j];
    //插入向右方向上的可走位置
    x = j + 1;
    y = i;
    flag = false;
    while (x < 9)
    {
        if(NOCHESS == position[y][x])//此位置上是否有棋子
        {
            if( ! flag)//是否隔有棋子
                AddMove(j, i, x, y, nPly);//没有隔棋子，插入可走位置
        }
        else
        {
            if( ! flag)//没有隔棋子,此棋子是第一个阻碍，设置标志
                flag = true;
            else
            {//隔有棋子，此处如为敌方棋子就可走
                if( ! IsSameSide(nChessID, position[y][x]))
                    AddMove(j, i, x, y, nPly);
                break;
            }
        }
        x++;//继续下一个位置
    }
    //插入向左方向上的的可走位置
    x = j - 1;
    flag = false;
    while (x >= 0)
    {
        if(NOCHESS == position[y][x])//此位置上是否有棋子
        {
            if( ! flag)//此位置是否同炮之间没有阻碍
                AddMove(j, i, x, y, nPly);//没有隔棋子，插入可走位置
        }
        else
        {
            if( ! flag)//没有隔棋子，此棋子是第一个阻碍，设置标志
                flag = true;
            else
            {//隔有棋子，此处如为敌方棋子就可走
                if( ! IsSameSide(nChessID, position[y][x]))
                    AddMove(j, i, x, y, nPly);//是敌方棋子，可走
                break;
            }
        }
        x--;//继续下一个位置
    }
    //插入向下方向上的可走位置
    x = j;
    y = i + 1;
    flag = false;
    while (y < 10)
    {
        if(NOCHESS == position[y][x])
        {
            if( ! flag)
                AddMove(j, i, x, y, nPly);
        }
        else
        {
            if( ! flag)//没有隔棋子，此棋子是第一个阻碍，设置标志
                flag = true;
            else
            {//隔有棋子，此处如为敌方棋子就可走
                if( ! IsSameSide(nChessID, position[y][x]))
                    AddMove(j, i, x, y, nPly);
                break;
            }
        }
        y++;
    }
    y = i - 1;
    flag = false;
    while (y >= 0)
    {
        if(NOCHESS == position[y][x])
        {
            if( ! flag)
                AddMove(j, i, x, y, nPly);
        }
        else
        {
            if( ! flag)
                flag = true;
            else
            {
                if( ! IsSameSide(nChessID, position[y][x]))
                    AddMove(j, i, x, y, nPly);
                break;
            }
        }
        y--;
    }
}//end of CMoveGenerator.cpp
