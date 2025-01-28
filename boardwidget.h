#ifndef BOARD_WIDGET_H
#define BOARD_WIDGET_H
#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QMouseEvent>
#include <QDebug>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stack>
#include <iostream>
#include <fstream>
#include <regex>
#include <set>
#include <QTreeWidget>
#include <QVariant>
#include "dingshishow.h"
#include "dingshishowwidget.h"
#include "gamesettings.h"
#include "piece.h"
#include "sgfparser.h"
#include "timecontrol.h"
#include <algorithm>
extern int dx[4];
extern int dy[4];

class TreeData {
public:
    std::weak_ptr<SGFTreeNode> node;
    int index;
};
Q_DECLARE_METATYPE(TreeData)


void showPoint(int row, int col, int color = -1);

QString showPiece(int row, int col, int color = -1);
QString showPiece(const Piece& piece);
QString colToChar(int col);



enum GameState {
    NOGAME = 0,
    DISCUSS = 1,
    PLAY = 2,
    OVER = 3,
    DoubleQuotation = 4,//复盘
};

//重构
class GoGameLogic : public QWidget {
    Q_OBJECT

public:
    explicit GoGameLogic(QWidget *parent = nullptr) : QWidget(parent){

    }
//    initializeBoard();// (初始化棋盘)
//    startNewGame();// (开始新游戏)
//    setBoardSize(int size);// (设置棋盘大小)
//    playMove(int x, int y);// (执行玩家落子)
//    isMoveLegal(int x, int y);// (检查落子是否合法)
//    checkCapture(int x, int y);// (检查是否有提子)
//    switchPlayer();// (切换玩家)
//    isGameOver();// (判断游戏是否结束)
//    calculateScore();// (计算得分)
//    undoMove();// (悔棋)
//    loadGameState();// (加载游戏状态)
//    saveGameState();// (保存游戏状态)

//    checkVictory();// (检查胜负)
//    printBoard();// (打印棋盘)

//    getCurrentBoardState(); //提供当前棋盘的状态，方便GameResearch类加载和使用。
//    getMoveHistory(); //提供当前棋局的历史记录，供研究模式分析使用。
//    checkGameOver(); //判断游戏是否结束，供研究模式在加载棋局后判断当前状态。

    std::vector<std::vector<Piece>> board;//棋盘状态
    std::vector<std::vector<Piece>> zeroBoard;// x y 2
    Qt::GlobalColor currentPlayer; //当前玩家
    //Player currentPlayer (当前玩家，黑或白)
    GameSettings settings; //(游戏规则设置)
    TimeControl timeControl; //(时间管理)

    GameState gameState; //游戏状态
    std::stack<std::vector<std::vector<Piece>>> MoveHistory; //(历史记录)
    std::vector<Piece> CapturedStones; //被提子列表
    int blackEaten;
    int whiteEaten;
    const int BoardSize = 19; //棋盘大小
    int GameOverFlag; //游戏结束标志
    std::vector<Piece> pieceSeq;//手数顺序


    //QPixmap blackPiece; // 黑棋图片
    //QPixmap whitePiece; // 白棋图片

    //std::stack<std::vector<std::vector<Piece>>> redoStack;  // 重做栈（用于重做）
    int moveNumber;//当前手数

    std::vector<std::pair<int, int>> blackLiberties;//黑气
    std::vector<std::pair<int, int>> whiteLiberties;//白气
    std::vector<std::pair<int, int>> eatenNowList;

    float tiemu;//贴目
    std::shared_ptr<SGFTreeNode> root;
    SGFParser sgfParser;

    QTreeWidget* pieceTree;
};


class GoBoardWidget : public QWidget {
    Q_OBJECT
public:
    explicit GoBoardWidget(QWidget *parent = nullptr) : QWidget(parent), hoverRow(-1), hoverCol(-1) {
        setMouseTracking(true);
        setFixedSize(640, 640); // 增加窗口大小，留出边距
        // 加载黑白棋子的图片:/images/black.png
        blackPiece = QPixmap(":/images/black.png"); // 使用资源文件
        blackPiece = blackPiece.scaled(QSize(30,30), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        whitePiece = QPixmap(":/images/white.png"); // 使用资源文件
        whitePiece = whitePiece.scaled(QSize(30,30), Qt::KeepAspectRatio, Qt::SmoothTransformation);

        // 如果你用的是文件路径，可以像这样加载图片
        // blackPiece = QPixmap("/path/to/black.png");
        // whitePiece = QPixmap("/path/to/white.png");

        board.assign(BOARDWIDTH, std::vector<Piece>(BOARDWIDTH));
        zeroBoard = board;
        currentPlayer = Qt::black;
        moveNumber = 1;
        allNumber = 1;
        blackEaten = 0;
        whiteEaten = 0;
        tiemu = 7.5;
        historyNode = nullptr;
        root = std::make_shared<SGFTreeNode>();
        root->boardHistory = zeroBoard;
        root->parent.reset();

        DingShiBook = nullptr;
        mStepN = 20;
        mTryMode = false;
        PracticeMode = false;
        seqIndex = -1;
        indexMap.assign(HEIGHT, std::vector<Filed*>(WIDTH, nullptr));
    }


    class Filed {
    public:
        int row;
        int col;
        int color;
        std::set<std::pair<int, int>> pieceFiled;
        std::vector<Filed*> aceFiled;
        std::vector<Filed*> roundFiled;
        std::vector<Filed*> neighborFiled;
        int eyeSize = 0;
        int eyeCnt = 0;
        bool alived = false;
        int belong = -1; //空属于黑还是白 0黑 1白 2共
    };

    // 打印棋盘（调试用）
    void printBoard() {
        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                std::cout << board[i][j].color << " ";
            }
            std::cout << "\n";
        }
    }
