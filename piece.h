#ifndef PIECE_H
#define PIECE_H
#include <vector>
#include <string>
#include <map>

extern const int BOARDWIDTH;
extern const int HEIGHT;
extern const int WIDTH;
enum PieceColor {BLACK = 0, WHITE = 1, SPACE = 2};
enum Direction {TOP = 0, BOTTOM, LEFT, RIGHT, TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT};


class Piece {
public:
    Piece() : color(2), aceCount(0), row(0), col(0), moveNumber(-1) {}
    int color;//0黑 1白 2无
    int aceCount;//气数
    int row;
    int col;
    int moveNumber;  // 手数
    bool operator==(Piece rhs);
};

#endif // PIECE_H
