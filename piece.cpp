#include "piece.h"
#include <QtDebug>
#include <QString>
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