protected:
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event)
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        int boardSize = 19;
        int margin = 30; // 留出30像素的边距
        int gridSize = (width() - 2 * margin) / boardSize; // 计算实际棋盘格子大小

        // 绘制棋盘背景
        painter.fillRect(margin, margin, width() - 2 * margin, height() - 2 * margin, QColor(255, 223, 186));

        // 绘制棋盘线条
        QPen pen;
        pen.setColor(Qt::black);
        pen.setWidth(2);
        painter.setPen(pen);

        for (int i = 0; i < boardSize; ++i) {
            // 绘制纵向和横向的线
            painter.drawLine(margin + gridSize * i, margin, margin + gridSize * i, height() - margin * 2 - 10);
            painter.drawLine(margin, margin + gridSize * i, width() - margin * 2 - 10, margin + gridSize * i);
        }

        // 标注数字
        QFont font = painter.font();
        font.setPointSize(10);
        painter.setFont(font);

        // 竖线标注
        for (int i = 0; i < boardSize; ++i) {
            int x = margin + gridSize * i + gridSize / 2 - 20;
            int y = margin - 10; // 放在棋盘上方
            // 防止第一个数字标注与棋盘重合
            painter.drawText(x, y, colToChar(i));
        }

        // 横线标注
        for (int i = 0; i < boardSize; ++i) {
            int x = margin - 25; // 放在棋盘左侧
            int y = margin + gridSize * i + gridSize / 2 - 15;
            if (i >= 0)
                painter.drawText(x, y, QString::number(19 - i));
        }


        for (int i = 0; i < 19; i++) {
            for (int j = 0; j < 19; j++) {
                if (board[i][j].color == 1) {
                painter.drawPixmap(margin + j * gridSize - whitePiece.width() / 2,
                               margin + i * gridSize - whitePiece.height() / 2,
                               whitePiece);
                }
                else if (board[i][j].color == 0) {
                    painter.drawPixmap(margin + j * gridSize - blackPiece.width() / 2,
                                       margin + i * gridSize - blackPiece.height() / 2,
                                       blackPiece);
                }
            }
        }
        //跟新手数显示
        if (mTryMode == false) {
            updateMoveLabel(painter, gridSize);
        }
        else {
            updateTrySeq(painter, gridSize);
        }

        if (!mTryMode) {
            // 绘制鼠标悬浮位置的小方框
            if (hoverRow != -1 && hoverCol != -1 && isValid(hoverRow, hoverCol)) {
                if (currentPlayer == Qt::black) {
                    painter.setBrush(QBrush(Qt::black));
                    painter.drawRect(margin + hoverCol * gridSize - 5, margin + hoverRow * gridSize - 5, 10, 10);
                }
                else {
                    painter.setBrush(QBrush(Qt::white));
                    painter.drawRect(margin + hoverCol * gridSize - 5, margin + hoverRow * gridSize - 5, 10, 10);
                }
            }
        }
        else {
            if (hoverRow != -1 && hoverCol != -1 && isValid(hoverRow, hoverCol)) {
                if (mTryColor == 0) {
                    painter.setBrush(QBrush(Qt::black));
                    painter.drawRect(margin + hoverCol * gridSize - 5, margin + hoverRow * gridSize - 5, 10, 10);
                }
                else {
                    painter.setBrush(QBrush(Qt::white));
                    painter.drawRect(margin + hoverCol * gridSize - 5, margin + hoverRow * gridSize - 5, 10, 10);
                }
            }
        }

        for (auto p : blackLiberties) {
            painter.setBrush(QBrush(Qt::black));
            painter.drawRect(margin + p.second * gridSize - 5, margin + p.first * gridSize - 5, 10, 10);
        }

        for (auto p : whiteLiberties) {
            painter.setBrush(QBrush(Qt::white));
            painter.drawRect(margin + p.second * gridSize - 5, margin + p.first * gridSize - 5, 10, 10);
        }

        for (auto p : eatenNowList) {
            painter.setBrush(QBrush(Qt::green));
            painter.drawRect(margin + p.second * gridSize - 6, margin + p.first * gridSize - 6, 10, 12);
        }

        for (auto p : filedLiberties) {
            painter.setBrush(QBrush(Qt::green));
            painter.drawRect(margin + p.second * gridSize - 6, margin + p.first * gridSize - 6, 10, 12);
        }

        std::vector<std::vector<bool>> visited(HEIGHT, std::vector<bool>(WIDTH, false));
        for (int i = 0; i < 19; i++) {
            for (int j = 0; j < 19; j++) {
                if (indexMap[i][j] != nullptr && visited[i][j] == false) {
                    auto liber = indexMap[i][j];
                    if (liber->color == 2) {
                        for (auto p : liber->pieceFiled) {
                            visited[p.first][p.second] = true;
                            if (liber->belong == 0) {
                                painter.setBrush(QBrush(Qt::yellow));
                                painter.drawRect(margin + p.second * gridSize - 6, margin + p.first * gridSize - 6, 10, 12);
                            }
                            else if (liber->belong == 1) {
                                painter.setBrush(QBrush(Qt::gray));
                                painter.drawRect(margin + p.second * gridSize - 6, margin + p.first * gridSize - 6, 10, 12);
                            }
                        }
                    }
                }
            }
        }
        //当前棋子加一个小红旗标示
    }

    void updateMoveLabel(QPainter& painter, int gridSize) {
        // 获取最近 5 颗棋子的手数
        if (historyNode == nullptr) {
            return;
        }
        int margin = 30; // 留出30像素的边距
        // 构建显示文本
        QString text;
        int count = 5;
        SGFTreeNode* node = historyNode.get();
        QPen penold = painter.pen();
        std::vector<SGFTreeNode*> showPieces;
        int lastMoveNum = INT_MAX;
        while (count > 0) {
            if (node == nullptr) {
                break;
            }
            if (lastMoveNum <= node->moveNum) {
                break;
            }
            else {
                lastMoveNum = node->moveNum;
            }
            showPieces.push_back(node);
            auto p = node->parent.lock();
            if (p == nullptr) {
                break;
            }
            node = p.get();
            count--;
        }
        std::set<std::pair<int, int>> st;//避免多个数字显示在一个棋子上
        for (int i = 0; i < (int)showPieces.size(); i++) {
            auto& p = showPieces[i];
            auto piece = p->move;
            if (st.count(std::make_pair(piece.row, piece.col))) {
                continue;
            }
            if (board[piece.row][piece.col].color == 2) {
                //被提子后，这个子上的标记不显示
                continue;
            }
            st.insert(std::make_pair(piece.row, piece.col));
            int row = margin + piece.row * gridSize + 5;
            int col = 0;
            text = QString::number(p->moveNum);
            if (p->moveNum < 10) {
                col = margin + piece.col * gridSize - 5;
            }
            else if (p->moveNum >= 10 && p->moveNum < 100) {
                col = margin + piece.col * gridSize - 10;
            }
            else if (p->moveNum >= 100) {
                col = margin + piece.col * gridSize - 15;
            }
            QFont font = painter.font();
            //font.setFamily("Arial");           // 设置字体为 Arial
            font.setPointSize(10);             // 设置字体大小
            font.setBold(true);                // 设置加粗
            //font.setWeight(QFont::DemiBold);   // 设置半粗体
            painter.setFont(font);
            // 设置文本颜色
            QPen pen;
            if (piece.color == 0) {
                pen.setColor(Qt::white);            // 设置文本颜色为蓝色
                //painter.setBrush(QBrush(Qt::white));
            }
            else {
               pen.setColor(Qt::black);            // 设置文本颜色为蓝色
               //painter.setBrush(QBrush(Qt::red));
            }
            if (i == 0) {
                pen.setColor(Qt::red);
            }
            painter.setPen(pen);
            painter.drawText(col, row, text);
            count--;
        }
        painter.setPen(penold);

    }
    void updateTrySeq(QPainter& painter, int gridSize) {
        QPen penold = painter.pen();
        int margin = 30; // 留出30像素的边距
        QString text;
        std::set<std::pair<int, int>> st;//避免多个数字显示在一个棋子上
        for (int i = seqIndex; i >= 0; i--) {
            int moveNum = i + 1;
            auto piece = mTryModeSeq[i];
            if (st.count(std::make_pair(piece.row, piece.col))) {
                continue;
            }
            if (board[piece.row][piece.col].color == 2 || piece.color == 2) {
                //被提子后，这个子上的标记不显示
                continue;
            }
            st.insert(std::make_pair(piece.row, piece.col));
            int row = margin + piece.row * gridSize + 5;
            int col = 0;
            text = QString::number(moveNum);
            if (moveNum < 10) {
                col = margin + piece.col * gridSize - 5;
            }
            else if (moveNum >= 10 && moveNum < 100) {
                col = margin + piece.col * gridSize - 10;
            }
            else if (moveNum >= 100) {
                col = margin + piece.col * gridSize - 15;
            }
            QFont font = painter.font();
            //font.setFamily("Arial");           // 设置字体为 Arial
            font.setPointSize(10);             // 设置字体大小
            font.setBold(true);                // 设置加粗
            //font.setWeight(QFont::DemiBold);   // 设置半粗体
            painter.setFont(font);
            // 设置文本颜色
            QPen pen;
            if (piece.color == 0) {
                pen.setColor(Qt::white);            // 设置文本颜色为蓝色
                //painter.setBrush(QBrush(Qt::white));
            }
            else {
               pen.setColor(Qt::black);            // 设置文本颜色为蓝色
               //painter.setBrush(QBrush(Qt::red));
            }
            if (i == seqIndex) {
                pen.setColor(Qt::red);
            }
            painter.setPen(pen);
            painter.drawText(col, row, text);
        }
        painter.setPen(penold);
    }
    // 判断位置是否合法
    bool isValid(int x, int y) {
        return x >= 0 && x < BOARDWIDTH && y >= 0 && y < BOARDWIDTH;
    }

    // 检查一个区域是否是眼 8个位置都要判断，
    // TODO: 还需要判断是否周围被这个颜色包围，也可能是大眼，需要更细致的判断
    bool isEye(int x, int y, int color) {
        int rx[8] {1,-1,0,0,  1,1,-1,-1};
        int ry[8] {0,0,1,-1,  1,-1,1,-1};
        // 检查一个眼的条件：四周必须是空白或敌方棋子，且没有其他棋子存在
        // 一个有效的眼必须完全被一个颜色围住
        int qutorNum = 0;
        int allqutorNum = 0;
        //上下左右
        int orthogonalityNum = 0;
        for (int i = 0; i < 8; i++) {
            int nx = x + rx[i];
            int ny = y + ry[i];
            if (isValid(nx, ny)) {
                allqutorNum++;
                if (board[nx][ny].color == 2 || board[nx][ny].color == color) {
                    qutorNum++;
                    if (i < 4 && board[nx][ny].color == color) {
                        orthogonalityNum++;
                    }
                }
            }
        }
        if (allqutorNum == 3) {
            return qutorNum >= 3;
        }
        else if (allqutorNum == 5) {
            return qutorNum >= 5;
        }
        else if (allqutorNum == 8) {
            return orthogonalityNum == 4 && qutorNum >= 7;
        }
        return true;
    }

    bool isEye(std::vector<std::vector<Piece>> & boarder, int x, int y, int color) {
        int rx[8] {1,-1,0,0,  1,1,-1,-1};
        int ry[8] {0,0,1,-1,  1,-1,1,-1};
        // 检查一个眼的条件：四周必须是空白或敌方棋子，且没有其他棋子存在
        // 一个有效的眼必须完全被一个颜色围住
        int qutorNum = 0;
        int allqutorNum = 0;
        //上下左右
        int orthogonalityNum = 0;
        for (int i = 0; i < 8; i++) {
            int nx = x + rx[i];
            int ny = y + ry[i];
            if (isValid(nx, ny)) {
                allqutorNum++;
                if (boarder[nx][ny].color == 2 || boarder[nx][ny].color == color) {
                    qutorNum++;
                    if (i < 4 && boarder[nx][ny].color == color) {
                        orthogonalityNum++;
                    }
                }
            }
        }
        if (allqutorNum == 3) {
            return qutorNum >= 3;
        }
        else if (allqutorNum == 5) {
            return qutorNum >= 5;
        }
        else if (allqutorNum == 8) {
            return orthogonalityNum == 4 && qutorNum >= 7;
        }
        return true;
    }

    int isEyes(std::set<std::pair<int, int>> &liberties) {
        int bEye = 0;
        int wEye = 0;
        for (auto p : liberties) {
            if (isEye(p.first, p.second, 0)) {
                bEye++;
            }
            if (isEye(p.first, p.second, 1)) {
                wEye++;
            }
            qDebug() << "isEyes " << p.first << p.second;
        }
        if (bEye != 0 && wEye != 0) {
            qDebug() << "bCnt " << bEye << " wCnt " << wEye;
            return 0;//都不是
        }
        else if (bEye > 0) {
            return liberties.size();
        }
        else if (wEye > 0) {
            return 0 - (int)liberties.size();
        }
        return 0;
    }

    int isEyes(std::vector<std::vector<Piece>> & boarder, Filed* spaceFiled) {
        int bEye = 0;
        int wEye = 0;
        auto &liberties = spaceFiled->pieceFiled;

        if (liberties.size() == 2) {

        }
        //TODO:判断2和3的情况，应该判断的
        //如果这片区域大小大于4，并且只被一种颜色围住，怎么都有一个眼
        //是否需要单独判断2和3的情况
        if (liberties.size() >= 2) {
            if (spaceFiled->roundFiled.size() == 1) {
                int color = spaceFiled->roundFiled[0]->color;
                //只有一种颜色，说明被围住了
                if (color == 0) {
                    return liberties.size();
                }
                else if (color == 1) {
                    return 0 - (int)liberties.size();
                }
                else {
                    qDebug() << "ERRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR";
                }
            }
        }

        //判断每个点是否是眼，并不完全合理，即时是一大片空，每个点也不一定是眼的形状（指4面围住这个点，4角占三个）
        for (auto p : liberties) {
            if (isEye(boarder, p.first, p.second, 0)) {
                bEye++;
            }
            if (isEye(boarder, p.first, p.second, 1)) {
                wEye++;
            }
            qDebug() << "isEyes " << p.first << p.second;
        }
        if (bEye != 0 && wEye != 0) {
            qDebug() << "bCnt " << bEye << " wCnt " << wEye;
            return 0;//都不是
        }
        else if (bEye > 0) {
            return liberties.size();
        }
        else if (wEye > 0) {
            return 0 - (int)liberties.size();
        }
        return 0;
    }

    //当不是眼时，判断是否能一手棋做成眼
    bool canBeEye();

    //判断某块棋能否活棋，1.具备两眼。 2.具备一眼，并能一手再做一眼 (3.可以通过对杀将对手杀死.)
    //不能活棋 1.无眼 2.具备一眼，但不能一手棋再做一眼
    bool isAlive(std::set<std::pair<int, int>> &liberties) {
        //游戏终局除了双活的情况。一个空要么是黑的眼，要么是白的眼，如果无法判定，说明这个空没下完，无法点目。
        auto r = liberties.begin();
        int color = board[r->first][r->second].color;
        std::set<std::pair<int, int>> visited;
        int eyeCount = 0;
        for (auto p : liberties) {
            int row = p.first;
            int col = p.second;
            for (int i = 0; i < 4; i++) {
                int nx = row + dx[i];
                int ny = col + dy[i];
                if (!isValid(nx, ny) || board[nx][ny].color != 2) {
                    continue;
                }
                //floodFill(nx, ny);
//                int size = isEye(spaceLiberties, color);//返回是否是眼，是哪种颜色的眼
//                if (size > 0) {
//                    eysCount++;
//                    spaceVisited.insert(spaceLiberties);
//                }
            }
        }
//        if (eyeCount > 2 || maxEysSize > 6) {
//            return true;
//        }
        //遍历周围所有的气，对这个气进行flood算法。

        //如果这个空四周既有黑，右有白，说明无法判定，第一轮先不判定。
        //第一轮先判定可以判定的眼，并确定黑白，以及它所属的棋块。
        //第一轮结束后，标定已经可以确定活棋的棋块。并将这些眼加入visited中。
        //第二轮继续遍历空，对所有的未判定空，判定是否有双活的情况。
        //第三轮继续遍历空，如果这个空的几个周围都是活棋，说明没有终局，这是一个单官。
        //如果一边是确定的活棋，一边是不确定的活棋。先保留，可能存在双活。
    }


    //判断某块棋能否活棋，1.具备两眼。 2.具备一眼，并能一手再做一眼 (3.可以通过对杀将对手杀死.)
    //不能活棋 1.无眼 2.具备一眼，但不能一手棋再做一眼
    bool isAlive(std::vector<std::vector<Piece>> &boarder, Filed* filed) {
        //游戏终局除了双活的情况。一个空要么是黑的眼，要么是白的眼，如果无法判定，说明这个空没下完，无法点目。
        int count = 0;
        int size = 0;
        int maxSize = 0;
        for (auto &p : filed->aceFiled) {
            size = isEyes(boarder, p);
            if (filed->color == 1) {
                size = -size;
            }
            if (size > 0) {
                count++;
                p->belong = filed->color;
            }
            maxSize = std::max(maxSize, size);
        }
        filed->eyeSize = maxSize;
        filed->eyeCnt = count;
        if (maxSize >= 5) {
            return true;
        }
        if (count >= 2) {
            return true;
        }
        return false;
    }

    bool judgeJieZheng(std::vector<std::vector<Piece>>& boarder) {
        qDebug() << "jiezheng start";
        if (mTryMode) {
            return true;
        }
        //TODO: 三劫循环应看6手之前 四届循环看8手之前。
        //SGFTreeNode* node = historyNode;
        auto p = historyNode->parent.lock();
        if (p == nullptr) {
            return true;
        }
        std::vector<std::vector<Piece>>& boardp = p->boardHistory;
        bool equal = true;
        for (int i = 0; i < 19; i++) {
            for (int j = 0; j < 19; j++) {
                if (boardp[i][j].color != boarder[i][j].color) {
                    equal = false;
                    break;
                }
            }
        }

        //前前手相等，不能下
        if (equal == true) {
            return false;
        }
        return true;
    }

    //大眼
    //1空 可能有眼 可能没眼
    //2空 可能没眼，可能后手眼，可能先手眼。
    //3空 可能没眼，可能有先手1眼，可能有后手一眼。
    // 4空：只有一种情况没眼，就是4空是一个正方，四角都是白棋，其他至少是后手眼。   还有一种，草帽四，可能没眼。
    // 5空：一定有一眼
    //DONE:数气
    int getAceOfPoint(std::vector<std::vector<Piece>>& boarder , int row, int col, int color) {
        std::queue<std::pair<int, int>> PeaceQue;
        bool book[19][19];
        int ace = 0;
        bool spaceblock[19][19];//空也不能多数
        for (int i = 0; i < 19; i++) {
            for (int j = 0 ; j < 19; j++) {
                book[i][j] = 0;
                spaceblock[i][j] = 0;
            }
        }
        PeaceQue.push(std::make_pair(row, col));
        while (!PeaceQue.empty()) {
             std::pair<int,int> p = PeaceQue.front();
             PeaceQue.pop();
             //周围同色点加入队列
             if (p.first > 0) {
                 if (boarder[p.first - 1][p.second].color == color && !book[p.first - 1][p.second]) {
                     book[p.first - 1][p.second] = 1;
                     PeaceQue.push(std::make_pair(p.first - 1, p.second));
                 }
                 if (boarder[p.first - 1][p.second].color == 2 && spaceblock[p.first - 1][p.second] == 0) {
                     spaceblock[p.first - 1][p.second] = 1;
                     ace++;
                 }
             }
             if (p.first < BOARDWIDTH - 1) {
                 if (boarder[p.first + 1][p.second].color == color && !book[p.first + 1][p.second]) {
                     book[p.first + 1][p.second] = 1;
                     PeaceQue.push(std::make_pair(p.first + 1, p.second));
                 }
                 if (boarder[p.first + 1][p.second].color == 2 && spaceblock[p.first + 1][p.second] == 0) {
                     spaceblock[p.first + 1][p.second] = 1;
                     ace++;
                 }
             }
             if (p.second > 0) {
                 if (boarder[p.first][p.second - 1].color == color && !book[p.first][p.second - 1]) {
                     book[p.first][p.second - 1] = 1;
                     PeaceQue.push(std::make_pair(p.first, p.second - 1));
                 }
                 if (boarder[p.first][p.second - 1].color == 2 && spaceblock[p.first][p.second - 1] == 0) {
                     spaceblock[p.first][p.second - 1] = 1;
                     ace++;
                 }
             }
             if (p.second < BOARDWIDTH - 1) {
                 if (boarder[p.first][p.second + 1].color == color && !book[p.first][p.second + 1]) {
                     book[p.first][p.second + 1] = 1;
                    PeaceQue.push(std::make_pair(p.first, p.second + 1));
                 }
                 if (boarder[p.first][p.second + 1].color == 2 && spaceblock[p.first][p.second + 1] == 0) {
                     spaceblock[p.first][p.second + 1] = 1;
                     ace++;
                 }
             }
        }
        return ace;
    }

    bool hasAceOfPeace(int row, int col, int color) {
        //可优化
        return getAceOfPoint(board, row, col, color) > 0;
    }

    //将要放入的棋子的颜色
    //可以假设将此子作为另一个颜色的子，如果加上这个子后，这部分是没气，那么是提子

    //判断一个子周围4个是否有异色
    bool hasDiff(std::vector<std::vector<Piece>> &boarder, int row, int col, int color) {
        bool flag = false;
        for (int i = 0; i < 4; i++) {
            if (row + dx[i] >= 0 && row + dx[i] < 19 && col + dy[i] >= 0 && col + dy[i] < 19
                    && boarder[row + dx[i]][col + dy[i]].color != color) {
                flag = true;
                break;
            }
        }
        return flag;
    }


    int eatChess(std::vector<std::vector<Piece>> &boarder, int row, int col, int color) {
        auto &newBoard = boarder;
        qDebug() << showPiece(row, col, color);
        newBoard[row][col].color = color;
        //int ace = getAceOfPoint(newBoard, row, col, color);
        int eatenNum = 0;
        int safeBook[19][19];
        for (int i = 0; i < 4; i++) {
            if (row + dx[i] >= 0 && row + dx[i] < 19 && col + dy[i] >= 0 && col + dy[i] < 19
                    && newBoard[row + dx[i]][col + dy[i]].color == !color) {
                int num = getAceOfPoint(newBoard, row + dx[i], col + dy[i], newBoard[row + dx[i]][col + dy[i]].color);
                if (num == 0) {
                    //删掉这一片
                    eatenNum += erasePiece(newBoard, row + dx[i], col + dy[i], safeBook);
                }
            }
        }

        board = newBoard;
        return eatenNum;
    }

    //删除此子连片的子，已确保这片棋是0气的
    int erasePiece(std::vector<std::vector<Piece>>& boarder, int row, int col, int (&safeBook)[19][19]) {
        std::queue<std::pair<int, int>> que;
        int color = boarder[row][col].color;
        qDebug() << showPiece(row, col, color);
        que.push(std::make_pair(row, col));
        int eaten = 0;
        while (!que.empty()) {
            std::pair<int,int> p = que.front();
            row = p.first;
            col = p.second;
            que.pop();
            if (safeBook[row][col] == 1) {
                continue;
            }
            qDebug() << showPiece(row, col, color) << " is eaten";
            if (boarder[row][col].color != 2) {
                boarder[row][col].color = 2;
                if (color == 0) {
                    whiteEaten++;
                }
                else if (color == 1) {
                    blackEaten++;
                }
                eaten++;
            }
            for (int i = 0; i < 4; i++) {
                int xx = row + dx[i];
                int yy = col + dy[i];
                if (xx >= 0 && xx < 19 && yy >= 0 && yy < 19
                        && boarder[xx][yy].color == color) {
                    if (safeBook[xx][yy] == 0) {
                        que.push(std::make_pair(xx, yy));
                    }
                }
            }
            safeBook[row][col] = 1;
        }
        return eaten;
    }

    bool checkAllowPut(int row, int col, int color) {
        if (isOccupied(row, col)) {
            return false;
        }
        auto newBoard = board;
        newBoard[row][col].color = color;
        //开始吃子
        int eatenNum = 0;
        int safeBook[19][19];
        for (int i = 0; i < 19; i++) {
            for (int j = 0; j < 19; j++) {
                safeBook[i][j] = 0;
            }
        }
        //如果上下左右有没气的棋
        for (int i = 0; i < 4; i++) {
            int xx = row + dx[i];
            int yy = col + dy[i];
            if (xx >= 0 && xx < 19 && yy >= 0 && yy < 19
                    && newBoard[xx][yy].color == !color) {
                int num = getAceOfPoint(newBoard, xx, yy, newBoard[xx][yy].color);
                if (num == 0) {
                    //删掉这一片
                    eatenNum += erasePiece(newBoard, xx, yy, safeBook);
                }
            }
        }
        int ace = getAceOfPoint(newBoard, row, col, color);
        if (eatenNum == 1) {
            //判断打劫
            bool ret = judgeJieZheng(newBoard);
            if (!ret) {
                //不可提劫
                qDebug() << "can not put because of JieZheng";
                return false;
            }
        }
        if (eatenNum != 0) {
            board = newBoard;
        }
        else if (eatenNum == 0 && ace == 0) {
            //不能添加
            qDebug() << "禁止放入";
            return false;
        }
        else if (ace < 0) {
            qDebug() << "Fatial Error\n";
            return false;
        }
        return true;
    }

    bool putPiece(std::shared_ptr<SGFTreeNode>& node, int OtherBranchPut) {
        int row = node->move.row;
        int col = node->move.col;
        int color = node->move.color;
        if (checkAllowPut(row, col, color)) {
            putPiece(row, col, color);
            showPoint(row, col, color);
            setMoveNum(node, OtherBranchPut);
            currentPlayer = (color == 0 ? Qt::white : Qt::black);
            //pieceSeq.push_back(board[row][col]);
            return true;
        }
        else {
            qDebug() << "not allow put ";
            return false;
        }
        return true;
    }

    void putPiece(int row, int col, int color) {
        board[row][col].color = color;
        board[row][col].row = row;
        board[row][col].col = col;
        //board[row][col].moveNumber = moveNumber++;  // 记录下棋的手数
        //pieceSeq.push_back(board[row][col]);
    }

    bool putPieceTry(int row, int col, int color) {
        if (checkAllowPut(row, col, color)) {
            putPiece(row, col, color);
            showPoint(row, col, color);
            return true;
        }
        else {
            qDebug() << "not allow put ";
            return false;
        }
        return true;
    }

    void delPiece(int row, int col) {
        board[row][col].color = 2;
        board[row][col].row = row;
        board[row][col].col = col;
        //board[row][col].moveNumber = moveNumber++;  // 记录下棋的手数
        //pieceSeq.push_back(board[row][col]);
    }
    //改造putPiece，在落子时可以在TreeWidget上添加
    //添加的N种情况：
    // 1. 当前节点没有其他分支，直接在当前节点的move添加，并更新history
    // 2. 当前节点已有分支或者move后续， 那么作为一个分支，但这样需要拆分SGFNode，因为它在move的中间断开了
    //所以需要重构SGFTree，不能已vector作为数据，而应以一个Piece作为节点。
    //先重构完再考虑

    void setMoveNum(std::shared_ptr<SGFTreeNode>& node, int OtherBranchPut) {
        auto p = node->parent.lock();
        if (p == nullptr || OtherBranchPut) {
            node->moveNum = 1;
        }
        else {
            node->moveNum = p->moveNum + 1;
        }
        if (!OtherBranchPut) {
            //不计入总分支长度与undo redo逻辑
            if (allNumber < node->moveNum) {
                allNumber = node->moveNum;
            }
            //TODO:这里需要改吗？上一个节点 historyNode目前对应所有结点，也可以只对应主线结点。
        }
        node->move.moveNumber = node->moveNum;
        board[node->move.row][node->move.col].moveNumber = node->moveNum;  // 记录下棋的手数
        node->boardHistory = board;

        historyNode = node;
    }

    //这个具体的排列逻辑还是要理一下
    QTreeWidgetItem* makeTreeItem(std::shared_ptr<SGFTreeNode> node) {
        if (node == nullptr || node == root) {
            return nullptr;
        }
        QTreeWidgetItem* item = new QTreeWidgetItem;
        auto piece = node->move;
        QString str = colToChar(piece.col) + QString::number(19 - piece.row) + " " + (piece.color == 0 ? "B" : "W");
        QString str2 = QString::number(node->moveNum) + "  ";
        //QString::number(node->move.moveNumber) + " is " + (isBranch ? "yes" : "no")
        item->setText(0, str);
        item->setText(1, str2);
        treeItemMap[node] = item;
        TreeData data;
        data.node = node;
        data.index = node->moveNum;
        QVariant variant = QVariant::fromValue(data);
        item->setData(0, 1, variant);
        return item;
    }


    bool isNodeDizi(std::shared_ptr<SGFTreeNode> node) {
        if (node == nullptr || node == root) {
            return true;
        }
        auto pa = node->parent.lock();
        if (pa == nullptr) {
            qDebug() << "Dizi Error";
            return true;
        }
        return pa->branches.size() == 1;
    }

    /*
     *原则是不要产生误解，当一个节点除了嫡子之外，还有其他分支时，其他分支都作为(可展开状态）。
     * 当一个节点只有嫡子时，可与嫡子并列，（但若该节点作为可展开状态时，嫡子作为子）
     * 其实以上逻辑是通用的，并不分顶层还是非顶层，因为把root节点也算在内了。但multigo事实上把主线做了区分。
     *
    1.当顶层时，嫡分支直接保持顶层。 庶分支在二层。
    2.非顶层时，嫡分支保持原层。庶分支在在下一层。
    3.当某节点为独子分支时，整个分支在下一层。
    4.当某节点为非独子分支时，整个分支以分支的第一个节点为头，其余节点以这个节点为父展开。
    5.当某节点由独自变为非独子时，将当前节点压缩，
    6.当某节点由非独子变为独子时，将释放节点。
    */
    //仅tree显示修改，不改变SGFTreeNode内部结构
    void showTreeItem(std::shared_ptr<SGFTreeNode> node) {
        auto item = makeTreeItem(node);
        auto parent = node->parent.lock();
        if (parent == nullptr) {
            return;
        }
        QTreeWidgetItem* parentItem = treeItemMap[parent];//获取父节点的treeWidget

        if (parent == root) {
            if (parent->branches.size() == 1) {
                pieceTree->addTopLevelItem(item);
            }
            else if (parent->branches.size() == 2) {
                //此时说明是在空棋盘上,且第一个子至少有两个分支。要先压缩原分支，然后将新分支压缩为分支
                if (parent->branches.size() == 2) {
                    treeCompress(root, nullptr);
                    pieceTree->addTopLevelItem(item);
                }
            }
            else {
                pieceTree->addTopLevelItem(item);
            }
            return;
        }

        if (parent->branches.size() == 1) {
            //没有后续，
            auto grandpa = parent->parent.lock();
            //如果父节点只有一个子，说明刚添加的子是唯一的分支
            //即使是独子，也要考虑是否应该加在兄弟分支，还是子分支。
            //应该加在兄弟分支，如果父分支是独分支时或者顶分支时
            //应该加在子分支，如果父分支是非独分支时。
            if (grandpa == nullptr || grandpa->branches.size() == 1) {
                QTreeWidgetItem* grandpaItem = parentItem->parent();//并不是真的grandpa对应的item
                if (grandpaItem == nullptr) {
                    pieceTree->addTopLevelItem(item);
                }
                else {
                    grandpaItem->addChild(item);
                }
            }
            else {
                parentItem->addChild(item);
            }
        }
        else if (parent->branches.size() == 2) {
            //由独变为非独
            //将之前的独子分支压缩，再添加新分支
            if (parentItem->childCount() == 0) {
                parentItem->addChild(item);
            }
            else {
                compress(parent->branches[0]);
                parentItem->addChild(item);
            }
        }
        else {
            parentItem->addChild(item);
        }
    }

    void addFrontChild(QTreeWidgetItem* parent, QTreeWidgetItem* son) {
        QList<QTreeWidgetItem*> wlist;
        for (int i = 0; i < parent->childCount(); i++) {
            wlist.push_back(parent->child(i));
        }
        for (int i = 0; i < wlist.size(); i++) {
            parent->removeChild(wlist[i]);
        }
        parent->addChild(son);
        for (int i = 0; i < wlist.size(); i++) {
            parent->addChild(wlist[i]);
        }
    }
    //单纯压缩一个节点，之前node和之后的节点为顺序分支关系，现在要以node节点为一个节点，压缩这个分支
    void compress(std::shared_ptr<SGFTreeNode> node) {
        QTreeWidgetItem* item = treeItemMap[node];
        if (node->branches.size() == 1) {
            //入主
            auto parent = node->parent.lock();
            if (parent == nullptr) {
                qDebug() << "Fatil Error";
                return;
            }
            QTreeWidgetItem* parentItem = item->parent();
            int index = parentItem->indexOfChild(item);
            QList<QTreeWidgetItem*> wlist;
            for (int i = index + 1; i < parentItem->childCount(); i++) {
                wlist.push_back(parentItem->child(i));
            }
            for (int i = 0; i < wlist.size(); i++) {
                parentItem->removeChild(wlist[i]);
                item->addChild(wlist[i]);
            }
        }
        else {
            //多路合并
            auto dd = node->branches[0];
            compress(dd);
            auto parent = node->parent.lock();
            if (parent == nullptr) {
                qDebug() << "Fatil Error";
                return;
            }
            QTreeWidgetItem* parentItem = item->parent();
            parentItem->removeChild(treeItemMap[dd]);
            //加在最前面
            addFrontChild(item, treeItemMap[dd]);//头部添加
        }
    }
    void treeCompress(std::shared_ptr<SGFTreeNode> node, QTreeWidgetItem* item) {
        //还有一种情况，就是这个点虽然在tree上没有分支，但是有2个子。也要压缩。
        if (node->branches.size() != 2) {
            return;
        }
        if (item == nullptr) {
            QList<QTreeWidgetItem*> wlist;
            QTreeWidgetItem *sonItem = pieceTree->topLevelItem(0);
            for (int i = 1; i < pieceTree->topLevelItemCount(); ++i) {
                wlist.push_back(pieceTree->topLevelItem(i));
            }
            for (int i = 0; i < wlist.size(); i++) {
                 pieceTree->takeTopLevelItem(1);
                 sonItem->addChild(wlist[i]);
            }
            return;
        }
        if (item->childCount() == 0) {
            auto ppitem = item->parent();
            if (ppitem == nullptr) {
                return;
            }
            //平层子压缩
            if (item != ppitem->child(0)) {
                return;
            }
            auto dage = ppitem->child(1);//新大哥
            QList<QTreeWidgetItem*> wlist;
            for (int i = 2; i < ppitem->childCount(); i++) {
                wlist.push_back(ppitem->child(i));
            }
            for (int i = 0; i < wlist.size(); i++) {
                 ppitem->removeChild(wlist[i]);
                 dage->addChild(wlist[i]);
            }
            ppitem->removeChild(dage);
            item->addChild(dage);
        }
        else {
            QList<QTreeWidgetItem*> wlist;
            for (int i = 0; i < item->childCount(); i++) {
                wlist.push_back(item->child(i));
            }
            for (int i = 1; i < wlist.size(); i++) {
                item->removeChild(wlist[i]);
                wlist[0]->addChild(wlist[i]);
            }
        }
    }

    void onLeftClickTry(QMouseEvent *event) {
        int margin = 30;
        int gridSize = (width() - 2 * margin) / 19;
        int row = std::round((float)(event->y() - margin) / (float)gridSize);
        int col = std::round((float)(event->x() - margin) / (float)gridSize);
        if (!isValid(row, col)) {
            return;
        }
        int color = currentPlayer == Qt::black ? 0 : 1;
        qDebug() << showPiece(row, col, color);

        if (!isValid(row, col)) {
            return;
        }
        // 检查该位置是否已经有棋子
        if (isOccupied(row, col)) {
            return; // 如果该位置已被占据，则不放置棋子
        }
        qDebug() << "putPiece " << showPiece(row, col, mTryColor);
        //TODO:此处putPiece应该符合吃子规则和填子规则。
        putPieceTry(row, col, mTryColor);
        if (seqIndex != -1 && seqIndex < (int)mTryModeSeq.size() - 1) {
            mTryModeSeq.erase(mTryModeSeq.begin() + seqIndex + 1, mTryModeSeq.end());
        }
        mTryModeSeq.emplace_back(row, col, mTryColor);
        seqIndex++;
        while (!redoTryStack.empty()) {
            redoTryStack.pop();
        }
        undoTryStack.push(board);
        mTryMode = true;
        mTryColor = !mTryColor;
        repaint();
    }

    void onLeftClick(QMouseEvent *event) {
        if (mTryMode == true) {
            onLeftClickTry(event);
            return;
        }
        int margin = 30;
        int gridSize = (width() - 2 * margin) / 19;
        int row = std::round((float)(event->y() - margin) / (float)gridSize);
        int col = std::round((float)(event->x() - margin) / (float)gridSize);
        if (!isValid(row, col)) {
            return;
        }
        // 输出点击的棋盘坐标
        // 检查该位置是否已经有棋子
        int color = currentPlayer == Qt::black ? 0 : 1;
        qDebug() << showPiece(row, col, color);
        //检查分支上已经有这个子了，就不用再放了，移动一下状态就行了。
        if (historyNode != nullptr) {
            for (auto n : historyNode->branches) {
                if (n->move.row == row && n->move.col == col && n->move.color == color) {
                    jumptoPiece(n);
                    return;
                }
            }
        }
        if (isOccupied(row, col)) {
            return; // 如果该位置已被占据，则不放置棋子
        }
        // 交替放置棋子
        if (checkAllowPut(row, col, color)) {
            putPiece(row, col, color);
            std::shared_ptr<SGFTreeNode> node = std::make_shared<SGFTreeNode>();
            Piece piece;
            piece.row = row; piece.col = col; piece.color = color;
            node->move = piece;
            bool isOtherBranch = false;
            if (historyNode != nullptr) {
                if (historyNode->branches.size() >= 1) {
                    isOtherBranch = true;
                }
                historyNode->branches.push_back(node);
                node->parent = historyNode;
            }
            else if (historyNode == nullptr) {
                root->branches.push_back(node);
                node->parent = root;
            }
            setMoveNum(node, isOtherBranch);
            showTreeItem(historyNode);
            currentPlayer = (currentPlayer == Qt::black ? Qt::white : Qt::black);
        }
        // 触发重绘
        repaint();
    }

    void onRightClick(QMouseEvent *event) {
        int margin = 30;
        int gridSize = (width() - 2 * margin) / 19;
        int row = std::round((float)(event->y() - margin) / (float)gridSize);
        int col = std::round((float)(event->x() - margin) / (float)gridSize);
        if (!isValid(row, col)) {
            return;
        }
        // 输出点击的棋盘坐标
        // 检查该位置是否已经有棋子
        if (isOccupied(row, col)) {
            qDebug() << showPiece(row, col, board[row][col].color) << " Ace: " << getAceOfPoint(board, row, col, board[row][col].color);
        }
        else {
            qDebug() << "block  row " << row << " col "<<  col;
        }
    }

    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::RightButton) {
            onRightClick(event);
        } else if (event->button() == Qt::LeftButton) {
            onLeftClick(event);
        }
    }


    void mouseMoveEvent(QMouseEvent *event) override {
        int margin = 30;
        int gridSize = (width() - 2 * margin) / 19;

        int row = std::round((float)(event->y() - margin) / (float)gridSize);
        int col = std::round((float)(event->x() - margin) / (float)gridSize);
        // 如果鼠标位置发生变化，更新坐标并触发重绘
        if (row != hoverRow || col != hoverCol) {
            hoverRow = row;
            hoverCol = col;

            // 触发窗口重绘
            update();
        }
    }

