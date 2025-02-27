﻿#ifndef KATA_H
#define KATA_H

#include "piece.h"

#include <QProcess>
#include <QString>
#include "sgfparser.h"
#include "threadsafequeue.h"

// 每一步棋的分析结果
struct MoveAnalysis {
    int moveNumber;          // 手数（从0或1开始）
    QString move;            // 着法（例如 "B Q16"）
    double winRate;          // 胜率（0~1）
    double scoreLead;        // 目数差（正数表示领先）
    int aiRank;              // AI推荐排名（0=一选，1=二选，-1=未推荐）
    bool isUserMoveBest;     // 用户着法是否为AI一选
    QStringList topMoves;    // 前N个推荐着法（用于计算吻合度）
    int color;
};

class AnalysisReport {
public:
    //针对某方的分析

    static void generateReport(QList<MoveAnalysis> analysis, int color) {
        int totalMoves = analysis.size();
        QList<int> bestMoveMatches;
        QList<int> top3Matches;
        QList<int> brilliantMoves;//妙手
        QList<int> badMoves;//恶手
        QList<int> purposeMoves;//AI推荐10选内
        QList<int> notGoodMoves;//不佳 掉10-20胜率以内
        // 计算吻合度和标记关键着法
        std::cout << "winRate\n";
        int colorCnt[2] = {0, 0};
        for (auto &r : analysis) {
            if (color != r.color) {
                r.winRate = 1.0 - r.winRate;
                r.scoreLead = -r.scoreLead;
            }
            std::cout << r.winRate << " ";
        }
        std::cout << "\n\n";
        fflush(stdout);
        for (int i = 0; i < analysis.size() - 1; i++) {
            if (analysis[i].color == 0)
                colorCnt[0]++;
            else
                colorCnt[1]++;
            if (analysis[i].color != color) {
                continue;
            }

            if (analysis[i].aiRank == 0) {
                //最佳
                bestMoveMatches.append(analysis[i].moveNumber);
            }
            if (analysis[i].aiRank >= 0 && analysis[i].aiRank < 3) {
                //优秀
                top3Matches.append(analysis[i].moveNumber);
            }
            else if (analysis[i + 1].winRate - analysis[i].winRate > 0.1) {
                //不在AI三选点内，落完当前手的胜率，比没落这手的胜率（AI一选）还高10个点，妙手
                brilliantMoves.append(analysis[i].moveNumber);
            } else if (analysis[i + 1].winRate - analysis[i].winRate < -0.2) {
                //掉20个点，恶手
                badMoves.append(analysis[i].moveNumber);
            } else if (analysis[i + 1].winRate - analysis[i].winRate > -0.2
                       && analysis[i + 1].winRate - analysis[i].winRate < -0.1) {
                //掉10-20
                notGoodMoves.append(analysis[i].moveNumber);
            } else {
                //3-10选及普通
                purposeMoves.append(analysis[i].moveNumber);
            }
        }
        //TODO: 最后一手单独处理，要看一下落完最后一手后的AI推荐及胜率，再运行一次kata analyze
        // 输出报告
        qDebug() << "==== AI 对局分析报告 ====";
        qDebug() << "总手数:" << totalMoves;
        qDebug() << (color == 0 ? "黑棋" : "白棋") << "手数" << colorCnt[color];
        qDebug() << "AI一选吻合度:" << ((int)bestMoveMatches.size() * 100.0 / colorCnt[color]) << "%";
        qDebug() << "AI三选内吻合度:" << ((int)top3Matches.size() * 100.0 / colorCnt[color]) << "%";
        qDebug() << "妙手（显著优势）:" << brilliantMoves << ((int)brilliantMoves.size() * 100.0 / colorCnt[color]) << "%";
        qDebug() << "优秀:" << ((int)purposeMoves.size() * 100.0 / colorCnt[color]) << "%";
        qDebug() << "较差:" << ((int)notGoodMoves.size() * 100.0 / colorCnt[color]) << "%";
        qDebug() << "恶手（显著劣势）:" << badMoves << ((int)badMoves.size() * 100.0 / colorCnt[color]) << "%";
    }
};

class Kata : public QObject
{
    Q_OBJECT
public:
    Kata();
    Kata(std::vector<std::vector<Piece>> *board);
    int test();
    void parseShowboard(const QString &showboardOutput, std::vector<std::vector<Piece>> &board);
    std::vector<std::vector<Piece>> *mBoard;
    void reInitKata(std::shared_ptr<SGFTreeNode> head);

    Q_SLOT int startKata();
    bool isValid(Piece piece);
    Q_SLOT QList<MoveAnalysis> analyzeFullGame(std::shared_ptr<SGFTreeNode> gameRoot);
    Q_SLOT void getAIPiece(Piece nowPiece, int color);
    Q_SLOT void calculateScore(std::shared_ptr<SGFTreeNode> node, JudgeInfo *info);
    Q_SLOT void calculateEndScore(std::shared_ptr<SGFTreeNode> node, JudgeInfo *info);
    Q_SLOT void startKataAnalyze(std::shared_ptr<SGFTreeNode> node, ThreadSafeQueue<QString> *queue);
    Q_SLOT void stopKataAnalyze();
    Q_SLOT void playOnePiece(Piece piece);
    MoveAnalysis parseAnalysisOutput(const QString &output, const QString &userMove);
    std::vector<Piece> getMoveHistory(std::shared_ptr<SGFTreeNode> node);
signals:
    void getAIPieceSuccess(Piece* piece);
    void calculateScoreSuccess();
    void calculateEndResultSuccess();
    void analyzeResultUpdate();
private:
    void sendCommand(const QString& cmd);
    std::shared_ptr<SGFTreeNode> root;
    QProcess* kataGoProcess;
    QString mKatagoOutput;
    QString mAnalyzeOutput;
    ThreadSafeQueue<QString>* mAnalyzeQueue;
    bool mAnalyzeRunning;


    bool isYingYan;
    ThreadSafeQueue<QString>* mYinYanOutputQueue;
    QList<MoveAnalysis> analysisList;
};

#endif // KATA_H
