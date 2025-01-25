#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include "timecontrol.h"

#include <QString>
#include <string>

enum WinLoseRule {
    ChinaRule = 0,
    KoreaRule,
    JapanRule
};

class GameSettings
{
public:
    GameSettings();

//    setBlackPlayerName(const std::string& name) (设置黑方玩家名字)
//    setWhitePlayerName(const std::string& name) (设置白方玩家名字)
//    setKomi(int komi) (设置贴目)
//    setTimeLimit(int timeLimit) (设置时间限制)
//    setByoYomi(int byoYomi) (设置读秒限制)
//    setScoringMethod(int method) (设置得分规则)
    QString toSGFHead();
    QString loadSGFHead();
    std::string blackPlayerName;// (黑方玩家名字)
    std::string whitePlayerName;// (白方玩家名字)
    int komi; //(贴目，浮动贴目规则)
    int boardSize;// (棋盘大小，如 19x19, 13x13)

    TimeControl timecontrol;

    WinLoseRule winLoseRule; //规则
//  int scoringMethod (得分规则：1. 累积，2. 围地)
    int blackEaten;//黑棋吃子个数
    int whiteEaten;//白棋吃子个数
    int blackScore;//黑棋目数
    int whiteScore;//白棋目数

    int winResult;//胜负结果 0黑 1白 2和
    float winScore;//胜子数或目数，（3.75子）
    int blackTime; //比赛用时
    int whiteTime;
};

#endif // GAMESETTINGS_H
