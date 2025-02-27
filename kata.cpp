﻿#include "kata.h"
#include <QProcess>
#include <QDebug>
#include <QThread>
#include <QRegularExpression>
#include "piece.h"
#include "threadsafequeue.h"
#include <iostream>
Kata::Kata()
{
    mAnalyzeQueue = nullptr;
    mYinYanOutputQueue = new ThreadSafeQueue<QString>;
    mAnalyzeRunning = false;
    isYingYan = false;
}

Kata::Kata(std::vector<std::vector<Piece> > *board) : mBoard(board)
{
    mAnalyzeQueue = nullptr;
    mYinYanOutputQueue = new ThreadSafeQueue<QString>;
    mAnalyzeRunning = false;
    isYingYan = false;
}

// 解析 showboard 输出并生成 19x19 的二维棋盘数组
void Kata::parseShowboard(const QString &showboardOutput, std::vector<std::vector<Piece>> &board) {
    // 去除无关信息，获取棋盘部分（假设每行棋盘信息为19个字符）
    QStringList lines = showboardOutput.split("\r\n", QString::SkipEmptyParts);
    int r = 0;
    while (r < lines.size()) {
        if (lines[r].startsWith("= MoveNum")) {
            break;
        }
        r++;
    }
    if (r == lines.size()) {
        return;
    }

    // 处理每一行棋盘
    for (int i = r + 2; i < BOARDWIDTH + r + 2; ++i) {
        QString line = lines[i];  // 反转行的顺序，从第19行开始处理
        int row = i - r - 2;
        int col = 0;
        for (int k = 0; k < line.size(); ++k) {
            if (col > 18) {
                qDebug() << "fatal error";
                return;
            }
            // 根据每行字符设置棋盘状态
            char s = line[k].toLatin1();
            if (s == 'X') {
                board[row][col].color = 0;
                board[row][col].row = row;
                board[row][col].col = col;
                col++;
            }
            else if (s == 'O') {
                board[row][col].color = 1;
                board[row][col].row = row;
                board[row][col].col = col;
                col++;
            }
            else if (s == '.') {
                board[row][col].color = 2;
                board[row][col].row = row;
                board[row][col].col = col;
                col++;
            }
        }
    }

    // 打印棋盘二维数组

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            std::cout << board[i][j].color << " ";
        }
        std::cout << "\n";
    }
    fflush(stdout);
}

int Kata::startKata() {
    kataGoProcess = new QProcess(this);
    // 设置 KataGo 可执行文件的路径
    // D:\download\katago-v1.15.0-eigen-windows-x64
    // kata1-b6c96-s938496-d1208807.txt.gz
    QString kataGoPath = "D:\\download\\katago-v1.15.3-eigen-windows-x64\\katago.exe";  // 替换为你的katago可执行文件的路径

    // 配置模型和配置文件路径
    QString modelFilePath = "D:\\download\\katago-v1.15.3-eigen-windows-x64\\kata1-b15c192-s1672170752-d466197061.txt.gz"; // 替换为你的模型文件路径
    QString configFilePath = "D:\\download\\katago-v1.15.3-eigen-windows-x64\\default_gtp.cfg";  // 替换为你的配置文件路径

    // 传递启动参数
    QStringList arguments;
    arguments << "gtp"                // 使用 GTP (Go Text Protocol) 模式
              << "-model" << modelFilePath
              << "-config" << configFilePath;

    // 启动 KataGo 进程
    kataGoProcess->start(kataGoPath, arguments);

    // 检查是否成功启动
    if (!kataGoProcess->waitForStarted()) {
        qDebug() << "Failed to start KataGo! Error: " << kataGoProcess->errorString();
        return -1;
    }

    // 连接信号和槽来处理输出
    QObject::connect(kataGoProcess, &QProcess::readyReadStandardOutput, [this]() {
        QByteArray output = kataGoProcess->readAllStandardOutput();
        const QString str(output);
        mKatagoOutput = str;
        qDebug() << "KataGo Output: " << output;
        if (str.startsWith("info move") && isYingYan == false) {
            //mAnalyzeOutput = str;
            if (mAnalyzeQueue != nullptr && mAnalyzeQueue->size() < 1000) {
                mAnalyzeQueue->enqueue(str);
                emit analyzeResultUpdate();
            }
            return;
        }
        else if (str.startsWith("info move") && isYingYan == true) {
            if (mYinYanOutputQueue->size() == 0) {
                mYinYanOutputQueue->enqueue(str);
            }
            return;
        }
        parseShowboard(str, *mBoard);
    });

    QObject::connect(kataGoProcess, &QProcess::readyReadStandardError, [this]() {
        QByteArray errorOutput = kataGoProcess->readAllStandardError();
        qDebug() << "KataGo Error Output: " << errorOutput;
    });
    return true;
}


