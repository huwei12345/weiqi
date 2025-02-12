#include "boardwidget.h"

#include <QPainter>

int dx[4] {0,  0,  -1,  1};
int dy[4] {-1, 1,  0,   0};

//斜
int ox[4] {1,1,-1,-1};
int oy[4] {1,-1,1,-1};

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
    if (color == 2) {
        QString str = "S" + colToChar(col) + QString::number(19 - row);
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
