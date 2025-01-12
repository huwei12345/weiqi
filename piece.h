#ifndef PIECE_H
#define PIECE_H
#include <vector>
#include <string>
#include <map>
class Piece {
public:
    Piece() : color(2), aceCount(0) {}
    int color;//0黑 1白 2无
    int aceCount;//气数
    int row;
    int col;
    int moveNumber;  // 手数
};

#endif // PIECE_H
