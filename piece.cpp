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

void Piece::load(const QString& str)
{
    col = charToCol(str[0].toLatin1());
    QString m;
    if (str.size() > 2 && str[2].isDigit()) {
        m = str.mid(1, 2);
    }
    else {
        m = str.mid(1, 1);
    }
    row = 19 - m.toInt();
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

void loadPiece(const QString str, Piece& piece) {

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

class ProtocolStream {
public:
    ProtocolStream(QString stream) {
        str = stream;
        pos = 0;
    }

    QString getNextSubStr() {
        if (pos == -1 || pos >= (int)str.size() - 1) {
            tmp.clear();
            return tmp;
        }
        pos = str.indexOf(" ", pos);
        tmp.clear();
        if (pos == -1 || pos == 0) {
            return tmp;
        }
        int end = str.indexOf(" ", pos + 1);
        if (end != -1) {
            tmp = str.mid(pos + 1, end - pos - 1);
            pos = end;
        }
        else {
            tmp = str.mid(pos);
            pos = -1;
        }
        return tmp;
    }
private:
    int pos;
    QString str;
    QString tmp;
};

/*
info move C16 visits 1 edgeVisits 1 utility 0.0575616 winrate 0.523927 scoreMean 1.23603 scoreStdev 27.7788 scoreLead 1.23603 scoreSelfplay 0.69225 prior 0.124701 lcb -0.726073 utilityLcb -3.44244 weight 1 order 0 pv C16 info move D17 visits 1 edgeVisits 1 utility 0.0575616 winrate 0.523927 scoreMean 1.23603 scoreStdev 27.7788 scoreLead 1.23603 scoreSelfplay 0.69225 prior 0.124701 lcb -0.726073 utilityLcb -3.44244 weight 1 isSymmetryOf C16 order 1 pv D17 info move D3 visits 1 edgeVisits 1 utility 0.0557992 winrate 0.52271 scoreMean 1.72998 scoreStdev 27.6679 scoreLead 1.72998 scoreSelfplay 0.781309 prior 0.141445 lcb -0.72729 utilityLcb -3.4442 weight 1 order 2 pv D3 info move R16 visits 1 edgeVisits 1 utility 0.0557992 winrate 0.52271 scoreMean 1.72998 scoreStdev 27.6679 scoreLead 1.72998 scoreSelfplay 0.781309 prior 0.141445 lcb -0.72729 utilityLcb -3.4442 weight 1 isSymmetryOf D3 order 3 pv R16 info move C4 visits 1 edgeVisits 1 utility 0.0460743 winrate 0.518572 scoreMean 1.67975 scoreStdev 27.6738 scoreLead 1.67975 scoreSelfplay 0.581424 prior 0.133207 lcb -0.731428 utilityLcb -3.45393 weight 1 order 4 pv C4 info move Q17 visits 1 edgeVisits 1 utility 0.0460743 winrate 0.518572 scoreMean 1.67975 scoreStdev 27.6738 scoreLead 1.67975 scoreSelfplay 0.581424 prior 0.133207 lcb -0.731428 utilityLcb -3.45393 weight 1 isSymmetryOf C4 order 5 pv Q17 info move D16 visits 1 edgeVisits 1 utility 0.0534237 winrate 0.522092 scoreMean 1.07716 scoreStdev 27.8136 scoreLead 1.07716 scoreSelfplay 0.628422 prior 0.0609161 lcb -0.727908 utilityLcb -3.44658 weight 1 order 6 pv D16\r\n
*/
bool AnalyzeInfo::parse(const QString &content)
{
    QString str = content;
    qDebug() << "str " << str;
    if (infoMoveList.size() != 0) {
        infoMoveList.clear();
    }
    int index = str.indexOf("info move");
    if (index == -1) {
        return false;
    }
    ProtocolStream stream(str);
    QString tmp;
    InfoMove im;
    while (1) {
        tmp = stream.getNextSubStr();
        if (tmp.size() == 0) {
            break;
        }
        if (tmp == "move") {
            tmp = stream.getNextSubStr();
            im.move.load(tmp);
        }
        else if (tmp == "visits"){
            tmp = stream.getNextSubStr();
            im.visits = tmp.toInt();
        }
        else if (tmp == "edgeVisits") {
            tmp = stream.getNextSubStr();
            im.edgeVisits = tmp.toInt();
        }
        else if (tmp == "utility") {
            tmp = stream.getNextSubStr();
            im.utility = tmp.toFloat();
        }
        else if (tmp == "winrate") {
            tmp = stream.getNextSubStr();
            im.winrate = tmp.toFloat();
        }
        else if (tmp == "scoreMean") {
            tmp = stream.getNextSubStr();
            im.scoreMean = tmp.toFloat();
        }
        else if (tmp == "order") {
            tmp = stream.getNextSubStr();
            im.order = tmp.toInt();
        }
        else if (tmp == "pv") {
            tmp = stream.getNextSubStr();
            while (tmp != "info" && tmp.size() != 0) {
                Piece piece;
                piece.load(tmp);
                im.pv.push_back(piece);
                tmp = stream.getNextSubStr();
            }
            infoMoveList.push_back(im);
            im.reset();
            if (infoMoveList.size() >= 10) {
                break;
            }
        }
    }
    print();
    return true;
}

void AnalyzeInfo::print() const
{
    for (auto &r : infoMoveList) {
        std::cout << "Move: " << r.move << "  ";
        std::cout << "Visits: " << r.visits << "  ";
        std::cout << "Edge Visits: " << r.edgeVisits << "  ";
        std::cout << "Utility: " << r.utility << "  ";
        std::cout << "Winrate: " << r.winrate << "  ";
        std::cout << "Score Mean: " << r.scoreMean << "  ";
        std::cout << "Order: " << r.order << "  ";
        std::cout << "PV: ";
        for (const auto& p : r.pv) {
            std::cout << p << " ";  // 打印 pv 中的每个 Piece
        }
        std::cout << std::endl;
    }
    std::cout << "\n";
    fflush(stdout);
}

std::ostream& operator<<(std::ostream& os, const Piece& p) {
    // 假设 Piece 类有一个成员 `name` 用来表示棋子的名称
    os << showPiece(p.row, p.col).toStdString(); // 修改为实际成员
    return os;
}

void InfoMove::reset()
{
    visits = 0;
    edgeVisits = 0;
    utility = 0;
    winrate = 0;
    scoreMean = 0;
    order = 0;
    pv.clear();
}