void Kata::playOnePiece(Piece piece) {
    QString str("play ");
    str += piece.color == 0 ? "B " : "W ";
    str += showPiece(piece.row, piece.col);
    str += "\r\n";
    qDebug() << str;
    QByteArray arr;
    arr.append(str);
    kataGoProcess->write(arr);
    kataGoProcess->waitForFinished(200);

    if (mAnalyzeRunning && mAnalyzeQueue != nullptr) {
        kataGoProcess->waitForFinished(200);
        while (!mAnalyzeQueue->isEmpty()) {
            mAnalyzeQueue->dequeue(mAnalyzeOutput);
        }
        mAnalyzeOutput.clear();
        kataGoProcess->write("kata-analyze 100\n");
    }
}

void Kata::getAIPiece(Piece nowPiece, int color) {
    QString str("play ");
    str += nowPiece.color == 0 ? "B " : "W ";
    str += showPiece(nowPiece.row, nowPiece.col);
    str += "\r\n";
    qDebug() << str;
    QByteArray arr;
    arr.append(str);
    kataGoProcess->write(arr);
    kataGoProcess->waitForFinished(200);
    QString cmd;
    if (color == 0)
        cmd = "genmove black\n";
    else
        cmd = "genmove white\n";
    mKatagoOutput.clear();
    kataGoProcess->write(cmd.toLatin1());
    int cnt = 0;
    while (mKatagoOutput.size() == 0 && cnt != 100) {
        kataGoProcess->waitForFinished(100);
        cnt++;
    }
    qDebug() << "katago: " << mKatagoOutput;
    if (mKatagoOutput.size() != 0) {
        Piece* newPiece = new Piece;
        newPiece->load(mKatagoOutput.mid(2));
        newPiece->color = color;
        if (isValid(*newPiece)) {
            qDebug() << "AI choice " << (color == 0 ? "black " : "white ") << " putIn" << showPiece(*newPiece);
            emit getAIPieceSuccess(newPiece);
        }
        else {
            delete newPiece;
            emit getAIPieceSuccess(nullptr);
        }
    }
    emit getAIPieceSuccess(nullptr);
}

bool Kata::isValid(Piece piece) {
    if (piece.row >= 0 && piece.col <= 18 && piece.col >= 0 && piece.col <= 18 && piece.color <= 2 && piece.color >= 0) {
        return true;
    }
    return false;
}


std::vector<Piece> Kata::getMoveHistory(std::shared_ptr<SGFTreeNode> node) {
    std::vector<Piece> pieceList;
    auto p = node;
    while (p != nullptr && p->move.color != -1) {
        if (isValid(p->move)) {
            pieceList.push_back(p->move);
            p = p->parent.lock();
        }
        else {
            qDebug() << "Fatal Error" << showPiece(p->move);
        }
    }
    std::reverse(pieceList.begin(), pieceList.end());
    return pieceList;
}

