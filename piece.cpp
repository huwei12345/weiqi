#include "piece.h"
const int BOARDWIDTH = 19;
const int HEIGHT = 19;
const int WIDTH = 19;
const int BOARD_SIZE = 19;
bool Piece::operator==(Piece rhs)
{
    return this->row == rhs.row && this->col == rhs.col && this->color == rhs.color;
}