public:
    void jumptoPiece(std::shared_ptr<SGFTreeNode> node) {
        if (historyNode != nullptr) {
            qDebug() << "before jump " << historyNode->moveNum;
        }
        if (node == nullptr) {
            qDebug() << "can not jump to ";
            return;
        }
        if (historyNode == node) {
            return;
        }
        historyNode = node;
        Piece piece = historyNode->move;
        board = historyNode->boardHistory;
        currentPlayer = piece.color == 0 ? Qt::white : Qt::black;
        qDebug() << "jump " << historyNode->moveNum << " board " << board.size();
        QTreeWidgetItem* item = treeItemMap[historyNode];
        pieceTree->setCurrentItem(item);
        repaint();
    }

    std::shared_ptr<SGFTreeNode> jumptoPiece(int index) {
        if (index == 0) {
            jumptoPiece(root);
            return root;
        }
        if (index <= 0 || index > allNumber) {
            qDebug() << "error index " << index;
        }
        if (root == nullptr || root->branches.size() == 0) {
            return nullptr;
        }
        auto node = root->branches[0];
        while (index != 1) {
            if (node->branches.size() > 0) {
                node = node->branches[0];
            }
            else {
                qDebug() << "can not jump to " << index;
            }
            index--;
        }
        jumptoPiece(node);
        return node;
    }

    void undo() {
        if (mTryMode == true) {
            undoTry();
            return;
        }
        if (historyNode == nullptr) {
            return;
        }
        qDebug() << "before undo " << historyNode->moveNum;
        auto p = historyNode->parent.lock();
        if (p == nullptr) {
            historyNode = nullptr;
            board = zeroBoard;
            currentPlayer = Qt::black;
            qDebug() << "can not undo";
            repaint();
            return;
        }
        historyNode = p;
        board = historyNode->boardHistory;
        currentPlayer = currentPlayer == Qt::black ? Qt::white : Qt::black;
        qDebug() << "undo " << historyNode->moveNum;
        QTreeWidgetItem* item = treeItemMap[historyNode];
        pieceTree->setCurrentItem(item);
        repaint();
    }

    // 重做撤销的操作
    //未考虑分支变化，只考虑主变化
    void redo() {
        if (mTryMode == true) {
            redoTry();
            return;
        }
        if (root == nullptr) {
            return;
        }
        if (historyNode == nullptr) {
            //空棋盘
            historyNode = root;
            board = historyNode->boardHistory;
            currentPlayer = Qt::black;
            qDebug() << "redo " << historyNode->moveNum << " board " << board.size();
            repaint();
            return;
        }
        if (historyNode->branches.size() == 0) {
            //终局不动
            qDebug() << "can not redo";
            repaint();
            return;
        }
        qDebug() << "before redo " << historyNode->moveNum;
        historyNode = historyNode->branches[0];
        board = historyNode->boardHistory;
        currentPlayer = currentPlayer == Qt::black ? Qt::white : Qt::black;
        qDebug() << "after redo " << historyNode->moveNum;
        QTreeWidgetItem* item = treeItemMap[historyNode];
        pieceTree->setCurrentItem(item);
        repaint();
    }


    void undoTry() {
        if (undoTryStack.empty()) {
            return;
        }
        auto b = undoTryStack.top();
        undoTryStack.pop();
        redoTryStack.push(b);
        if (undoTryStack.empty()) {
            if (historyNode != nullptr) {
                board = historyNode->boardHistory;
            }
            else {
                board = zeroBoard;
            }
        }
        else {
            board = undoTryStack.top();
        }
        seqIndex--;
        repaint();
    }

    void redoTry() {
        if (redoTryStack.empty()) {
            return;
        }
        auto b = redoTryStack.top();
        redoTryStack.pop();
        undoTryStack.push(b);
        if (undoTryStack.empty()) {
            if (historyNode != nullptr) {
                board = historyNode->boardHistory;
            }
            else {
                board = zeroBoard;
            }
        }
        else {
            board = undoTryStack.top();
        }
        seqIndex++;
        repaint();
    }

    void selectPreviousItem() {
            QTreeWidgetItem *currentItem = pieceTree->currentItem();
            if (currentItem) {
                QTreeWidgetItem *prevItem = pieceTree->itemAbove(currentItem);
                if (prevItem) {
                    pieceTree->setCurrentItem(prevItem);
                }
            }
        }

        void selectNextItem() {
            QTreeWidgetItem *currentItem = pieceTree->currentItem();
            if (currentItem) {
                QTreeWidgetItem *nextItem = pieceTree->itemBelow(currentItem);
                if (nextItem) {
                    pieceTree->setCurrentItem(nextItem);
                }
            }
        }