QList<MoveAnalysis> Kata::analyzeFullGame(std::shared_ptr<SGFTreeNode> gameRoot) {

    // 重置棋盘并设置规则
    sendCommand("clear_board");
    sendCommand("boardsize 19");
    sendCommand("kata-set-rules chinese");
    analysisList.clear();
    // 遍历棋局历史
    std::vector<Piece> moveHistory = getMoveHistory(gameRoot); // 实现获取历史着法
    isYingYan = true;
    for (int i = 0; i < (int)moveHistory.size(); ++i) {
        mYinYanOutputQueue->clear();
        // 发送分析请求，获取当前局面的所有候选着法
        sendCommand("kata-analyze 100 maxmoves 10"); // 分析前20个候选着法
        int cnt = 0;
        while (mYinYanOutputQueue->size() == 0 && cnt < 100) {
            kataGoProcess->waitForFinished(30);
            cnt++;
        }
        QString yinyanStr;
        sendCommand("");
        if (mYinYanOutputQueue->size() != 0) {
            mYinYanOutputQueue->dequeue(yinyanStr);
        }
        else {
            qDebug() << i <<" ERRRRRRRRRRRRRRRRRRRRRRRRRRRRRR";
            break;
        }
        auto move = moveHistory[i];
        // 播放到当前局面
        QString cmd = QString("play %1 %2\n")
                          .arg(move.color == 0 ? "B" : "W")
                          .arg(move.toString());
        qDebug() << "seq " << i << " " << cmd;
        sendCommand(cmd);
        kataGoProcess->waitForFinished(30);
        MoveAnalysis analysis = parseAnalysisOutput(yinyanStr, move.toString());
        analysis.color = move.color;
        analysis.moveNumber = i + 1;
        analysisList.append(analysis);
    }

    //针对最后局面，分析一下形式
    mYinYanOutputQueue->clear();
    // 发送分析请求，获取当前局面的所有候选着法
    sendCommand("kata-analyze 100 maxmoves 10"); // 分析前20个候选着法
    int cnt = 0;
    while (mYinYanOutputQueue->size() == 0 && cnt < 100) {
        kataGoProcess->waitForFinished(30);
        cnt++;
    }
    QString yinyanStr;
    sendCommand("");
    if (mYinYanOutputQueue->size() != 0) {
        mYinYanOutputQueue->dequeue(yinyanStr);
    }
    else {
        qDebug() << "last" <<" ERRRRRRRRRRRRRRRRRRRRRRRRRRRRRR";
    }
    MoveAnalysis analysis = parseAnalysisOutput(yinyanStr, "");
    analysis.moveNumber = moveHistory.size() + 1;
    analysis.color = !moveHistory[moveHistory.size() - 1].color;
    analysisList.append(analysis);
    if (analysisList.size() != (int)moveHistory.size() + 1) {
        qDebug() << "YYYYYYYYYYYYYYYYYYYYYYYYYYYYY";
        return {};
    }
    return analysisList;
}


MoveAnalysis Kata::parseAnalysisOutput(const QString& output, const QString& userMove) {
    MoveAnalysis analysis;
    analysis.winRate = -1;
    analysis.scoreLead = 0;
    analysis.aiRank = -1;
    analysis.isUserMoveBest = false;

    QStringList lines = output.split("info ");
    QList<QPair<double, QString>> moves; // 保存（胜率, 着法）

    bool flag = false;
    for (const QString& line : lines) {
        if (line.size() != 0) {
            QRegularExpression regex(
                "move (\\w+) .* winrate ([0-9.]+) scoreMean ([+-]?[0-9.]+)");
            QRegularExpressionMatch match = regex.match(line);
            if (match.hasMatch()) {
                QString move = match.captured(1);
                double winRate = match.captured(2).toDouble();
                double scoreLead = match.captured(3).toDouble();
                if (flag == false) {
                    //一选胜率作为当前胜率（是还没下当前手的胜率）。
                    analysis.winRate = winRate;
                    analysis.scoreLead = scoreLead;
                    flag = true;
                }
                qDebug() << "{}{} "<< move << " " << winRate << " " << scoreLead;
                // 记录所有候选着法
                moves.append(qMakePair(winRate, move));
            }
        }
    }

    // 按胜率排序，确定AI推荐排名
    std::sort(moves.begin(), moves.end(), [](auto& a, auto& b) {
        return a.first > b.first; // 降序排列
    });

    if (userMove != "") {
        // 记录排名和推荐着法
        for (int i = 0; i < moves.size(); ++i) {
            if (moves[i].second == userMove) {
                analysis.aiRank = i;
                analysis.isUserMoveBest = (i == 0);
            }
            analysis.topMoves.append(moves[i].second);
        }
    }
    else {
        for (int i = 0; i < moves.size(); ++i) {
            analysis.topMoves.append(moves[i].second);
        }
        //最后一手用户没有落子
    }

    return analysis;
}

