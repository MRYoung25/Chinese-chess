#include <stdio.h>
#include "SearchEngine.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] =__FILE__;
#define new DEBUG_NEW
#endif
CSearchEngine::CSearchEngine()
{
    
}
CSearchEngine::~CSearchEngine()
{
    delete m_pMG;//删去挂在搜索引擎上的走法产生器
    delete m_pEval;//删去挂在搜索引擎上的估值核心
}
//根据传入的走法改变棋盘
//move是要进行的走法
BYTE CSearchEngine::MakeMove(CHESSMOVE * move)
{
    BYTE nChessID;
    nChessID = CurPosition[move -> To.y][move -> To.x];//取目标位置棋子
    //把棋子移动到目标位置
    CurPosition[move -> To.y][move -> To.x] = CurPosition[move -> From.y][move -> From.x];
    //将原位置清空
    CurPosition[move -> From.y][move -> From.x] = NOCHESS;
    return nChessID;//返回被吃掉的棋子
}
//根据传入的走法恢复棋盘
//move是要进行的走法
//nChessID是原棋盘上move目标位置的棋子类型
void CSearchEngine::UnMakeMove(CHESSMOVE * move, BYTE nChessID)
{
    //将目标位置和棋子拷回原位
    CurPosition[move -> From.y][move -> From.x] =CurPosition[move -> To.y][move -> To.x];
    //恢复目标位置的棋子
    CurPosition[move -> To.y][move -> To.x] = nChessID;
}
//用以检查给定局面游戏是否结束
//如未结束，返回0，否则返回极大值/极小值
int CSearchEngine::IsGameOver(BYTE position[10][9], int nDepth)
{
    int i, j;
    bool RedLive = false, BlackLive = false;
    //检查红方九宫是否有将帅
    for(i = 7; i < 10; i++)
        for(j = 3; j < 6; j++)
        {
            if(position[i][j] == B_KING)
                BlackLive = true;
            if(position[i][j] == R_KING)
                RedLive = true;
        }
    //检查黑九方宫是否有将帅
    for(i = 0; i < 3; i++)
        for(j = 3; j < 6; j++)
        {
            if(position[i][j] == B_KING)
                BlackLive = true;
            if(position[i][j] == R_KING)
                RedLive = true;
        }
    i = (m_nMaxDepth - nDepth + 1) % 2;//取当前是奇偶标志
    if( ! RedLive)//红将是否不在了
        if(i)
            return 19990 + nDepth;//奇数层返回最大值
        else
            return -19990 - nDepth;//偶数层返回最大值
    return 0;//两个将都在，返回零
}
//end of CSearchEngine.cpp