public:
        // 捕获按键事件
        void onKeyPressEvent(QKeyEvent *event) {
           if (event->key() == Qt::Key_Z && event->modifiers() == Qt::ControlModifier) {
               undo();  // Ctrl + Z 执行撤销

           } else if (event->key() == Qt::Key_X && event->modifiers() == Qt::ControlModifier) {
               redo();  // Ctrl + X 执行重做
           } else if (event->key() == Qt::Key_E && event->modifiers() == Qt::ControlModifier) {
               int margin = 30;
               int gridSize = (width() - 2 * margin) / 19;
               QPoint mousePos = this->mapFromGlobal(QCursor::pos());  // 获取鼠标在窗口中的位置
               int row = std::round((float)(mousePos.y() - margin) / (float)gridSize);
               int col = std::round((float)(mousePos.x() - margin) / (float)gridSize);

               // 输出点击的棋盘坐标
               // 检查该位置是否已经有棋子
               if (isOccupied(row, col)) {
                   qDebug() << "not black";
                   return; // 如果该位置已被占据，则不放置棋子
               }
               qDebug() << showPiece(row, col, 2) << " is BEye ? " << isEye(row, col, 0);
               qDebug() << showPiece(row, col, 2) << " is WEye ? " << isEye(row, col, 1);
           } else if (event->key() == Qt::Key_R && event->modifiers() == Qt::ControlModifier) {
               int margin = 30;
               int gridSize = (width() - 2 * margin) / 19;
               QPoint mousePos = this->mapFromGlobal(QCursor::pos());  // 获取鼠标在窗口中的位置
               int row = std::round((float)(mousePos.y() - margin) / (float)gridSize);
               int col = std::round((float)(mousePos.x() - margin) / (float)gridSize);
               if (isOccupied(row, col)) {
                   qDebug() << "not black";
                   return; // 如果该位置已被占据，则不放置棋子
               }
               int color = (currentPlayer == Qt::black ? 0 : 1);
               std::vector<std::vector<Piece>> ans;
               remember(board, row, col, color, mStepN, ans);
           } else if (event->key() == Qt::Key_T && event->modifiers() == Qt::ControlModifier) {
               //调试用
               DingShiShow* ds = new DingShiShow();
               ds->show();
           } else if ((event->key() == Qt::Key_B || event->key() == Qt::Key_W) && event->modifiers() == Qt::ControlModifier) {
               if (!mTryMode) {
                   qDebug() << "please open TryMode";
                   return;
               }
               bool isBlack = (event->key() == Qt::Key_B);
               int margin = 30;
               int gridSize = (width() - 2 * margin) / 19;
               QPoint mousePos = this->mapFromGlobal(QCursor::pos());  // 获取鼠标在窗口中的位置
               int row = std::round((float)(mousePos.y() - margin) / (float)gridSize);
               int col = std::round((float)(mousePos.x() - margin) / (float)gridSize);
               if (!isValid(row, col)) {
                   return;
               }
               // 检查该位置是否已经有棋子
               if (isOccupied(row, col)) {
                   return; // 如果该位置已被占据，则不放置棋子
               }
               qDebug() << "putPiece " << showPiece(row, col, isBlack ? 0 : 1);
               putPieceTry(row, col, isBlack ? 0 : 1);
               if (seqIndex != -1 && seqIndex < (int)mTryModeSeq.size() - 1) {
                   mTryModeSeq.erase(mTryModeSeq.begin() + seqIndex + 1, mTryModeSeq.end());
               }
               mTryModeSeq.emplace_back(row, col, isBlack ? 0 : 1);
               seqIndex++;
               while (!redoTryStack.empty()) {
                   redoTryStack.pop();
               }
               undoTryStack.push(board);
               mTryMode = true;
               repaint();

           } else if (event->key() == Qt::Key_D && event->modifiers() == Qt::ControlModifier) {
               if (PracticeMode != true) {
                   qDebug() << "please open PracticeMode";
                   return;
               }
               //删除节点
               int margin = 30;
               int gridSize = (width() - 2 * margin) / 19;
               QPoint mousePos = this->mapFromGlobal(QCursor::pos());  // 获取鼠标在窗口中的位置
               int row = std::round((float)(mousePos.y() - margin) / (float)gridSize);
               int col = std::round((float)(mousePos.x() - margin) / (float)gridSize);
               if (!isValid(row, col)) {
                   return;
               }
               // 检查该位置是否已经有棋子
               if (!isOccupied(row, col)) {
                   qDebug() << "no piece";
                   return; // 如果该位置已被占据，则不放置棋子
               }
               qDebug() << "delPiece " << showPiece(row, col);
               delPiece(row, col);
               mTryMode = true;
               for (auto p = mTryModeSeq.begin(); p != mTryModeSeq.end(); p++) {
                   if (p->row == row && p->col == col) {
                       mTryModeSeq.erase(p);//标示删除
                       break;
                   }
               }
               repaint();
           } else if (event->key() == Qt::Key_H && event->modifiers() == Qt::ControlModifier) {
               currentPlayer = currentPlayer == Qt::black ? Qt::white : Qt::black;
               qDebug() << "currentPlayer " << currentPlayer;
               repaint();
           } else if (event->key() == Qt::Key_G && event->modifiers() == Qt::ControlModifier) {
               int margin = 30;
               int gridSize = (width() - 2 * margin) / 19;
               QPoint mousePos = this->mapFromGlobal(QCursor::pos());  // 获取鼠标在窗口中的位置
               int row = std::round((float)(mousePos.y() - margin) / (float)gridSize);
               int col = std::round((float)(mousePos.x() - margin) / (float)gridSize);
               qDebug() << showPiece(row, col);
//               std::vector<std::vector<bool>> visited(HEIGHT, std::vector<bool>(WIDTH, false));
//               floodFill(row, col, visited);
               if (hasCalc == false) {
                   calc(board, false);
                   hasCalc = true;
               }
               Filed* fd = indexMap[row][col];
               filedLiberties = fd->pieceFiled;
               if (fd) {
                   if (aliveFiled.count(fd)) {
                       qDebug() << "isAlive";
                   }
                   else {
                       qDebug() << "no Alive";
                   }
               }
               else {
                   qDebug() << "error";
               }
               repaint();
           }
        }

        void wheelEvent(QWheelEvent *event) override {
           // 获取滚轮的偏移量
           int delta = event->angleDelta().y();  // 获取滚动的距离，正值表示上滚，负值表示下滚

           if (delta > 0) {
               // 向上滚动，执行撤销操作
               undo();
           } else if (delta < 0) {
               // 向下滚动，执行重做操作
               redo();
           }
        }

        void keyPressEvent(QKeyEvent *event) override {
          this->onKeyPressEvent(event);  // 转发按键事件到棋盘
        }