void Kata::sendCommand(const QString &cmd)
{
    kataGoProcess->write(cmd.toLatin1() + "\n");
    kataGoProcess->waitForFinished(10);
}

void Kata::reInitKata(std::shared_ptr<SGFTreeNode> head)
{
    if (head == nullptr) {
        return;
    }
    root = head;
    auto p = head;
    while (p != nullptr) {
        Piece piece = p->move;
        QString str("play ");
        str += piece.color == 0 ? "B " : "W ";
        str += showPiece(piece.row, piece.col);
        str += "\r\n";
        qDebug() << str;
        QByteArray arr;
        arr.append(str);
        kataGoProcess->write(arr);
        kataGoProcess->waitForFinished(100);
        if (p->branches.size() > 0) {
            p = p->branches[0];
        }
        else {
            break;
        }
    }
}

void Kata::calculateScore(std::shared_ptr<SGFTreeNode> node, JudgeInfo *info)
{
    info->reset();
    //根据棋局规则，选择katago规则
    kataGoProcess->write("kgs-rules chinese\n");
    kataGoProcess->waitForFinished(10);
    kataGoProcess->write("komi 7.5\n");
    kataGoProcess->waitForFinished(10);
    kataGoProcess->write("clear_board\n");
    kataGoProcess->waitForFinished(10);
    kataGoProcess->write("boardsize 19\n");
    kataGoProcess->waitForFinished(10);
    std::vector<Piece> pieceList;
    auto p = node;
    while (p != nullptr && p->move.color != -1) {
        if (isValid(p->move)) {
            pieceList.push_back(p->move);
            p = p->parent.lock();
        }
        else {
            qDebug() << "Fatal Error" << showPiece(p->move);
        }
    }
    std::reverse(pieceList.begin(), pieceList.end());
    for (auto piece : pieceList) {
        QString str;
        str = QString("play ") + (piece.color == 0 ? "B " : "W ") + showPiece(piece.row, piece.col) + "\n";
        //qDebug() << str;
        kataGoProcess->write(str.toLatin1());
        kataGoProcess->waitForFinished(10);
    }
    kataGoProcess->waitForFinished(100);
    mKatagoOutput.clear();
    kataGoProcess->write("kata-raw-nn 0\n");
    int cnt = 0;
    while (mKatagoOutput.size() == 0 && cnt != 100) {
        kataGoProcess->waitForFinished(100);
        cnt++;
    }
    qDebug() << "katago: " << mKatagoOutput;
    if (mKatagoOutput.size() != 0) {
        if (mKatagoOutput.startsWith("= symmetry 0") == false) {
            qDebug() << "Fatal Error";
            return;
        }
        bool ret = info->parse(mKatagoOutput);
        if (ret) {
            emit calculateScoreSuccess();
        }
    }
}

void Kata::calculateEndScore(std::shared_ptr<SGFTreeNode> node, JudgeInfo *info)
{
    //judgeBlackWin
    info->reset();
    //根据棋局规则，选择katago规则
    kataGoProcess->write("kgs-rules chinese\n");
    kataGoProcess->waitForFinished(10);
    kataGoProcess->write("komi 7.5\n");
    kataGoProcess->waitForFinished(10);
    kataGoProcess->write("clear_board\n");
    kataGoProcess->waitForFinished(10);
    kataGoProcess->write("boardsize 19\n");
    kataGoProcess->waitForFinished(10);
    std::vector<Piece> pieceList;
    auto p = node;
    while (p != nullptr && p->move.color != -1) {
        if (isValid(p->move)) {
            pieceList.push_back(p->move);
            p = p->parent.lock();
        }
        else {
            qDebug() << "Fatal Error1" << showPiece(p->move);
        }
    }
    std::reverse(pieceList.begin(), pieceList.end());
    for (auto piece : pieceList) {
        QString str;
        str = QString("play ") + (piece.color == 0 ? "B " : "W ") + showPiece(piece.row, piece.col) + "\n";
        //qDebug() << str;
        kataGoProcess->write(str.toLatin1());
        kataGoProcess->waitForFinished(10);
    }
    kataGoProcess->waitForFinished(100);
    mKatagoOutput.clear();
    kataGoProcess->write("final_score\n");
    int cnt = 0;
    while (mKatagoOutput.size() == 0 && cnt != 100) {
        kataGoProcess->waitForFinished(100);
        cnt++;
    }
    qDebug() << "katago: " << mKatagoOutput;
    if (mKatagoOutput.size() != 0) {
        bool ret = info->parseEnd(mKatagoOutput);
        if (ret) {
            emit calculateEndResultSuccess();
        }
    }
}

