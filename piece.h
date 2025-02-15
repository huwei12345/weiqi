#ifndef PIECE_H
#define PIECE_H
#include <vector>
#include <string>
#include <map>
#include <QString>
#include <QObject>
extern const int BOARDWIDTH;
extern const int HEIGHT;
extern const int WIDTH;
extern const int BOARD_SIZE;
extern int dx[4];
extern int dy[4];
extern int ox[4];
extern int oy[4];

enum PieceColor {BLACK = 0, WHITE = 1, SPACE = 2};
enum Direction {TOP = 0, BOTTOM, LEFT, RIGHT, TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT};
enum BoardModeType {
    PlayMode = 0,//比赛模式
    TryMode = 1,//试下模式
    PutMode = 2,//摆放模式
    PracticeMode = 3,//练习模式
    SearchMode = 4,
    DingShiMode = 5,
    ExerciseMode = 6,
    AIMode = 7
};

enum GameState {
    NOGAME = 0,
    DISCUSS = 1,
    PLAY = 2,
    OVER = 3,
    DoubleQuotation = 4,//复盘
};

enum PutPieceType {
    BWChange = 0,
    BAlways,
    WAlways
};

enum ShouShuState {
    SHOWSHOUSHU = 0,
    NOSHOWSHU,
};

class Piece {
public:
    Piece() : color(2), aceCount(0), row(0), col(0), moveNumber(-1) {}
    Piece(int row, int col, int color) : color(color), row(row), col(col) {}
    int color;//0黑 1白 2无
    int aceCount;//气数
    int row;
    int col;
    int moveNumber;  // 手数
    bool operator==(Piece rhs);

    void load(QString str);
};
Q_DECLARE_METATYPE(Piece);

void showPoint(int row, int col, int color = -1);
QString showPiece(int row, int col, int color = -1);
QString showPiece(const Piece& piece);
QString colToChar(int col);
int charToCol(char col);
#endif // PIECE_H
