#include "piece.h"
#include <QtDebug>
#include <QString>
#include <iostream>

const int BOARDWIDTH = 19;
const int HEIGHT = 19;
const int WIDTH = 19;
const int BOARD_SIZE = 19;


int dx[4] {0,  0,  -1,  1};
int dy[4] {-1, 1,  0,   0};

//斜
int ox[4] {1,1,-1,-1};
int oy[4] {1,-1,1,-1};




bool Piece::operator==(Piece rhs)
{
    return this->row == rhs.row && this->col == rhs.col && this->color == rhs.color;
}

void Piece::load(QString str)
{
    col = charToCol(str[0].toLatin1());
    str = str.mid(1);
    row = 19 - str.toInt();
}

void showPoint(int row, int col, int color) {
    if (color == -1) {
        QString str = QString('A' + col + 1) + QString::number(19 - row) + "  noColor";
        qDebug() << "Piece row " << str;
        return;
    }
    QString str = QString('A' + col + 1) + QString::number(19 - row) + " " + (color == 0 ? "B" : (color == 1 ? "W" : "SPACE"));
    qDebug() << "Piece row " << str;
}

QString showPiece(const Piece &piece)
{
    QString str = (piece.color == 0 ? "b" : "w") + colToChar(piece.col) + QString::number(19 - piece.row);
    return str;
}

QString showPiece(int row, int col, int color)
{
    if (color == -1) {
        QString str = colToChar(col) + QString::number(19 - row);
        return str;
    }
    if (color == 2) {
        QString str = QString("S") + colToChar(col) + QString::number(19 - row);
        return str;
    }
    QString str = (color == 0 ? "b" : "w") + colToChar(col) + QString::number(19 - row);
    return str;
}


QString colToChar(int col) {
    QString numx;
    if (col >= 8) {
        numx = QString('A' + col + 1);
    }
    else {
        numx = QString('A' + col);
    }
    return numx;
}

int charToCol(char col)
{
    int num = 0;
    if (col >= 'I') {
        num = col - 'A' - 1;
    }
    else {
        num = col - 'A';
    }
    return num;
}

void JudgeInfo::reset()
{
    whiteOwnership.assign(BOARD_SIZE, std::vector<double>(BOARD_SIZE, 0));
    whiteWin = 0;
    whiteLoss = 0;
    noResult = 0;
    whiteLead = 0;//白领先目数
    whiteScoreSelfplay = 0;//领先参考
    whiteScoreSelfplaySq = 0;//no
    shorttermWinlossError = 0;//whiteWin-whiteLoss
    policy.assign(BOARD_SIZE, std::vector<float>(BOARD_SIZE, 0));
    whiteground = 0;
    blackground = 0;
}

void JudgeInfo::print() {
    qDebug() << "whiteWin" << whiteWin;
    qDebug() << "whiteLoss" << whiteLoss;
    qDebug() << "noResult" << noResult;
    qDebug() << "whiteLead" << whiteLead;
    qDebug() << "whiteScoreSelfplay" << whiteScoreSelfplay;
    qDebug() << "whiteScoreSelfplaySq" << whiteScoreSelfplaySq;
    qDebug() << "shorttermWinlossError" << shorttermWinlossError;
    for (int i = 0; i < BOARDWIDTH; i++) {
        for (int j = 0; j < BOARDWIDTH; j++) {
            std::cout << whiteOwnership[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool JudgeInfo::parse(const QString& content) {
//    = symmetry 0
//    whiteWin 0.000292
//    whiteLoss 0.999708
//    noResult 0.000000
//    whiteLead -30.243
//    whiteScoreSelfplay -30.942
//    whiteScoreSelfplaySq 1005.400
//    varTimeLeft -1.000
//    shorttermWinlossError -1.000
//    shorttermScoreError -1.000
    QStringList lines = content.split("\r\n", QString::SkipEmptyParts);
    int r = 0;
    while (r < lines.size()) {
        if (lines[r].startsWith("whiteWin")) {
            lines[r] = lines[r].mid(lines[r].indexOf(" ") + 1);
            whiteWin = lines[r].toFloat();
        }
        if (lines[r].startsWith("whiteLoss")) {
            lines[r] = lines[r].mid(lines[r].indexOf(" ") + 1);
            whiteLoss = lines[r].toFloat();
        }
        if (lines[r].startsWith("noResult")) {
            lines[r] = lines[r].mid(lines[r].indexOf(" ") + 1);
            noResult = lines[r].toFloat();
        }
        if (lines[r].startsWith("noResult")) {
            lines[r] = lines[r].mid(lines[r].indexOf(" ") + 1);
            noResult = lines[r].toFloat();
        }
        if (lines[r].startsWith("whiteLead")) {
            lines[r] = lines[r].mid(lines[r].indexOf(" ") + 1);
            whiteLead = lines[r].toFloat();
        }
        if (lines[r].startsWith("whiteScoreSelfplay")) {
            lines[r] = lines[r].mid(lines[r].indexOf(" ") + 1);
            whiteScoreSelfplay = lines[r].toFloat();
        }
        if (lines[r].startsWith("whiteScoreSelfplaySq")) {
            lines[r] = lines[r].mid(lines[r].indexOf(" ") + 1);
            whiteScoreSelfplaySq = lines[r].toFloat();
        }
        if (lines[r].startsWith("shorttermWinlossError")) {
            lines[r] = lines[r].mid(lines[r].indexOf(" ") + 1);
            shorttermWinlossError = lines[r].toFloat();
        }
        if (lines[r].startsWith("whiteOwnership")) {
            r++;
            for (int i = 0; i < BOARDWIDTH; i++, r++) {
                QStringList list = lines[r].split(" ", QString::SkipEmptyParts);
                for (int j = 0; j < BOARDWIDTH; j++) {
                    whiteOwnership[i][j] = list[j].toDouble();
                }
            }
        }
        if (r < lines.size() && lines[r].startsWith("policy")) {
            //r++;
//            for (int i = 0; i < BOARDWIDTH; i++, r++) {
//                QStringList list = lines[r].split(" ", QString::SkipEmptyParts);
//                for (int j = 0; j < BOARDWIDTH; j++) {
//                    whiteOwnership[i][j] = list[i].toFloat();
//                }
//            }
        }
        r++;
    }
    print();
    if (r == lines.size()) {
        return true;
    }
    // 处理每一行棋盘
    return true;
}

bool JudgeInfo::parseEnd(const QString &content)
{
    QString str;
    if (content.startsWith("= B") || content.startsWith("= W")) {
        str = content.mid(2);
        int winColor = (str[0].toLatin1() == 'B' ? 0 : 1);
        str = str.mid(1);
        judgeWhiteWin = str.toDouble();
        if (winColor == 0) {
            judgeWhiteWin = 0.0 - judgeWhiteWin;
        }
        return true;
    }
    return false;
}