void Kata::startKataAnalyze(std::shared_ptr<SGFTreeNode> node, ThreadSafeQueue<QString> *queue)
{
    //judgeBlackWin
    //根据棋局规则，选择katago规则
//    kataGoProcess->write("komi 7.5\n");
//    kataGoProcess->waitForFinished(10);
    kataGoProcess->write("clear_board\n");
    kataGoProcess->waitForFinished(10);
    kataGoProcess->write("boardsize 19\n");
    kataGoProcess->waitForFinished(10);
    kataGoProcess->write("kata-set-rules chinese\n");
    kataGoProcess->waitForFinished(10);
    std::vector<Piece> pieceList;
    auto p = node;
    while (p != nullptr && p->move.color != -1) {
        if (isValid(p->move)) {
            pieceList.push_back(p->move);
            p = p->parent.lock();
        }
        else {
            qDebug() << "Fatal Error1" << showPiece(p->move);
        }
    }
    std::reverse(pieceList.begin(), pieceList.end());
    for (auto piece : pieceList) {
        QString str;
        str = QString("play ") + (piece.color == 0 ? "B " : "W ") + showPiece(piece.row, piece.col) + "\n";
        //qDebug() << str;
        kataGoProcess->write(str.toLatin1());
        kataGoProcess->waitForFinished(10);
    }
    mAnalyzeQueue = queue;
    mAnalyzeRunning = true;


    kataGoProcess->waitForFinished(200);
    mAnalyzeQueue->clear();
    mAnalyzeOutput.clear();
    kataGoProcess->write("kata-analyze 100\n");
//    qDebug() << "katago2: " << mAnalyzeOutput;
//    QString tmp = mAnalyzeOutput;
//    kataGoProcess->write("\r\n");
//    if (tmp.size() != 0) {
//        bool ret = info->parse(tmp);
//        if (ret) {
//            emit analyzeResultUpdate();
//        }
    //    }
}

void Kata::stopKataAnalyze()
{
    kataGoProcess->write("\n");
    mAnalyzeRunning = false;
    kataGoProcess->waitForFinished(300);
    mAnalyzeOutput.clear();
    if (mAnalyzeQueue != nullptr) {
        mAnalyzeQueue->clear();
    }
}




//suicide: (true | false)- 多子自杀是否合法。
//ko: ("SIMPLE" | "POSITIONAL" | "SITUATIONAL")- 用于防止循环的规则。
//whiteHandicapBonus\":\"0
//whiteHandicapBonus ("0" | "N-1" | "N")- 在让分盘游戏中，无论白方获得 0、N-1 还是 N 奖励分，其中 N 是黑方让分石的数量。


int Kata::test() {
    // 向 KataGo 发送 GTP 命令
    //    kataGoProcess->write("boardsize 19\n"); // 设置棋盘大小为19x19
    //    kataGoProcess->write("clear_board\n");   // 清空棋盘
    //    kataGoProcess->write("genmove black\n"); // 让 AI 下黑棋
    kataGoProcess->write("loadsgf play.sgf\n");     // 获取棋盘状态
    kataGoProcess->waitForFinished(1000);
    kataGoProcess->write("showboard\n");     // 获取棋盘状态

    // 等待进程结束
    kataGoProcess->waitForFinished(3000);

    // 关闭进程
    kataGoProcess->close();

    return 0;
}
