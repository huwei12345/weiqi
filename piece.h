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

    void load(const QString& str);

public:
    // 假设 Piece 类有一些属性，并重载了输出操作符
    friend std::ostream& operator<<(std::ostream& os, const Piece& p);
};
Q_DECLARE_METATYPE(Piece);

class JudgeInfo {
public:
    std::vector<std::vector<double>> whiteOwnership;
    float whiteWin;
    float whiteLoss;
    float noResult;
    float whiteLead;//白领先目数
    float whiteScoreSelfplay;//领先参考
    float whiteScoreSelfplaySq;//no
    float shorttermWinlossError;//whiteWin-whiteLoss
    std::vector<std::vector<float>> policy; //下一次可能的落子点(boardXSize * boardYSize浮动，包括可能的非法移动NAN) -下一步移动的策略分布
    int whiteground;
    int blackground;
    float judgeWhiteWin;//智能裁判结果
    void reset();
    //...
    bool parse(const QString &content);
    bool parseEnd(const QString &content);
    void print();
};
Q_DECLARE_METATYPE(JudgeInfo);
Q_DECLARE_METATYPE(JudgeInfo*);

class InfoMove {
public:
    Piece move;
    int visits;//累计计算量
    int edgeVisits;
    float utility;
    float winrate;//黑方视角
    float scoreMean;//黑方视角
    int order;
    std::vector<Piece> pv;
    void reset();
};

class AnalyzeInfo {
public:
    std::vector<InfoMove> infoMoveList;
    bool parse(const QString& content);

    // 打印 InfoMove 的内容
    void print() const;
};
Q_DECLARE_METATYPE(AnalyzeInfo);
Q_DECLARE_METATYPE(AnalyzeInfo*);
void showPoint(int row, int col, int color = -1);
QString showPiece(int row, int col, int color = -1);
QString showPiece(const Piece& piece);
QString colToChar(int col);
int charToCol(char col);
#endif // PIECE_H