public:
    //计算胜负
    // 计算并输出胜负和数目
    void calculateScore() {
        getGameResult();

        return;
        blackLiberties.clear();
        whiteLiberties.clear();
        float blackScore = 0, whiteScore = 0;
        blackScore = blackEaten;
        whiteScore = whiteEaten;
        std::cout << "Black Eaten: " << blackScore << std::endl;
        std::cout << "White Eaten: " << whiteScore << std::endl;
        // 计算地盘和提子数目
        std::vector<std::vector<bool>> visited(HEIGHT, std::vector<bool>(WIDTH, false));
        // 计算地盘
        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                if (board[i][j].color == 2 && !visited[i][j]) {
                    // 计算该空格的围地
                    int blackTerritory = 0, whiteTerritory = 0;
                    std::set<std::pair<int, int>> st;
                    if (floodFill(i, j, visited, blackTerritory, whiteTerritory, st)) {
                        if (blackTerritory > whiteTerritory) {
                            qDebug() << showPiece(i, j, 2) << " " << " blackTerritory  " << st.size();
                            blackScore += st.size();
                            //此处不包括死子，所以存在的死子算2遍
                            for (auto& p : st) {
                                blackLiberties.push_back(p);
                            }
                        } else if (blackTerritory < whiteTerritory) {
                            qDebug() << showPiece(i, j, 2) << " whiteTerritory  " << st.size();
                            whiteScore += st.size();
                            for (auto& p : st) {
                                whiteLiberties.push_back(p);
                            }
                        } else {
                            int black = 0;
                            int white = 0;
                            for (int k = 0; k < 4; k++) {
                                int rx = i + dx[k]; int ry = j + dy[k];
                                if (!isValid(rx, ry)) {
                                    continue;
                                }
                                if (board[rx][ry].color == 0) {
                                    black++;
                                }
                                if (board[rx][ry].color == 1) {
                                    white++;
                                }
                            }
                            qDebug() << "xxxxxxx " << showPiece(i, j, 2) << black << " w " << white;
                            if (white == 0 && black != 0) {
                                blackLiberties.push_back({i, j});
                                blackScore += 1;//TODO:可能不是1，而是块大小
                            }
                            else if (black == 0 && white != 0) {
                                whiteLiberties.push_back({i, j});
                                whiteScore +=1;
                            }
                        }
                    }
                }
            }
        }

        // 计算提子数
        int eatenNowBlack = countCapturedStones2(0);
        blackScore +=  eatenNowBlack;
        int eatenNowWhite = countCapturedStones2(1);
        whiteScore += eatenNowWhite;
        std::cout << "Black Eaten now: " << eatenNowBlack << std::endl;
        std::cout << "White Eaten now: " << eatenNowWhite << std::endl;
        // 输出总分
        whiteScore += 7.5;
        std::cout << "Black Score: " << blackScore << std::endl;
        std::cout << "White Score: " << whiteScore << std::endl;
        if (blackScore > whiteScore) {
            std::cout << "Black wins! " << blackScore - whiteScore << std::endl;
        } else if (whiteScore > blackScore) {
            std::cout << "White wins! " << whiteScore - blackScore << std::endl;
        } else {
            std::cout << "It's a draw!" << std::endl;
        }
        repaint();
    }


    //终局判定
    void calc(std::vector<std::vector<Piece>> & boarder, bool firstTime) {
        filedLiberties.clear();
        indexMap.clear();
        //TODO:此处有内存泄漏，应删除Filed
        indexMap.assign(HEIGHT, std::vector<Filed*>(WIDTH, nullptr));
        whiteFiled.clear();
        blackFiled.clear();
        spaceFiled.clear();
        fuzzFiled.clear();
        std::vector<std::vector<bool>> visited(HEIGHT, std::vector<bool>(WIDTH, false));

//用于形式判断？
//        visited.assign(HEIGHT, std::vector<bool>(WIDTH, false));
//        for (int i = 0; i < 19; i++) {
//            for (int j = 0; j < 19; j++) {
//                if (indexMap[i][j] != nullptr && visited[i][j] == false) {
//                    getFiledAndInner(indexMap[i][j], indexMap);
//                }
//            }
//        }

        //获取所有的块，白棋块、黑棋块、气块
        for (int i = 0; i < 19; i++) {
            for (int j = 0; j < 19; j++) {
                if (indexMap[i][j] == nullptr) {
                    Filed* fd = floodFill7(boarder, i,j);
                    if (boarder[i][j].color == 0) {
                        blackFiled.push_back(fd);
                    } else if (boarder[i][j].color == 1) {
                        whiteFiled.push_back(fd);
                    } else {
                        spaceFiled.push_back(fd);
                    }
                }
            }
        }

        //获取这些棋块之间、棋块与周围的气的关系
        for (int i = 0; i < 19; i++) {
            for (int j = 0; j < 19; j++) {
                //对某点的四周，判断是空还是同色子，还是异色子。
                for (int k = 0; k < 4; k++) {
                    int nx = i + dx[k];
                    int ny = j + dy[k];
                    if (isValid(nx,ny)) {
                        //周围的气
                        if (boarder[i][j].color == 2 && boarder[nx][ny].color != 2) {
                            if (std::find(indexMap[nx][ny]->aceFiled.begin(), indexMap[nx][ny]->aceFiled.end(), indexMap[i][j]) == indexMap[nx][ny]->aceFiled.end()) {
                                indexMap[nx][ny]->aceFiled.push_back(indexMap[i][j]);
                            }
                        }
                        //周围的区域
                        else if (boarder[i][j].color != 2 && boarder[nx][ny].color == 2) {
                            if (std::find(indexMap[nx][ny]->roundFiled.begin(), indexMap[nx][ny]->roundFiled.end(), indexMap[i][j]) == indexMap[nx][ny]->roundFiled.end()) {
                                indexMap[nx][ny]->roundFiled.push_back(indexMap[i][j]);
                            }
                        }
                        //非同色相邻
                        else if (boarder[nx][ny].color + boarder[i][j].color == 1) {
                            if (std::find(indexMap[nx][ny]->neighborFiled.begin(), indexMap[nx][ny]->neighborFiled.end(), indexMap[i][j]) == indexMap[nx][ny]->neighborFiled.end()) {
                                indexMap[nx][ny]->neighborFiled.push_back(indexMap[i][j]);
                            }
                        }
                    }
                }
            }
        }

        //现在已经获取了所有的区域
        //应该判断区域是否活棋（根据本身及其周围的气，先判断内气能否直接活，排除一些，再判断外气，是否有明显结果的对杀或者双活），再判断是否双活？
        //获取明显的活棋，其他添加到未知列表fuzz
        for (auto p : blackFiled) {
            bool ret = isAlive(boarder, p);
            if (ret) {
                p->alived = true;
                aliveFiled.insert(p);
            }
            else {
                fuzzFiled.insert(p);
            }
        }
        for (auto p : whiteFiled) {
            bool ret = isAlive(boarder, p);
            if (ret) {
                p->alived = true;
                aliveFiled.insert(p);
            }
            else {
                fuzzFiled.insert(p);
            }
        }


        //对模糊的未判活区域进行是双活还是死棋判定。  如果一方是死棋，它邻近的其他方可以作为活棋
        int lastSize = -1;
        while (fuzzFiled.size() != 0 && lastSize != (int)fuzzFiled.size()) {
            lastSize = fuzzFiled.size();
            for (auto filed = fuzzFiled.begin(); filed != fuzzFiled.end(); ) {
                //单子无双活？
                if ((*filed)->pieceFiled.size() == 1) {
                    deadFiled.insert(*filed);
                    filed = fuzzFiled.erase(filed);
                }
                else {
                    std::vector<Filed*> winResult;//对杀中胜的一方
                    std::vector<Filed*> loseResult;//对杀中输的一方
                    std::vector<Filed*> balanceResult;//双活的情况
                    isShuanghuoOrDead(*filed, winResult, loseResult, balanceResult);//知道它和它的邻居是双活还是谁吃了谁，可能有三块以上棋块一起双活？
                    //可能涉及到删除后边的filed，要操作好删除后的位置
                    if (winResult.size() != 0) {
                        for (auto t : winResult) {
                            fuzzFiled.erase(t);
                            aliveFiled.insert(t);
                        }
                    }
                    if (loseResult.size() != 0) {
                        for (auto t : loseResult) {
                            fuzzFiled.erase(t);
                            deadFiled.insert(t);
                        }
                    }
                    if (balanceResult.size() != 0) {
                        //将二者的公气，标注为平分，在计算时计算0.5个
                    }
                    if (winResult.size() != 0 || loseResult.size() != 0) {
                        break;
                    }
                    if (winResult.size() == 0 && loseResult.size() == 0 && balanceResult.size() == 0) {
                        filed++;
                    }
                }
            }
        }

        //对于活棋的周围的空格，如果这个空格是四周被这个活棋包围的，那么这个空一定属于这一方。无论这个空是不是眼
        for (auto r : aliveFiled) {
            int color = r->color;
            for (auto ace : r->aceFiled) {
                if (surround(boarder, color, ace)) {
                    ace->belong = r->color;
                }
            }
        }

        qDebug() << "Calc Over : lastSize " << lastSize;
        if (lastSize == 0) {
            return;
        }
        //这个lastSize是棋的块，这个一定是可以处理的，不可以处理的是空的块。因为可能有单官
        //筛掉死棋，把它作为空
        std::vector<std::vector<Piece>> newBoard = boarder;// x y
        for (auto r : deadFiled) {
            for (auto x : r->pieceFiled) {
                newBoard[x.first][x.second].color = 2;
            }
        }
        //对于去掉第一次筛掉的死棋的棋盘，再进行一次终局判定
        if (firstTime == false) {
            calc(newBoard, true);
        }
    }

    //这片区域如果周围都是由这块活棋包围的，
    bool surround(std::vector<std::vector<Piece>> &boarder, int color, Filed* ace) {
        for (auto p : ace->pieceFiled) {
            for (int i = 0; i < 4; i++) {
                int nx = p.first + dx[i];
                int ny = p.second + dy[i];
                if (isValid(nx, ny)) {
                    if (boarder[nx][ny].color == !color && boarder[nx][ny].color != 2) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void getGameResult() {
        calc(board, false);
        double blackPiece = 0;
        double whitePiece = 0;
        double blackSpace = 0;
        double whiteSpace = 0;
        double blackScore = 0;
        double whiteScore = 0;
        for (auto r : spaceFiled) {
            if (r->color != 2) {
                continue;
            }
            if (r->belong == 0) {
                blackSpace += r->pieceFiled.size();
            }
            else if (r->belong == 1) {
                whiteSpace += r->pieceFiled.size();
            }
            else {
                blackSpace += (double)r->pieceFiled.size() / 2.0;
                whiteSpace += (double)r->pieceFiled.size() / 2.0;
            }
        }
        for (auto r : blackFiled) {
            blackPiece += r->pieceFiled.size();
        }
        for (auto r : whiteFiled) {
            whitePiece += r->pieceFiled.size();
        }
        blackScore = blackSpace + blackPiece;
        whiteScore = whiteSpace + whitePiece;
        qDebug() << "blackSpace " << blackSpace << " blackPiece " << blackPiece << " blackScore " << blackScore << "finalScore" << blackScore - mSetting.komi / 2.0;
        qDebug() << "whiteSpace " << whiteSpace << " whitePiece " << whitePiece << " whiteScore " << whiteScore << "finalScore" << whiteScore + mSetting.komi / 2.0;
        if (std::abs((blackScore - mSetting.komi / 2.0) - (whiteScore + mSetting.komi / 2.0)) < 0.001) {
            qDebug() << "All Win! " << blackScore - mSetting.komi / 2.0;
        }
        else if (blackScore - mSetting.komi / 2.0 > whiteScore + mSetting.komi / 2.0) {
            qDebug() << "Black Win! " << (blackScore - whiteScore - mSetting.komi) / 2.0 << " zi";
        }
        else {
            qDebug() << "White Win! " << (whiteScore - blackScore + mSetting.komi) / 2.0 << " zi";
        }
        int blackx = 0;
        int whitex = 0;
        int spacex = 0;
        for (int i = 0; i < 19; i++) {
            for (int j = 0; j < 19; j++) {
                if (board[i][j].color == 0) {
                    blackx++;
                }
                else if (board[i][j].color == 1) {
                    whitex++;
                }
                else {
                    spacex++;
                }
            }
        }
        qDebug() << "[debug]rrrrrr " << blackx << " " << whitex << " " << spacex;
    }

    //result存储哪些棋块赢了，哪块棋输了
    bool isShuanghuoOrDead(Filed* filed, std::vector<Filed*>& winResult, std::vector<Filed*>& loseResult, std::vector<Filed*>& balanceResult) {
        //有眼杀瞎
        if (filed->eyeSize == 0) {
            bool flag = true;
            for (auto r : filed->neighborFiled) {
                //周围有不活且没眼的棋，说明要对杀或双活
                if (!r->alived && r->eyeSize == 0) {
                    flag = false;
                }
            }
            if (flag) {
                loseResult.push_back(filed);
                for (auto r : filed->neighborFiled) {
                    winResult.push_back(r);
                }
            }
            else {
                //TODO:判定双活或者对杀，终局基本上是双活
                //judgeShuanghuo(filed);
            }
        }
        //活棋对有眼，且有眼的一方做不出第二只眼，这里不判断是否做出来了，因为已经点终局判定了，所以当死棋处理
        //如果对方不服，可以继续对弈，作出第二只眼。
        if (filed->eyeSize == 1) {
            bool flag = true;
            for (auto r : filed->neighborFiled) {
                if (!r->alived) {
                    flag = false;
                }
            }
            if (flag) {
                loseResult.push_back(filed);
            }
        }
        return true;
    }

    //获取这块棋围起来的区域，以及它本身。
    //由于已经终局，不考虑单官，所有的空要么是双活，要么必然属于一方
    //但是死子也是一个片，死子调用这个函数会把所有的空也获取到的，这时候还是要判断是否是死子，或者就用之前的比子法。
    void getFiledAndInner(Filed *filed, std::vector<std::vector<Filed*>> &indexMap) {
        std::vector<std::vector<bool>> visited(HEIGHT, std::vector<bool>(WIDTH, false));
        int territory[3] = {0};
        auto filedLiberties = filed->pieceFiled;
        for (auto piece : filedLiberties) {
            int x = piece.first;
            int y = piece.second;
            //还应该把空周围的反颜色的子也算在里面。 当然这可能存在双活的情况。（这种情况，可以对这个子对应的区域和filedLiberties进行分析是否是双活）
            std::stack<std::pair<int, int>> stack;
            stack.push({x, y});
            int color = board[x][y].color;
            visited[x][y] = true;
            //空不应对多个区域只判断一次，因为有双活，但在一个区域时应当只判断一次
            std::vector<std::vector<bool>> otherVisited(HEIGHT, std::vector<bool>(WIDTH, false));
            //bool isBordered = true;  // 检查该区域是否被边界围住
            while (!stack.empty()) {
                std::pair<int, int> pos = stack.top();
                stack.pop();
                for (int i = 0; i < 4; i++) {
                    int newX = pos.first + dx[i], newY = pos.second + dy[i];
                    if (isValid(newX, newY)) {
                        if (visited[newX][newY] == true || otherVisited[newX][newY] == true) {
                            continue;
                        }
                        if (board[newX][newY].color == color) {
                            stack.push({newX, newY});
                            visited[newX][newY] = true;
                        } else if (board[newX][newY].color == 2) {
                            territory[2]++;
                            otherVisited[newX][newY] = true;
                            floodFill(newX, newY, visited);
                            Filed *acefiled = new Filed;
                            acefiled->pieceFiled = filedLiberties;
                            acefiled->row = newX;
                            acefiled->col = newY;
                            acefiled->color = 2;
                            filed->aceFiled.push_back(acefiled);//属于这块的气
                            acefiled->roundFiled.push_back(filed);
                            for (auto p : filedLiberties) {
                                indexMap[p.first][p.second] = acefiled;
                            }
                        }
                    }
                }
            }
        }
    }

    bool getBelongFiled(const std::set<std::pair<int, int>> &filedLiberties, std::vector<Filed> filedList, int& index) {
        //如果这些气和某些区域相邻，那么判断这个气是否某个区域的眼。
    }

    bool floodFill(int row, int col, std::vector<std::vector<bool>> &visited) {
        filedLiberties.clear();
        if (!isValid(row, col)) {
            return false;
        }
        int territory[3] = {0};
        std::set<std::pair<int, int>> liberties;
        if (board[row][col].color == 2) {
            floodFill5(row, col, visited, territory, filedLiberties);
            //调试顺便判断一下是属于哪个颜色的眼，还是不是眼
            int ret = isEyes(filedLiberties);
            if (ret == 0) {
                qDebug() << "not Eye";
            }
            else {
                qDebug() << showPiece(row, col, 2) << (ret > 0 ? " is BEye" : "is WEye");
            }
        }
        else {
            floodFill4(row, col, visited, territory, filedLiberties);
        }
        qDebug() << "blackTerritory " << territory[0] << " whiteTerritory " << territory[1] << "spaceTerritory" << territory[2];
        repaint();
    }

    //空白旁既有黑又有白不算目数，或者不能进行数子
    // Flood fill 计算区域的围棋
    bool floodFill(int x, int y, std::vector<std::vector<bool>>& visited, int& blackTerritory, int& whiteTerritory, std::set<std::pair<int, int>>& liberties) {
        std::stack<std::pair<int, int>> stack;
        stack.push({x, y});
        visited[x][y] = true;
        bool isBordered = true;  // 检查该区域是否被边界围住
        while (!stack.empty()) {
            std::pair<int, int> pos = stack.top();
            stack.pop();
            liberties.insert({pos.first, pos.second});
            for (int i = 0; i < 4; i++) {
                int newX = pos.first + dx[i], newY = pos.second + dy[i];
                if (isValid(newX, newY)) {
                    if (board[newX][newY].color == 2 && visited[newX][newY] == false) {
                        stack.push({newX, newY});
                        visited[newX][newY] = true;
                    } else if (board[newX][newY].color == 0) {
                        blackTerritory++;
                    } else if (board[newX][newY].color == 1) {
                        whiteTerritory++;
                    }
                }
            }
        }
        return isBordered;
    }


    bool ishukou(int row, int col, int color) {
        if (board[row][col].color != 2) {
            return false;
        }
        int hukou = 0;
        for (int i = 0; i < 4; i++) {
            int nx = row + dx[i];
            int ny = col + dy[i];
            if (!isValid(nx, ny)) continue;
            if (board[nx][ny].color == color) {
                hukou++;
            }
        }
        if (hukou >= 3) {
            return true;
        }
        return false;
    }
    //判断某子是否能被征吃死
    //TODO:待实现征子
    bool canbeZhengzi(int row, int col, int color) {
        std::vector<std::vector<Piece>> bod = board;
        return true;
    }

    //不考虑虎口连接，只考虑直连
    bool floodFill2(int x, int y, std::vector<std::vector<bool>>& visited, int& blackTerritory, int& whiteTerritory, int spaceTerritory, std::set<std::pair<int, int>>& liberties) {
        std::stack<std::pair<int, int>> stack;
        stack.push({x, y});
        int color = board[x][y].color;
        visited[x][y] = true;
        bool isBordered = true;  // 检查该区域是否被边界围住
        while (!stack.empty()) {
            std::pair<int, int> pos = stack.top();
            stack.pop();
            liberties.insert({pos.first, pos.second});
            for (int i = 0; i < 4; i++) {
                int newX = pos.first + dx[i], newY = pos.second + dy[i];
                if (isValid(newX, newY)) {
                    if (board[newX][newY].color == color && visited[newX][newY] == false) {
                        stack.push({newX, newY});
                        visited[newX][newY] = true;
                    } if (board[newX][newY].color == 0) {
                        blackTerritory++;
                    } else if (board[newX][newY].color == 1) {
                        whiteTerritory++;
                    } else if (board[newX][newY].color == 2) {
                        spaceTerritory++;
                    }
                }
            }
        }
        return isBordered;
    }

    //能整体连片，但是不能推理两块棋是否相连。
    bool floodFill3(int x, int y, std::vector<std::vector<bool>>& visited, int& blackTerritory, int& whiteTerritory, int spaceTerritory, std::set<std::pair<int, int>>& liberties) {
        std::stack<std::pair<int, int>> stack;
        stack.push({x, y});
        int color = board[x][y].color;
        visited[x][y] = true;
        bool isBordered = true;  // 检查该区域是否被边界围住
        std::vector<std::vector<bool>> Spacevisited(HEIGHT, std::vector<bool>(WIDTH, false));
        while (!stack.empty()) {
            std::pair<int, int> pos = stack.top();
            stack.pop();
            liberties.insert({pos.first, pos.second});
            for (int i = 0; i < 4; i++) {
                int newX = pos.first + dx[i], newY = pos.second + dy[i];
                if (isValid(newX, newY)) {
                    if (board[newX][newY].color == color && visited[newX][newY] == false) {
                        stack.push({newX, newY});
                        visited[newX][newY] = true;
                    } if (board[newX][newY].color == 0) {
                        blackTerritory++;
                    } else if (board[newX][newY].color == 1) {
                        whiteTerritory++;
                    } else if (board[newX][newY].color == 2) {
                        if (Spacevisited[newX][newY] == false) {
                            spaceTerritory++;
                            for (int i = 0; i < 4; i++) {
                               int nx = newX + dx[i];
                               int ny = newY + dy[i];
                               if (!isValid(nx, ny)) continue;
                               if (board[nx][ny].color == color && visited[nx][ny] == false) {
                                   stack.push({nx, ny});
                                   visited[nx][ny] = true;
                               }
                            }
                            Spacevisited[newX][newY] = true;
                        }
                    }
                }
            }
        }
        return isBordered;
    }

    //能整体连片，能推理两块棋是否相连。
    bool floodFill4(int x, int y, std::vector<std::vector<bool>>& visited, int territory[3], std::set<std::pair<int, int>>& liberties) {
        std::stack<std::pair<int, int>> stack;
        stack.push({x, y});
        int color = board[x][y].color;
        visited[x][y] = true;
        bool isBordered = true;  // 检查该区域是否被边界围住
        std::vector<std::vector<bool>> Spacevisited(HEIGHT, std::vector<bool>(WIDTH, false));
        std::vector<std::vector<bool>> Othervisited(HEIGHT, std::vector<bool>(WIDTH, false));
        while (!stack.empty()) {
            std::pair<int, int> pos = stack.top();
            stack.pop();
            liberties.insert({pos.first, pos.second});
            for (int i = 0; i < 4; i++) {
                int newX = pos.first + dx[i], newY = pos.second + dy[i];
                if (isValid(newX, newY)) {
                    if (board[newX][newY].color == color && visited[newX][newY] == false) {
                        stack.push({newX, newY});
                        visited[newX][newY] = true;
                        territory[color]++;
                    } else if (board[newX][newY].color == !color) {
                        if (Othervisited[newX][newY] == true) {
                            continue;
                        }
                        Othervisited[newX][newY] = true;
                        territory[!color]++;
                        int ace = getAceOfPoint(board, newX, newY, !color);
                        //绝对判定，当然可能存在倒扑
                        if (ace == 1) {
                            for (int i = 0; i < 4; i++) {
                               int nx = newX + dx[i];
                               int ny = newY + dy[i];
                               if (!isValid(nx, ny)) continue;
                               if (board[nx][ny].color == color && visited[nx][ny] == false) {
                                   stack.push({nx, ny});
                                   visited[nx][ny] = true;
                               }
                            }
                        }
                        //非绝对判定，基于当前本方下，也可能存在倒扑
                        if (ace == 2) {
                            if (canbeZhengzi(newX, newY, !color)) {
                                for (int i = 0; i < 4; i++) {
                                   int nx = newX + dx[i];
                                   int ny = newY + dy[i];
                                   if (!isValid(nx, ny)) continue;
                                   if (board[nx][ny].color == color && visited[nx][ny] == false) {
                                       stack.push({nx, ny});
                                       visited[nx][ny] = true;
                                   }
                                }
                            }
                        }
                    } else if (board[newX][newY].color == 2) {
                        if (Spacevisited[newX][newY] == true) {
                            continue;
                        }
                        Spacevisited[newX][newY] = true;
                        for (int i = 0; i < 4; i++) {
                           int nx = newX + dx[i];
                           int ny = newY + dy[i];
                           if (!isValid(nx, ny)) continue;
                           if (board[nx][ny].color == color && visited[nx][ny] == false) {
                               stack.push({nx, ny});
                               visited[nx][ny] = true;
                           }
                        }
                    }
                }
            }
        }
        return isBordered;
    }

    //对空白进行连片
    bool floodFill5(int x, int y, std::vector<std::vector<bool>>& visited, int territory[3], std::set<std::pair<int, int>>& liberties) {
        std::stack<std::pair<int, int>> stack;
        stack.push({x, y});
        int color = board[x][y].color;
        if (color != 2) {
            return false;
        }
        visited[x][y] = true;
        bool isBordered = true;  // 检查该区域是否被边界围住
        std::vector<std::vector<bool>> Othervisited(HEIGHT, std::vector<bool>(WIDTH, false));
        while (!stack.empty()) {
            std::pair<int, int> pos = stack.top();
            stack.pop();
            liberties.insert({pos.first, pos.second});
            for (int i = 0; i < 4; i++) {
                int newX = pos.first + dx[i], newY = pos.second + dy[i];
                if (isValid(newX, newY)) {
                    if (Othervisited[newX][newY] == true) {
                        continue;
                    }
                    Othervisited[newX][newY] = true;
                    if (board[newX][newY].color == color && visited[newX][newY] == false) {
                        stack.push({newX, newY});
                        visited[newX][newY] = true;
                    }
                    if (board[newX][newY].color == 0) {
                        territory[0]++;
                    } else if (board[newX][newY].color == 1) {
                        territory[1]++;
                    } else if (board[newX][newY].color == 2) {
                        territory[2]++;
                    }
                }
            }
        }
        return isBordered;
    }


    //能整体连片，能推理两块棋是否相连。
    bool floodFill6(int x, int y, std::vector<std::vector<bool>>& visited, int territory[3], std::set<std::pair<int, int>>& liberties) {
        std::stack<std::pair<int, int>> stack;
        stack.push({x, y});
        int color = board[x][y].color;
        visited[x][y] = true;
        bool isBordered = true;  // 检查该区域是否被边界围住
        std::vector<std::vector<bool>> Spacevisited(HEIGHT, std::vector<bool>(WIDTH, false));
        std::vector<std::vector<bool>> Othervisited(HEIGHT, std::vector<bool>(WIDTH, false));
        while (!stack.empty()) {
            std::pair<int, int> pos = stack.top();
            stack.pop();
            liberties.insert({pos.first, pos.second});
            for (int i = 0; i < 4; i++) {
                int newX = pos.first + dx[i], newY = pos.second + dy[i];
                if (isValid(newX, newY)) {
                    if (board[newX][newY].color == color && visited[newX][newY] == false) {
                        stack.push({newX, newY});
                        visited[newX][newY] = true;
                        territory[color]++;
                    } else if (board[newX][newY].color == !color) {
                        if (Othervisited[newX][newY] == true) {
                            continue;
                        }
                        Othervisited[newX][newY] = true;
                        territory[!color]++;
                        int ace = getAceOfPoint(board, newX, newY, !color);
                        //绝对判定，当然可能存在倒扑
                        if (ace == 1) {
                            for (int i = 0; i < 4; i++) {
                               int nx = newX + dx[i];
                               int ny = newY + dy[i];
                               if (!isValid(nx, ny)) continue;
                               if (board[nx][ny].color == color && visited[nx][ny] == false) {
                                   stack.push({nx, ny});
                                   visited[nx][ny] = true;
                               }
                            }
                        }
                        //非绝对判定，基于当前本方下，也可能存在倒扑
                        if (ace == 2) {
                            if (canbeZhengzi(newX, newY, !color)) {
                                for (int i = 0; i < 4; i++) {
                                   int nx = newX + dx[i];
                                   int ny = newY + dy[i];
                                   if (!isValid(nx, ny)) continue;
                                   if (board[nx][ny].color == color && visited[nx][ny] == false) {
                                       stack.push({nx, ny});
                                       visited[nx][ny] = true;
                                   }
                                }
                            }
                        }
                    } else if (board[newX][newY].color == 2) {
                        if (Spacevisited[newX][newY] == true) {
                            continue;
                        }
                        Spacevisited[newX][newY] = true;
                        for (int i = 0; i < 4; i++) {
                           int nx = newX + dx[i];
                           int ny = newY + dy[i];
                           if (!isValid(nx, ny)) continue;
                           if (board[nx][ny].color == color && visited[nx][ny] == false) {
                               stack.push({nx, ny});
                               visited[nx][ny] = true;
                           }
                           Filed* filed = floodFill7(board, newX, newY);
                        }
                    }
                }
            }
        }
        return isBordered;
    }


    //对这一点进行连片
    Filed* floodFill7(std::vector<std::vector<Piece>> & boarder, int x, int y) {
        std::stack<std::pair<int, int>> stack;
        if (indexMap[x][y] != nullptr) {
            return indexMap[x][y];
        }
        Filed* filed = new Filed;
        stack.push({x, y});
        int color = boarder[x][y].color;
        filed->row = x; filed->col = y; filed->color = color;
        std::set<std::pair<int, int>> liberties;
        std::vector<std::vector<bool>> visited(HEIGHT, std::vector<bool>(WIDTH, false));
        while (!stack.empty()) {
            std::pair<int, int> pos = stack.top();
            stack.pop();
            liberties.insert({pos.first, pos.second});
            for (int i = 0; i < 4; i++) {
                int newX = pos.first + dx[i], newY = pos.second + dy[i];
                if (isValid(newX, newY)) {
                    if (visited[newX][newY] == true) {
                        continue;
                    }
                    visited[newX][newY] = true;
                    if (boarder[newX][newY].color == color) {
                        stack.push({newX, newY});
                    }
                    //非空格点 以空格斜对角相连
                    if (color != 2 && boarder[newX][newY].color == 2) {
                        for (int i = 0; i < 4; i++) {
                           int nx = newX + dx[i];
                           int ny = newY + dy[i];
                           if (!isValid(nx, ny)) continue;
                           if (boarder[nx][ny].color == color && visited[nx][ny] == false) {
                               stack.push({nx, ny});
                               visited[nx][ny] = true;
                           }
                        }
                    }
                    //非空格点，被其他颜色的卡住，但是其他颜色的点只有1气，或者2气但是能征死，基于当前颜色先手判断
                    else if (color != 2 && boarder[newX][newY].color == !color) {
                        int ace = getAceOfPoint(boarder, newX, newY, !color);
                        //绝对判定，当然可能存在倒扑
                        if (ace == 1) {
                            for (int i = 0; i < 4; i++) {
                               int nx = newX + dx[i];
                               int ny = newY + dy[i];
                               if (!isValid(nx, ny)) continue;
                               if (boarder[nx][ny].color == color && visited[nx][ny] == false) {
                                   stack.push({nx, ny});
                                   visited[nx][ny] = true;
                               }
                            }
                        }
                        //非绝对判定，基于当前本方下，也可能存在倒扑
                        if (ace == 2) {
                            if (canbeZhengzi(newX, newY, !color)) {
                                for (int i = 0; i < 4; i++) {
                                   int nx = newX + dx[i];
                                   int ny = newY + dy[i];
                                   if (!isValid(nx, ny)) continue;
                                   if (boarder[nx][ny].color == color && visited[nx][ny] == false) {
                                       stack.push({nx, ny});
                                       visited[nx][ny] = true;
                                   }
                                }
                            }
                        }
                    }
                }
            }
        }
        filed->pieceFiled = liberties;
        for (auto p : liberties) {
            indexMap[p.first][p.second] = filed;
        }
        return filed;
    }

    // 统计已提子数目
    int countCapturedStones(int color) {
        int capturedStones = 0;
        std::vector<std::vector<bool>> visited(HEIGHT, std::vector<bool>(WIDTH, false));
        // 对棋盘上的每个位置进行遍历
        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                // 如果棋子不是0且未访问过，且它是敌方的棋子
                if (board[i][j].color != 2 && board[i][j].color != color && !visited[i][j]) {
                    int blackTerritory = 0, whiteTerritory = 0;
                    // 检查该棋块是否被吃掉
                    std::set<std::pair<int, int>> st;
                    if (floodFill(i, j, visited, blackTerritory, whiteTerritory, st)) {
                        // 如果敌方区域被完全围住且为空白地带，那么该区域就是死棋
                        if (color == 1) { // 如果当前是黑棋
                            capturedStones += whiteTerritory;
                        } else { // 如果当前是白棋
                            capturedStones += blackTerritory;
                        }
                    }
                }
            }
        }
        return capturedStones;
    }

    // 计算被提取的棋子数量
    int countCapturedStones2(int color) {
        int captured = 0;
        // 用于记录已经遍历过的棋子
        std::set<std::pair<int, int>> visited;

        // 检查棋盘上的每一个点
        for (int i = 0; i < BOARDWIDTH; i++) {
            for (int j = 0; j < BOARDWIDTH; j++) {
                if (board[i][j].color != 2 && board[i][j].color != color && visited.find({i, j}) == visited.end()) {
                    if (i == 5 && j == 10) {
                        qDebug() << "point";
                    }
                    // 如果是对方的棋子并且未被访问过
                    int opponentColor = (color == 1) ? 0 : 1; // 对方棋子
                    std::set<std::pair<int, int>> group;
                    std::set<std::pair<int, int>> liberties;
                    std::set<std::pair<int, int>> eyes;

                    bool isAlive = bfs(i, j, opponentColor, group, liberties, eyes); // 使用BFS或DFS遍历对方的棋块

                    // 标记这些棋子已经被遍历
                    for (const auto& p : group) {
                        visited.insert(p);
                    }

                    // 如果该棋块没有气，说明它被提取
                    if (!isAlive) {
                        for (auto r : group) {
                            eatenNowList.push_back(r);
                        }
                        captured += group.size(); // 这些棋子都被提取
                    }
                }
            }
        }
        return captured;
    }

public:
    //形式判断
    // 广度优先搜索（BFS）来检查一个棋块
    //传入的是一个有颜色的棋子
    //group : 返回棋块总体
    //liberties 返回棋块的外气和内气
    bool bfs(int x, int y, int color, std::set<std::pair<int, int>>& group, std::set<std::pair<int, int>>& liberties, std::set<std::pair<int, int>>& eyes) {
        std::queue<std::pair<int, int>> q;
        q.push({x, y});
        group.insert({x, y});

        while (!q.empty()) {
            std::pair<int, int> p = q.front();
            q.pop();
            bool isSpace = board[p.first][p.second].color == 2 ? true : false;
            // 遍历上下左右
            if (!isSpace) {
                for (int i = 0; i < 4; i++) {
                    int nx = p.first + dx[i];
                    int ny = p.second + dy[i];

                    if (!isValid(nx, ny)) continue;

                    if (board[nx][ny].color == color && group.find({nx, ny}) == group.end()) {
                        // 如果是同色棋子，加入组
                        group.insert({nx, ny});
                        q.push({nx, ny});
                    } else if (board[nx][ny].color == 2 && liberties.find({nx, ny}) == liberties.end()) {
                        // 如果是空位，加入气
                        liberties.insert({nx, ny});
                        q.push({nx, ny});
                    } else if (board[nx][ny].color != color) {
                        // 如果是对方棋子，什么都不做
                        continue;
                    }
                }
            }
            else {
                //是空格 不仅考虑直接连接 也 考虑虎口连接但实际不连接 的棋也是这块棋的一部分
//                for (int i = 0; i < 4; i++) {
//                    int nx = p.first + dx[i];
//                    int ny = p.second + dy[i];

//                    if (!isValid(nx, ny)) continue;

//                    if (board[nx][ny].color == color && group.find({nx, ny}) == group.end()) {
//                        // 如果是同色棋子，加入组
//                        group.insert({nx, ny});
//                        q.push({nx, ny});
//                    } else if (board[nx][ny].color == 2 && liberties.find({nx, ny}) == liberties.end()) {
//                        // 如果是空位，加入气
//                        liberties.insert({nx, ny});
//                        q.push({nx, ny});
//                    } else if (board[nx][ny].color != color) {
//                        // 如果是对方棋子，什么都不做
//                        continue;
//                    }
//                }










                int hukou = 0;
                for (int i = 0; i < 4; i++) {
                    int nx = p.first + dx[i];
                    int ny = p.second + dy[i];

                    if (!isValid(nx, ny)) continue;
                    if (board[nx][ny].color == color) {
                        hukou++;
                    }
                }
                if (hukou >= 3) {
                    for (int i = 0; i < 4; i++) {
                        int nx = p.first + dx[i];
                        int ny = p.second + dy[i];
                        if (!isValid(nx, ny))
                            continue;
                        if (board[nx][ny].color == color && group.find({nx, ny}) == group.end()) {
                            //以虎口连接的棋，算作连通，继续遍历
                            q.push({nx, ny});
                            group.insert({nx, ny});
                        }
                    }
                }
            }
        }

        // 遍历所有的气（liberties），判断是否有眼
        std::vector<std::vector<int>> book(19, std::vector<int>(19, 0));
        int maxEyeSize = 0;
        for (auto& liberty : liberties) {
            int ex = liberty.first;
            int ey = liberty.second;
            if (book[ex][ey] == 1) {
                continue;
            }
            std::queue<std::pair<int, int>> que;
            int eyeSize = 0;
            book[ex][ey] = 1;
            que.push({ex,ey});
            bool isEyes = false;
            while (!que.empty()) {
                auto p = que.front();
                que.pop();
                int tx = p.first;
                int ty = p.second;
                for (int i = 0; i < 4; i++) {
                    int rx = tx + dx[i];
                    int ry = ty + dy[i];
                    if (isValid(rx, ry) && liberties.find({rx, ry}) != liberties.end() && book[rx][ry] == 0) {
                        book[rx][ry] = 1;
                        que.push({rx, ry});
                    }
                }
                if (isEye(tx, ty, color)) {
                    isEyes = true;
                    eyeSize++;
                    ex = tx;
                    ey = ty;
                }
            }
            if (isEyes)
                eyes.insert({ex, ey});
            maxEyeSize = std::max(maxEyeSize, eyeSize);
        }
        for (auto r : eyes) {
            qDebug() << "eye " << showPiece(r.first, r.second, 2);
        }
        qDebug() << "eysNum " << eyes.size() << " maxEyeSize = " << maxEyeSize;
        if (eyes.size() >= 2 || maxEyeSize >= 5) {
            return true;
        }
        else {
            return false;
        }
    }

    // 计算并输出棋局的目数
    //形式判断
    std::pair<int, int> calculateScore2(int index) {
        if (index == 0) {
            whiteLiberties.clear();
            blackLiberties.clear();
            repaint();
            return {0, 0};
        }
        int blackScore = 0, whiteScore = 0;

        // 用于记录已经遍历过的棋子
        std::set<std::pair<int, int>> visited;
        blackLiberties.clear();
        whiteLiberties.clear();
        // 检查棋盘上的每一个点
        for (int i = 0; i < BOARDWIDTH; i++) {
            for (int j = 0; j < BOARDWIDTH; j++) {
                if (board[i][j].color != 2 && visited.find({i, j}) == visited.end()) {
                    int color = board[i][j].color;
                    std::set<std::pair<int, int>> group;
                    std::set<std::pair<int, int>> liberties;
                    std::set<std::pair<int, int>> eyes;

                    bfs(i, j, color, group, liberties, eyes);

                    // 标记这些棋子已经被遍历
                    for (const auto& p : group) {
                        visited.insert(p);
                    }

                    // 判断是否有眼，来判断是活棋还是死棋
                    if (eyes.size() >= 2) {
                        // 有两个眼，算作活棋
                        if (color == 1) {
                            blackScore += liberties.size();  // 黑棋占据的气
                            //TODO: 形式判断时，需要判断是内气还是外气，外气不能算目数
                        } else {
                            whiteScore += liberties.size();  // 白棋占据的气
                        }
                    } else {
                        // 没有眼，算作死棋，直接把这些棋子加到对方的分数
                        if (color == 1) {
                            whiteScore += group.size();  // 黑棋吃掉的白棋
                        } else {
                            blackScore += group.size();  // 白棋吃掉的黑棋
                        }
                    }

                    //TODO:把眼和气都划分颜色，显示在界面上。
                    for (auto &liber : liberties) {
                        if (color == 0) {
                            blackLiberties.push_back(liber);
                        }
                        else {
                            whiteLiberties.push_back(liber);
                        }
                    }
                }

            }
        }

        repaint();
        // 返回结果
        return {blackScore, whiteScore};
    }


public:
    //读取棋谱

    // 将坐标从 'a' 到 's' 转换为棋盘索引
    int charToIndex(char c) {
        return c - 'a';  // 'a' 转为 0, 'b' 转为 1, ..., 's' 转为 18
    }
    // 将坐标从 0 到 18 转换为 'a' 到 's'
    char indexToChar(int index) {
        return 'a' + index;  // 0 -> 'a', 1 -> 'b', ..., 18 -> 's'
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
    //顶层
    bool showSGF(std::shared_ptr<SGFTreeNode> node, QTreeWidgetItem* parent, int compress, bool isBranch) {
        if (node == root && node != nullptr) {
            bool flag = false;
            for (auto p : root->branches) {
                auto oldBorder = board;
                auto oldHistoryNode = historyNode;
                if (flag == false) {
                    if (root->branches.size() <= 1) {
                        showSGF(p, nullptr, 0, 0);
                    }
                    else {
                        showSGF(p, nullptr, 1, 0);
                    }
                    flag = true;
                }
                else {
                    showSGF(p, nullptr, 1, 1);
                }
                board = oldBorder;
                historyNode = oldHistoryNode;
            }
            return true;
        }
        QTreeWidgetItem* item = nullptr;

        if (compress == 1) {
            Piece& piece = node->move;
            putPiece(node, isBranch);
            item = new QTreeWidgetItem;

            QString str = colToChar(piece.col) + QString::number(19 - piece.row) + " " + (piece.color == 0 ? "B" : "W");
            QString str2 = QString::number(node->moveNum) + "  ";
            item->setText(0, str);
            item->setText(1, str2);
            treeItemMap[node] = item;
            TreeData data;
            data.node = node;
            data.index = node->moveNum;
            QVariant variant = QVariant::fromValue(data);
            item->setData(0, 1, variant);
            if (parent == nullptr) {
                pieceTree->addTopLevelItem(item);
            }
            else {
                parent->addChild(item);
            }
            if (node->branches.size() == 0) {
                return true;
            }
            else if (node->branches.size() == 1) {
                showSGF(node->branches[0], item, 0, 0);
            }
            else {
                for (int i = 0; i < (int)node->branches.size(); i++) {
                    auto oldBorder = board;
                    auto oldHistoryNode = historyNode;
                    if (i == 0)
                        showSGF(node->branches[i], item, 1, 0);
                    else
                        showSGF(node->branches[i], item, 1, 1);
                    board = oldBorder;
                    historyNode = oldHistoryNode;
                }
            }
        }
        else {
            while (1) {
                Piece& piece = node->move;
                putPiece(node, isBranch);
                item = new QTreeWidgetItem;
                QString str = colToChar(piece.col) + QString::number(19 - piece.row) + " " + (piece.color == 0 ? "B" : "W");
                QString str2 = QString::number(node->moveNum) + "  ";
                item->setText(0, str);
                item->setText(1, str2);
                treeItemMap[node] = item;
                TreeData data;
                data.node = node;
                data.index = node->moveNum;
                QVariant variant = QVariant::fromValue(data);
                item->setData(0, 1, variant);
                if (parent == nullptr)
                    pieceTree->addTopLevelItem(item);
                else
                    parent->addChild(item);
                if (node->branches.size() == 0) {
                    break;
                }
                else if (node->branches.size() == 1) {
                    node = node->branches[0];
                    continue;
                }
                else {
                    for (int i = 1; i < (int)node->branches.size(); i++) {
                        auto oldBorder = board;
                        auto oldHistoryNode = historyNode;
                        showSGF(node->branches[i], item, 1, 1);
                        board = oldBorder;
                        historyNode = oldHistoryNode;
                    }
                    showSGF(node->branches[0], parent, 0, 0);
                    break;
                }
            }
        }
        return true;
    }


    void clearRoot() {
        historyNode = nullptr;
        treeItemMap.clear();
        board = zeroBoard;
        clearBranch(root);
        root = nullptr;
        root = std::make_shared<SGFTreeNode>();
        root->boardHistory = zeroBoard;
        root->parent.reset();
    }

    void clearBranch(std::shared_ptr<SGFTreeNode>& node) {
        for (auto p : node->branches) {
            clearBranch(p);
        }
        node->parent.reset();
        node->branches.clear();
    }
    // 读取 .sgf 文件并解析棋谱
    bool readSGF(const std::string &filename) {
        if (root != nullptr) {
            //清除原棋盘和SFG
            clear();
        }
        root = sgfParser.parse(filename, setupInfo);
        showSGF(root, nullptr, 0, 0);
        repaint();
        parsesetupInfo(setupInfo, mSetting);
        return true;
    }

    void parsesetupInfo(std::map<std::string, std::string> &setupInfo, GameSettings& mSetting) {
        if (setupInfo.count("Komi")) {
            double komi = std::stof(setupInfo["Komi"]);
            if (komi >= 0 && komi <= 100) {
                mSetting.komi = komi;
            }
            qDebug() << "Read KM " << mSetting.komi;
        }
    }

    bool saveSGF(const std::string &filename) {
        sgfParser.saveSGF(filename, root, setupInfo);
        return true;
    }

    bool deleteSGFNode(std::shared_ptr<SGFTreeNode> node) {
        auto parent = node->parent.lock();
        historyNode = parent;
        for (auto r =  parent->branches.begin(); r != parent->branches.end(); r++ ) {
            if (*r == node) {
                parent->branches.erase(r);
                break;
            }
        }
        node->parent.reset();
        node->branches.clear();//digui?
        return true;
    }

public:
    //slot deleteItem
    bool deleteSGFTreeItem(QTreeWidgetItem* item) {
        if (item == nullptr) {
            return false;
        }
        auto p = item->parent();
        TreeData data = item->data(0, 1).value<TreeData>();
        auto node = data.node.lock();
        if (p == nullptr) {
            int index = pieceTree->indexOfTopLevelItem(item);
            pieceTree->takeTopLevelItem(index);
            treeItemMap.erase(node);
            deleteSGFNode(node);
            return true;
        }
        else {
            p->removeChild(item);
            treeItemMap.erase(node);
            deleteSGFNode(node);
            return true;
        }
    }

    // 打印棋盘 test BW
    void printBoard2(std::vector<std::vector<Piece>> & boarder) {
        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                if (boarder[i][j].color == 0) {
                    std::cout << "B ";
                } else if (boarder[i][j].color == 1) {
                    std::cout << "W ";
                } else {
                    std::cout << ". ";  // 空格
                }
            }
            std::cout << std::endl;
        }
    }

public:
    void clear() {
        board = zeroBoard;
        //pieceSeq.clear();
//        while (!redoStack.empty()) {
//            redoStack.pop();
//        }
        moveNumber = 0;
        allNumber = 0;
        blackEaten = 0;
        whiteEaten = 0;
        currentPlayer = Qt::black;
        repaint();
        clearJudge();
        clearRoot();
        treeItemMap.clear();
        pieceTree->clear();
    }
    void clearJudge() {
        blackLiberties.clear();
        whiteLiberties.clear();
        eatenNowList.clear();
        repaint();
    }

    void setUITree(QTreeWidget* widget) {
        pieceTree = widget;
    }


public:
    bool loadDingShiBook(const std::string &filename) {
        mDingShiBookPath = filename;
        DingShiBook = sgfParser.parse(filename, DingShiSetupInfo);
        return true;
    }

    bool storeDingShiBook(std::string &filename) {
        if (filename == "") {
            filename = mDingShiBookPath;
        }
        return sgfParser.saveSGF(filename, DingShiBook, DingShiSetupInfo);
    }
    //A B C
    //A C B
    //B A C
    //B C A
    //C A B
    //C B A
    //n!
    //row col color 下一招准备下的位置
    //stepN 准备获取后续stepN招
    //定时不要超过25步，否则复杂度极大
    //获取当前棋盘已放置棋子的所有顺序pieceSeqList
    //color当前谁走
    void getEverySeq(std::vector<std::vector<Piece>> &boarder, std::vector<std::vector<Piece>>& pieceSeqList, int color) {
        std::vector<Piece> pieceSeq;
        for (int i = 0; i < BOARDWIDTH; i++) {
            for (int j = 0; j < BOARDWIDTH; j++) {
                if (boarder[i][j].color != 2) {
                    pieceSeq.push_back(boarder[i][j]);
                }
            }
        }
        printBoard2(boarder);
        qDebug() << pieceSeq[0].row << " " << pieceSeq[0].col;
        qDebug() << showPiece(pieceSeq[0]);
        //推断当前颜色 所有子回退后，定式的第一子是黑还是白
        color = pieceSeq.size() % 2 == 0? color : !color;
        int n = 0;
        std::set<int> st;
        std::vector<Piece> seq;
        getSeq(pieceSeq, n, pieceSeqList, seq, color, st);
        for (auto r : pieceSeqList) {
            std::cout << "seq: ";
            for (auto x : r) {
                std::cout << showPiece(x).toStdString() + " ";
            }
            std::cout << std::endl;
        }
    }

    void getSeq(std::vector<Piece> pieceSeq, int index, std::vector<std::vector<Piece>>& res, std::vector<Piece> cur, int curColor, std::set<int> st) {
        if (index == (int)pieceSeq.size() && cur.size() == pieceSeq.size()) {
            res.push_back(cur);
            return;
        }
        for (size_t i = 0; i < pieceSeq.size(); i++) {
            if (pieceSeq[i].color == curColor && !st.count(i)) {
                st.insert(i);
                cur.push_back(pieceSeq[i]);
                getSeq(pieceSeq, index + 1, res, cur, (int)(!curColor), st);
                cur.pop_back();
                st.erase(i);
            }
        }
    }


    //无法处理打劫问题，只能根据当前盘面与当前落子点和颜色推断如何下（依据是定式库）。
    //目前没有显示，只是打印分支，最好做多个小图显示，或者将第一手以虚子显示。然后逐渐补齐。
    void remember(std::vector<std::vector<Piece>> &boarder, int row, int col, int color, int stepN, std::vector<std::vector<Piece>>& res) {
        if (DingShiBook == nullptr) {
            qDebug() << "no DingShiBook";
            return;
        }
        std::vector<std::vector<Piece>> seqList;
        getEverySeq(boarder, seqList, color);
        int rotate = 0;
        if (seqList.size() == 0) {
            return;
        }
        {
            //调整row col
            auto pieceSeq = seqList[0];
            AdjustPosToLeftDown(pieceSeq, rotate);//for中的每次rotate一定相同
            std::cout << std::endl;
            if (rotate == BOTTOMRIGHT) {
                col = 18 - col;
            }
            else if (rotate == TOPLEFT) {
                row = 18 - row;
            }
            else if (rotate == TOPRIGHT) {
                row = 18 - row;
                col = 18 - col;
            }
        }
        for (size_t i = 0; i < seqList.size(); i++) {
            auto pieceSeq = seqList[i];
            AdjustPosToLeftDown(pieceSeq, rotate);//for中的每次rotate一定相同
            //这种方式还有利于将错误棋局导向正确棋局
            getNextStep(pieceSeq, DingShiBook, row, col, color, stepN, res);
        }
        {
            //冗余代码，可以重构
            //反转颜色再搜一遍
            adjustColor(seqList);
            //row col已经调整过了
            std::vector<std::vector<Piece>> colorRes;
            for (size_t i = 0; i < seqList.size(); i++) {
                auto pieceSeq = seqList[i];
                AdjustPosToLeftDown(pieceSeq, rotate);//for中的每次rotate一定相同
                //这种方式还有利于将错误棋局导向正确棋局
                getNextStep(pieceSeq, DingShiBook, row, col, !color, stepN, colorRes);
            }
            adjustColor(colorRes);
            for (auto x : colorRes) {
                res.push_back(x);
            }
        }
        adjustResultOrigin(res, rotate);//逆操作将结果调回原位
        showNextNStep2(res);
    }

    //已知一种确定的顺序pieceSeq
    //已知下一步要下在哪
    //获取stepN步分支，存入res
    //res  num个stepN步分支
    //另外考虑，不同方向，不同角，对称位置，其实是同一种
    //也就是每个Node对应一个piece，和N个branch,其实像前缀树
    //row col color 当前准备下的位置
    //匹配规则完善逻辑 旋转 对称 黑白 4 * 2 * 2 = 16，得到结果后再翻转回来,还要筛出相同项（或者在入库时就统一在左下放置并筛出相同，然后记录变换） (定位) ->废弃
    //TODO: 存的时候统一旋转位置放在左下，然后对称放两种。搜索的时候转化到左下就行了，结果再转化过去就行了
    //如何判断需要旋转，如果60%的棋子在左上右上右下，那么需要转换到左下，存的时候先正常存，再col row存一次
    //需要判断当前局面的位置，然后记录转化步骤，顺时针转90 180 270，然后得到结果后再将结果逆时针转90 180 270，然后显示。习题也可以这样借鉴。
    void getNextStep(std::vector<Piece> & pieceSeq, std::shared_ptr<SGFTreeNode>& book, int row, int col, int color, int stepN, std::vector<std::vector<Piece>>& res) {
        //先对前边的几手棋找到起始搜索节点cur
        size_t i = 0;
        std::shared_ptr<SGFTreeNode> cur = book;
        size_t cnt = 0;
        while (i < pieceSeq.size()) {
            cnt = 0;
            if (cur->branches.size() == 0) {
                return;
            }
            for (auto branch : cur->branches) {
                if (branch->move.row == pieceSeq[i].row
                        && branch->move.col == pieceSeq[i].col
                        && branch->move.color == pieceSeq[i].color) {
                    break;
                }
                cnt++;
            }
            if (cnt != cur->branches.size()) {
                //有
                cur = cur->branches[cnt];
                i++;
            }
            else {
                break;
            }
        }
        if (i != pieceSeq.size()) {
            return;
        }
        cnt = 0;
        for (auto branch : cur->branches) {
            if (branch->move.row == row
                    && branch->move.col == col
                    && branch->move.color == color) {
                break;
            }
            cnt++;
        }
        if (cnt == cur->branches.size()) {
            //选点无后续
            return;
        }
        cur = cur->branches[cnt];
        //算cur节点
        std::vector<Piece> vec;
        dfs(cur, stepN, res, vec);
        qDebug() << "stepN = " << stepN << " dfs result: " << res.size();
    }

    void dfs(std::shared_ptr<SGFTreeNode> node, int stepN, std::vector<std::vector<Piece>> &res, std::vector<Piece> vec) {
        vec.push_back(node->move);
        // || stepN == 0
        if (node->branches.size() == 0 || stepN <= 0) {
            res.push_back(vec);
            return;
        }
        for (auto r : node->branches) {
            dfs(r, stepN - 1, res, vec);
        }
    }

    //最多显示20种，所以应当先将stepN调小，越往后越大，前边变化多，后边变化少
    void showNextNStep(std::vector<std::vector<Piece>> &res) {
        //将分支以多个方框并列显示在界面上侧
        //按照胜率或者按照常用程度排列
        if (res.size() == 0) {
            std::cout << "no match" << std::endl;
            return;
        }
        for (size_t i = 0; i < res.size(); i++) {
            for (auto r : res[i]) {
                std::cout << showPiece(r.row, r.col, r.color).toStdString() << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }


    void showNextNStep2(std::vector<std::vector<Piece>> &res) {
        //将分支以多个方框并列显示在界面上侧
        //按照胜率或者按照常用程度排列
        if (res.size() == 0) {
            std::cout << "no match" << std::endl;
            return;
        }
        else {
            std::cout << "has " << res.size() << " type DS " << std::endl;
        }
        for (size_t i = 0; i < res.size(); i++) {
            for (auto r : res[i]) {
                std::cout << showPiece(r.row, r.col, r.color).toStdString() << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        DingShiShowWidget* dsList = new DingShiShowWidget;//成员
        for (size_t i = 0; i < res.size(); i++) {
            DingShiShow* ds = new DingShiShow(board, res[i]);
            ds->showDS(i);
            dsList->addItem(ds);
        }
        dsList->showDS();
    }


private:



    void adjustColor(std::vector<std::vector<Piece>>& seqList) {
        for (int i = 0; i < (int)seqList.size(); i++) {
            for (int j = 0; j < (int)seqList[i].size(); j++) {
                seqList[i][j].color = !seqList[i][j].color;
            }
        }
    }

    //rotate 4 无旋转 5 TOPRIGHT 6 BOTTOMLEFT 7 BOTTOMRIGHT。不是真的旋转，只是记录一下是哪一种逆操作
    void AdjustPosToLeftDown(std::vector<Piece>& seq, int& rotate) {
        Direction direction = BOTTOMLEFT;//
        int dirce[8] = {0};
        for (int i = 0; i < (int)seq.size(); i++) {
            if (seq[i].row <= 9 && seq[i].col <= 9) {
                dirce[TOPLEFT]++;
            }
            if (seq[i].row <= 9 && seq[i].col >= 9) {
                dirce[TOPRIGHT]++;
            }
            if (seq[i].row >= 9 && seq[i].col <= 9) {
                dirce[BOTTOMLEFT]++;
            }
            if (seq[i].row >= 9 && seq[i].col >= 9) {
                dirce[BOTTOMRIGHT]++;
            }
        }
        int maxFreq = 0;
        for (int i = 0; i < 8; i++) {
            if (dirce[i] > maxFreq) {
                direction = Direction(i);
                rotate = Direction(i);
                maxFreq = dirce[i];
            }
        }
        if (direction == BOTTOMLEFT) {
            return;
        }
        //怎么旋转， 左上，row直接19 - 。  右上 row col都减 右下 col直接减
        for (int i = 0; i < (int)seq.size(); i++) {
            if (direction == BOTTOMRIGHT) {
                seq[i].col = 18 - seq[i].col;
            }
            else if (direction == TOPLEFT) {
                seq[i].row = 18 - seq[i].row;
            }
            else if (direction == TOPRIGHT) {
                seq[i].row = 18 - seq[i].row;
                seq[i].col = 18 - seq[i].col;
            }
        }
    }

    //按左下对角线对称
    void symmetrization(std::vector<Piece>& seq) {
        for (int i = 0; i < (int)seq.size(); i++) {
            int tmp = seq[i].col;
            seq[i].col = 18 - seq[i].row;
            seq[i].row = 18 - tmp;
        }
    }


    //逆操作将结果调回原位
    void adjustResultOrigin(std::vector<std::vector<Piece>>& res, int rotate) {
        for (int i = 0; i < (int)res.size(); i++) {
            for (int j = 0; j < (int)res[i].size(); j++) {
                if (rotate == BOTTOMRIGHT) {
                    res[i][j].col = 18 - res[i][j].col;
                }
                else if (rotate == TOPLEFT) {
                    res[i][j].row = 18 - res[i][j].row;
                }
                else if (rotate == TOPRIGHT) {
                    res[i][j].row = 18 - res[i][j].row;
                    res[i][j].col = 18 - res[i][j].col;
                }
            }
        }
    }

    bool addnewBranchDS(std::shared_ptr<SGFTreeNode> node, std::vector<Piece> &seq, int index) {
        if (node == nullptr) {
            return false;
        }
        while (index < (int)seq.size()) {
            auto newNode = std::make_shared<SGFTreeNode>();
            newNode->move = seq[index];
            newNode->parent = node;
            if (node->branches.size() == 0) {
                newNode->moveNum = node->moveNum + 1;
            }
            else {
                newNode->moveNum = 1;
            }
            node->branches.push_back(newNode);
            node = newNode;
            index++;
        }
        return true;
    }

    bool addBranchDS(std::shared_ptr<SGFTreeNode> node, std::vector<Piece>& seq) {
        int i = 0;
        while (i < (int)seq.size()) {
            bool has = false;
            for (int j = 0; j < (int)node->branches.size(); j++) {
                if (seq[i] == node->branches[j]->move) {
                    has = true;
                    node = node->branches[j];
                    i++;
                    break;
                }
            }
            if (!has) {
                //开始添加
                //把seq[i] 添加到node下。
                return addnewBranchDS(node, seq, i);
            }
        }
        if (i == (int)seq.size()) {
            //已完整匹配，已存在
            qDebug() << "current DS has exists";
            return false;
        }
        return true;
    }

public:
    //TODO: 存的时候统一旋转位置放在左下，然后对称放两种。搜索的时候转化到左下就行了，结果再转化过去就行了
    //如何判断需要旋转，如果60%的棋子在左上右上右下，那么需要转换到左下，存的时候先正常存，再对称存一次
    bool addDSintoBook() {
        if (DingShiBook == nullptr) {
            qDebug() << "please first read DingShiBook from local";
            return false;
        }
        auto head = DingShiBook;
        auto node = historyNode;
        std::vector<Piece> seq;
        while (node->parent.lock() != nullptr) {
            node = node->parent.lock();
            if (node->branches.size() > 1) {
                qDebug() << "addDS failed: dingshi can not has other branch";
                return false;
            }
        }
        node = node->branches[0];
        while (node != nullptr) {
            seq.push_back(node->move);
            if (!node->branches.empty())
                node = node->branches[0];
            else
                break;
        }
        if (seq.empty()) {
            qDebug() << "has no piece";
            return false;
        }
        int rotate = 0;
        AdjustPosToLeftDown(seq, rotate);//调整到左下
        bool ret1 = addBranchDS(head, seq);
        symmetrization(seq);//对称
        bool ret2 = addBranchDS(head, seq);
        return ret1 && ret2;
    }

    void openTryMode(bool open) {
        mTryMode = open;
        if (mTryMode == false) {
            mTryModeSeq.clear();
            seqIndex = -1;
            while (!undoTryStack.empty()) {
                undoTryStack.pop();
            }
            while (!redoTryStack.empty()) {
                redoTryStack.pop();
            }
            refresh();
        }
        else {
            mTryColor = (currentPlayer == Qt::black ? 0 : 1);
            repaint();
        }
    }
    void refresh() {
        if (historyNode == nullptr) {
            board = zeroBoard;
            repaint();
            return;
        }
        board = historyNode->boardHistory;
        repaint();
    }

private:
    bool isOccupied(int row, int col) {
        // 检查是否有棋子在这个位置
        if (board[row][col].color != 2) {
            return true;
        }
        return false;
    }
    int hoverRow; // 当前鼠标所在行
    int hoverCol; // 当前鼠标所在列

    Qt::GlobalColor currentPlayer; // 当前玩家（黑棋或白棋）
    QPixmap blackPiece; // 黑棋图片
    QPixmap whitePiece; // 白棋图片

    std::vector<std::vector<Piece>> zeroBoard;// x y

    //这两个可能有用，可以用当前节点，反向迭代回根节点获取历史和已下节点
    std::vector<Piece> pieceSeq;


    std::shared_ptr<SGFTreeNode> historyNode;

    //std::stack<std::vector<std::vector<Piece>>> history;  // 历史栈（用于撤销）  TODO:这个有问题
    //std::stack<std::vector<std::vector<Piece>>> undoStack;  // 重做栈（用于重做）
    //std::stack<std::vector<std::vector<Piece>>> redoStack;  // 重做栈（用于重做）
    int moveNumber;//当前手数
    int blackEaten;
    int whiteEaten;

    std::vector<std::pair<int, int>> blackLiberties;
    std::vector<std::pair<int, int>> whiteLiberties;
    std::vector<std::pair<int, int>> eatenNowList;
    float tiemu;//贴目
    std::shared_ptr<SGFTreeNode> root;
    SGFParser sgfParser;

    QTreeWidget* pieceTree;
    std::map<std::shared_ptr<SGFTreeNode>, QTreeWidgetItem*> treeItemMap;
    std::shared_ptr<SGFTreeNode> DingShiBook;
    std::map<std::string, std::string> DingShiSetupInfo;   
    std::string mDingShiBookPath;
public:
    std::vector<std::vector<Piece>> board;// x y
    std::map<std::string, std::string> setupInfo;//读取棋局获得的信息
    int allNumber;//总手数
    int mStepN;
    bool mTryMode;
    int mTryColor;
    std::vector<Piece> mTryModeSeq;
    std::stack<std::vector<std::vector<Piece>>> undoTryStack;  // 重做栈（用于重做）
    std::stack<std::vector<std::vector<Piece>>> redoTryStack;  // 重做栈（用于重做）
    int seqIndex;
    bool PracticeMode = false;


    bool hasCalc = false;
    std::set<std::pair<int, int>> filedLiberties;
    std::vector<std::vector<Filed*>> indexMap;
    std::vector<Filed*> whiteFiled;
    std::vector<Filed*> blackFiled;
    std::vector<Filed*> spaceFiled;

    std::set<Filed*> aliveFiled;
    std::set<Filed*> fuzzFiled;
    std::set<Filed*> deadFiled;
    GameSettings mSetting;
};

/*TODO:

 *  顶层分支(完成)
 *  统一读取出来的和下出来的子(完成)
 *  添加文件head(完成)
 *  进度条，前进 后退，大前进，开头 结尾 跳转(完成)
 *  劫争逻辑(完成)
 *
 *  分割类
 *
 *
 * 程序难点
 * 难点：获取图片  解析图片转化为二维数组  将数组放到棋盘上，然后选择一点进行推理。将可能的后续，用多个图给出或者以虚棋子显示在棋盘上。
 * 难点2：形式判断 是否终局 判定胜负。
 * 难点3：作为一个游戏，哪怕是自己对自己，需要完成。（悔棋、和棋 认输 退出等） (添加让子 贴目 时间 判定方式等要素)
 * 难点4：制作网络对战，可能有网络层 连接层 session层 游戏平台，游戏对战界面等。
 *
 *  匹配定式逻辑
    1.读取大棋盘
    2.清除非匹配部分,或者框选或修改，支持删除，放置。
    3.匹配结果合适的显示方式
    4.旋转，对称，黑白交换的匹配结果，并进行过滤相同结果。
    5.结果排序，近似不放一块。 bfs
    6.库的合理组织，以及定式录入的程序化。骗招是单方面的，给出警示标志，添加存储信息。
    7.合理的UI界面
 *
 *
    试下（对局不可试下） 手数 摆黑 摆白 交替等。。。
    存储 存储信息，让子... 贴目 对局双方 时间 对局结果 游戏 ...

    判定胜负和形式判断，形式判断需要在图上显示如何判定的。
    判定胜负简单一点需要先判定是否可以终局数子（是否收完所有单关和劫争）
    如果不能判定胜负，可以使用形式判断的函数给出结果。
    形式判断有很多模棱两可的判断。
    双活逻辑 对杀逻辑，（合理的逻辑：将这一片进行割出，作为研究对象，当两个绝顶聪明的人互相下）
    无胜负（三劫循环以上） 盘龙眼 摇头劫 长生。。。

    截图 模式识别（基础完成）
    入库（完成）
    组织一颗大树 检索 显示 跳转（完成）

    目前应该完成定式入库逻辑和匹配规则完善逻辑（旋转 定位等，先将结果作为字符串显示）（完成）
    在考虑合理的的字符串可视化。（或者这步先做更好）（完成）

    定式已经可以读入，但可惜在显示定式文件时存在问题bug readSGF或者showSGF有问题（完成）
    在获取下一步的时候，目前有问题。需要进行修改，修正定式方位和结果方位。之前没方位是可以匹配的。（完成）

    界面上删除tree分支。(完成)
    对定式后续结果进行显示(完成）
    缩小显示棋盘10*10(完成）
    网格布局显示或者使用滚动条（完成）

    应当对定式进行检查不能有分支，否则不能添加。(完成)
    黑白交换如何匹配(完成)

    (添加一些额外添加的子，添加 删除 修改) 节点。先做一个试下功能，再考虑在SGF中添加这种节点。
    截图识别功能有待加强（优化）
    存储结构有待加强和压缩，SGF费空间，检索慢，考虑使用数据库。
    入库需要多一些定式
    搜索N步（完成）


    主要应该区分比赛模式还是复盘模式（试下模式），还是练习模式（摆放模式+试下模式）。

    试下加入步数信息，和记录以及关闭试下后的记录
    试下模式：（基本完成）
    试下模式是任然支持围棋规则的试下，在当前状态下进行下棋，但是取消试下后恢复到原状态。
    也支持回退与前进，但不支持分支和任意添加棋子，比如一直摆黑。
    试下模式不应支持一直摆黑、一直摆白，删除棋子，移动棋子。试下有手数信息和前进回退。不支持分支。
    目前试下功能已经有了，可以进行试下，支持左键试下和W B键试下。
    但是不能进行删除节点和右键删除节点，不支持分支。稍微有点问题
    可能确实不应该支持W B试下，这样会捣乱黑白顺序。不好还原。
    星阵的做法是支持，只是在连续下黑时，中间的白实际是在停一手，没有下


    摆放模式（黑白某种颜色一直摆，或者删除，移动）：
    可以一直摆黑，或者一直摆白。不符合围棋规则，新加的棋子不计入棋数。
    鼠标左击按下棋子，右击删除节点。不支持回退和前进。
    但切换到黑白顺序下的情况，就符合围棋规则，进入试下模式。
    一旦进入摆放模式，就删掉试下seq。如果再进入试下模式，则开始添加seq。
    关掉试下模式时。

    考虑再添加一种摆放模式，作为一个节点，添加到棋局中，进行一些添加，删除和移动操作。
    或者直接在之后的死活题模式中添加这种模式。

    TODO:删除节点是不是应该只删本节点，而不是删所有后续节点，或者只删分支节点，
    然后把本节点删掉，把后续的嫡子节点接续。

    两块活棋的边界填满
    空填满子。
    然后数子
    19 * 19 = 361，181 180 黑贴3.75子，
    x - (361 - x) = 7.5, 2x = 361 + 7.5 = 368.5 = 185（黑赢） 177（白赢）
                                                  176      184
    目前初步实现了终局判定功能，有3个TODO未解决。
    是否终局还没实现，应该是在排除双活之后，如果还有belong=-1的情况的话，就是单官，那么应该提示未终局

    形式判断需要更细致的判断。如角部 拆二拆三 连接分断 对杀 打劫 双活。

    TODO:将单官和双活的空填上颜色，一半黑，一半白。
*/


/*
    //node由于它的branch中由一个元素变为2个元素，所以进行压缩，将后面所有的兄弟节点压入第一个元素，然后放入第二个元素
    void treeCompress(std::shared_ptr<SGFTreeNode> node, std::shared_ptr<SGFTreeNode> son) {
        //还有一种情况，就是这个点虽然在tree上没有分支，但是有2个子。也要压缩。
        if (node->branches.size() != 2) {
            return;
        }
        if (node == root) {
            QTreeWidgetItem *sonItem = treeItemMap[node];
            QList<QTreeWidgetItem*> wlist;
            for (int i = 1; i < pieceTree->topLevelItemCount(); ++i) {
                wlist.push_back(pieceTree->topLevelItem(i));
            }
            if (sonItem->childCount() == 0) {
                for (int i = 0; i < wlist.size(); i++) {
                     pieceTree->takeTopLevelItem(1);
                     sonItem->addChild(wlist[i]);
                }
            }
            else {
                //TODO: 应该递归压缩
                compress(root->branches[0]);
                pieceTree->addTopLevelItem(treeItemMap[son]);
            }
            return;
        }

        compress(node->branches[0]);
        QTreeWidgetItem* sonItem = treeItemMap[son];
        QTreeWidgetItem* item = treeItemMap[node];
        item->addChild(sonItem);
//        if (item->childCount() == 0) {
//            auto ppitem = item->parent();
//            if (ppitem == nullptr) {
//                return;
//            }
//            //平层子压缩
//            if (item != ppitem->child(0)) {
//                return;
//            }
//            auto dage = ppitem->child(1);//新大哥
//            QList<QTreeWidgetItem*> wlist;
//            for (int i = 2; i < ppitem->childCount(); i++) {
//                wlist.push_back(ppitem->child(i));
//            }
//            for (int i = 0; i < wlist.size(); i++) {
//                 ppitem->removeChild(wlist[i]);
//                 dage->addChild(wlist[i]);
//            }
//            ppitem->removeChild(dage);
//            item->addChild(dage);
//        }
//        else {
//            QList<QTreeWidgetItem*> wlist;
//            for (int i = 0; i < item->childCount(); i++) {
//                wlist.push_back(item->child(i));
//            }
//            for (int i = 1; i < wlist.size(); i++) {
//                item->removeChild(wlist[i]);
//                wlist[0]->addChild(wlist[i]);
//            }
//        }
    }
*/

#endif
