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
#include "gamesettings.h"
#include "piece.h"
#include "sgfparser.h"
#include "timecontrol.h"
extern int dx[4];
extern int dy[4];

extern const int BOARDWIDTH;
extern const int HEIGHT;
extern const int WIDTH;


class GoGameLogic : public QWidget {
    Q_OBJECT

public:
    explicit GoGameLogic(QWidget *parent = nullptr) : QWidget(parent), hoverRow(-1), hoverCol(-1) {

    }


    initializeBoard();// (初始化棋盘)
    startNewGame();// (开始新游戏)
    setBoardSize(int size);// (设置棋盘大小)
    playMove(int x, int y);// (执行玩家落子)
    isMoveLegal(int x, int y);// (检查落子是否合法)
    checkCapture(int x, int y);// (检查是否有提子)
    switchPlayer();// (切换玩家)
    isGameOver();// (判断游戏是否结束)
    calculateScore();// (计算得分)
    undoMove();// (悔棋)
    loadGameState();// (加载游戏状态)
    saveGameState();// (保存游戏状态)

    checkVictory();// (检查胜负)
    printBoard();// (打印棋盘)

    **getCurrentBoardState()**：提供当前棋盘的状态，方便GameResearch类加载和使用。
    **getMoveHistory()**：提供当前棋局的历史记录，供研究模式分析使用。
    **checkGameOver()**：判断游戏是否结束，供研究模式在加载棋局后判断当前状态。

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
        history.push(board);
        currentPlayer = Qt::black;
        moveNumber = 1;
        allNumber = 1;
        blackEaten = 0;
        whiteEaten = 0;
        tiemu = 7.5;
    }
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

        // 横线标注
        for (int i = 0; i < boardSize; ++i) {
            int x = margin + gridSize * i + gridSize / 2 - 23;
            int y = margin - 5; // 放在棋盘上方
            // 防止第一个数字标注与棋盘重合
            painter.drawText(x, y, QString::number(i + 1));
        }

        // 竖线标注
        for (int i = 0; i < boardSize; ++i) {
            int x = margin - 20; // 放在棋盘左侧
            int y = margin + gridSize * i + gridSize / 2 - 15;
            if (i >= 0)
                painter.drawText(x, y, QString('A' + i));
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
        updateMoveLabel(painter, gridSize);

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
        //当前棋子加一个小红旗标示
    }

    void updateMoveLabel(QPainter& painter, int gridSize) {
        // 获取最近 5 颗棋子的手数
        int margin = 30; // 留出30像素的边距
        // 构建显示文本
        QString text;
        int cur = moveNumber - 1;
        int count = 5;
        QPen penold = painter.pen();
        while (cur >= 1 && count != 0) {
            Piece &piece = pieceSeq[cur - 1];
            text = QString::number(piece.moveNumber);
            int row = margin + piece.row * gridSize + 5;
            int col = 0;
            if (piece.moveNumber < 10) {
                col = margin + piece.col * gridSize - 5;
            }
            else if (piece.moveNumber >= 10 && piece.moveNumber < 100) {
                col = margin + piece.col * gridSize - 10;
            }
            else if (piece.moveNumber >= 100) {
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
            if (piece.moveNumber + 1 == moveNumber) {
                pen.setColor(Qt::red);
            }
            painter.setPen(pen);
            painter.drawText(col, row, text);
            cur--;
            count--;
        }
        painter.setPen(penold);

        //TODO:被提子后，这个子上的标记不显示
    }

    // 判断位置是否合法
    bool isValid(int x, int y) {
        return x >= 0 && x < BOARDWIDTH && y >= 0 && y < BOARDWIDTH;
    }

    // 检查一个区域是否是眼 8个位置都要判断，
    // TODO: 还需要判断是否周围被这个颜色包围
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

    bool judgeJieZheng(std::vector<std::vector<Piece>>& boarder , int row, int col, int color) {
        qDebug() << "jiezheng start";
        //TODO: 三劫循环应看6手之前 四届循环看8手之前。
        if (history.size() <= 1) {
            return true;
        }
        std::vector<std::vector<Piece>> board1 = history.top();
        history.pop();
        std::vector<std::vector<Piece>>& board2 = history.top();
        bool equal = true;
        for (int i = 0; i < 19; i++) {
            for (int j = 0; j < 19; j++) {
                if (board2[i][j].color != boarder[i][j].color) {
                    equal = false;
                }
            }
        }
        if (equal == true) {
            history.push(board1);
            return false;
        }
        history.push(board1);
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
        qDebug() << " row1    " << row << "col1        " << col;
        newBoard[row][col].color = color;
        int ace = getAceOfPoint(newBoard, row, col, color);
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
        qDebug() << " row    " << row << "col        " << col;
        std::queue<std::pair<int, int>> que;
        int color = boarder[row][col].color;
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
            qDebug() << "row " << row + 1 << "col" << col + 1 << "color : " << color << "is eaten";
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
            bool ret = judgeJieZheng(newBoard, row, col, color);
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
            qDebug() << "Row: " << row + 1 << ", Column: " << col + 1 << "Color: " << board[row][col].color << " Ace: " << getAceOfPoint(board, row, col, board[row][col].color);
        }
        else {
            qDebug() << "block";
        }
    }

    bool putPiece(int row, int col, int color, std::shared_ptr<SGFTreeNode> node) {
        bool ret = putPiece(row, col, color);
        if (ret) {
            auto p = node->parent.lock();
            if (node->startMoveNum == 0 && p != nullptr) {
                node->startMoveNum = p->endMoveNum + 1;
            }
            else if (node->startMoveNum == 0) {
                node->startMoveNum = 1;
            }
            if (node->endMoveNum == 0) {
                node->endMoveNum = node->startMoveNum;
            }
            else {
                node->endMoveNum++;
            }
            node->boardHistory.push_back(board);
        }
        return ret;
    }

    bool putPiece(int row, int col, int color) {
        if (checkAllowPut(row, col, color)) {
            board[row][col].color = color;
            currentPlayer = (color == 0 ? Qt::white : Qt::black);
            board[row][col].row = row;
            board[row][col].col = col;
            board[row][col].moveNumber = moveNumber++;  // 记录下棋的手数
            if (moveNumber > allNumber) {
                allNumber = moveNumber;
            }
            history.push(board);
            pieceSeq.push_back(board[row][col]);
            return true;
        }
        else {
            qDebug() << "not allow put ";
            return false;
        }
    }


    void onLeftClick(QMouseEvent *event) {
        int margin = 30;
        int gridSize = (width() - 2 * margin) / 19;
        int row = std::round((float)(event->y() - margin) / (float)gridSize);
        int col = std::round((float)(event->x() - margin) / (float)gridSize);
        if (!isValid(row, col)) {
            return;
        }
        // 输出点击的棋盘坐标
        qDebug() << "Row: " << row + 1 << ", Column: " << col + 1;
        // 检查该位置是否已经有棋子
        if (isOccupied(row, col)) {
            return; // 如果该位置已被占据，则不放置棋子
        }

        // 交替放置棋子
        if (currentPlayer == Qt::black) {
            putPiece(row, col, 0);

        } else {
            putPiece(row, col, 1);
        }
        // 检查棋子是否符合规则
        // 触发重绘
        repaint();
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
        if (row != hoverRow || col != hoverCol && isValid(row, col)) {
            hoverRow = row;
            hoverCol = col;

            // 触发窗口重绘
            update();
        }
    }

    // 撤销一步
       void undo() {
           qDebug() << "undo " << history.size();
           if (history.size() > 1) {
               //undo栈顶永远是当前界面
               redoStack.push(history.top());  // 恢复上一步的棋盘状态
               history.pop();
               board = history.top();
               std::cout << "Undo performed." << std::endl;
               moveNumber--;
               repaint();
           }
           else {
               qDebug() << "can not undo";
           }
       }

       // 重做撤销的操作
       void redo() {
           qDebug() << "redo " << redoStack.size();
           if (!redoStack.empty()) {
               board = redoStack.top();  // 恢复重做的棋盘状态
               redoStack.pop();
               std::cout << "Redo performed." << std::endl;
               history.push(board);
               moveNumber++;
               repaint();
           }
           else {
               qDebug() << "can not redo";
           }
       }
public:
       // 捕获按键事件
       void onKeyPressEvent(QKeyEvent *event) {
           if (event->key() == Qt::Key_Z && event->modifiers() == Qt::ControlModifier) {
               undo();  // Ctrl + Z 执行撤销

           } else if (event->key() == Qt::Key_X && event->modifiers() == Qt::ControlModifier) {
               redo();  // Ctrl + X 执行重做
           } else if (event->key() == Qt::Key_B && event->modifiers() == Qt::ControlModifier) {
               int margin = 30;
               int gridSize = (width() - 2 * margin) / 19;
               QPoint mousePos = this->mapFromGlobal(QCursor::pos());  // 获取鼠标在窗口中的位置
               int row = std::round((float)(mousePos.y() - margin) / (float)gridSize);
               int col = std::round((float)(mousePos.x() - margin) / (float)gridSize);
               if (!isValid(row, col)) {
                   return;
               }
               // 输出点击的棋盘坐标
               qDebug() << "Row: " << row + 1 << ", Column: " << col + 1;
               // 检查该位置是否已经有棋子
               if (isOccupied(row, col)) {
                   return; // 如果该位置已被占据，则不放置棋子
               }
               putPiece(row, col, 0);
               repaint();
           } else if (event->key() == Qt::Key_N && event->modifiers() == Qt::ControlModifier) {
               int margin = 30;
               int gridSize = (width() - 2 * margin) / 19;
               QPoint mousePos = this->mapFromGlobal(QCursor::pos());  // 获取鼠标在窗口中的位置
               int row = std::round((float)(mousePos.y() - margin) / (float)gridSize);
               int col = std::round((float)(mousePos.x() - margin) / (float)gridSize);

               // 输出点击的棋盘坐标
               qDebug() << "Row: " << row + 1 << ", Column: " << col + 1;
               // 检查该位置是否已经有棋子
               if (isOccupied(row, col)) {
                   return; // 如果该位置已被占据，则不放置棋子
               }
               putPiece(row, col, 1);
               repaint();
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
               qDebug() << "Row: " << row + 1 << ", Column: " << col + 1 << " is BEye ? " << isEye(row, col, 0);
               qDebug() << "Row: " << row + 1 << ", Column: " << col + 1 << " is WEye ? " << isEye(row, col, 1);
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
                            qDebug() << "[i,j]" << (char)('A' + i) << " " << j + 1 << " " << " blackTerritory  " << st.size();
                            blackScore += st.size();
                            //此处不包括死子，所以存在的死子算2遍
                            for (auto& p : st) {
                                blackLiberties.push_back(p);
                            }
                        } else if (blackTerritory < whiteTerritory) {
                            qDebug() << "[i,j]" << (char)('A' + i) << " " << j + 1 << " " << " whiteTerritory  " << st.size();
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
                            qDebug() << "xxxxxxx " << (char)('A' + i) << " yyyyy " << j + 1 << " b " << black << " w " << white;
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
            qDebug() << "eye " << (char)('A' + r.first) << " " << r.second + 1;
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


    //需要加入的节点分支，对应图item
    bool showBranch(std::shared_ptr<SGFTreeNode> node, QTreeWidgetItem* parItem) {
        if (parItem == NULL) {
            return false;
        }
        QTreeWidgetItem* first = NULL;
        QTreeWidgetItem* last  = NULL;
        //将分支第一个棋作为一个节点，内部其他棋作为这个节点的子
        for (auto piece : node->moves) {
            //TOSEE: 分支就先不画了，点击再画
            //bool ret = putPiece(piece.row, piece.col, piece.color, node);

            QTreeWidgetItem* item = new QTreeWidgetItem;
            QString str = QString('A' + piece.row) + QString::number(piece.col + 1) + " "+ (piece.color == 0 ? "B" : "W");
            item->setText(0, str);
            if (first == NULL) {
                first = item;
                parItem->addChild(item);
            }
            else {
                first->addChild(item);
            }
            last = item;

        }
        if (node->branches.size() > 0 && last != NULL) {
            //第一个作为顺序继承

            showSGF(node->branches[0], first);
            for (int i = 1; i < node->branches.size(); i++) {
                showBranch(node->branches[i], last);
            }
        }
    }

    //顶层
    bool showSGF(std::shared_ptr<SGFTreeNode> node, QTreeWidgetItem* parent) {
        QTreeWidgetItem* last = NULL;
        for (auto piece : node->moves) {
            if (parent == NULL) {
                putPiece(piece.row, piece.col, piece.color, node);
            }
            QTreeWidgetItem* item = new QTreeWidgetItem;
            QString str = QString('A' + piece.row) + QString::number(piece.col + 1) + " "+ (piece.color == 0 ? "B" : "W");
            QString str2 = QString::number(node->startMoveNum) + "  " + QString::number(node->endMoveNum);
            item->setText(0, str);
            item->setText(1, str2);
            last = item;
            if (parent == NULL)
                pieceTree->addTopLevelItem(item);
            else
                parent->addChild(item);
        }
        if (node->branches.size() > 0 && last != NULL) {
            //第一个作为顺序继承
            showSGF(node->branches[0], parent);
            for (int i = 1; i < node->branches.size(); i++) {
                showBranch(node->branches[i], last);
            }
        }
        return true;
    }

    // 读取 .sgf 文件并解析棋谱
    bool readSGF(const std::string &filename) {
        root = sgfParser.parse(filename);
        showSGF(root, NULL);
        repaint();
        return true;
    }

    bool saveSGF(const std::string &filename) {
        sgfParser.saveSGF(filename, root);
        return true;
    }
//    // 读取 .sgf 文件并解析棋谱
//    bool readSGF(const std::string &filename) {

//        std::ifstream file(filename);
//        if (!file.is_open()) {
//            std::cerr << "can not open: " << filename << std::endl;
//            return false;
//        }

//        std::string line;
//        std::string sgfContent;
//        while (std::getline(file, line)) {
//            sgfContent += line;  // 读取整个文件
//        }
//        file.close();

//        // 使用正则表达式来匹配棋谱的每一步
//        std::regex moveRegex(R"([;](B|W)\[([a-s]{2})\])");
//        std::smatch match;

//        // 初始化棋盘为空
//        for (int i = 0; i < HEIGHT; ++i) {
//            for (int j = 0; j < WIDTH; ++j) {
//                board[i][j].color = 2;
//            }
//        }

//        // 遍历棋谱内容，匹配每一步落子
//        std::string::const_iterator searchStart(sgfContent.cbegin());
//        while (std::regex_search(searchStart, sgfContent.cend(), match, moveRegex)) {
//            char player = match[1].str()[0];  // 'B' 或 'W'
//            std::string coords = match[2].str();  // 坐标，如 'ab'
//            // 将坐标转换为棋盘索引
//            int x = charToIndex(coords[0]);
//            int y = charToIndex(coords[1]);

//            // 根据棋手更新棋盘
//            if (player == 'B') {
//                putPiece(y, x, 0);
//            } else if (player == 'W') {
//                putPiece(y, x, 1);
//            }
//            searchStart = match.suffix().first;  // 继续查找下一步
//        }
//        repaint();
//        return true;
//    }

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
    void getEverySeq(std::vector<std::vector<Piece>> &boarder, std::vector<std::vector<Piece>>& pieceSeqList) {
        std::vector<Piece> pieceSeq;
        for (int i = 0; i < BOARDWIDTH; i++) {
            for (int j = 0; j < BOARDWIDTH; j++) {
                if (boarder[i][j].color != 2) {
                    pieceSeq.push_back(boarder[i][j]);
                }
            }
        }
        int n = 0;
        std::set<int> st;
        getSeq(pieceSeq, n, pieceSeqList, mask, 0, st);
        getSeq(pieceSeq, n, pieceSeqList, mask, 1, st);
    }


    void getSeq(std::vector<Piece> pieceSeq, int index, std::vector<std::vector<Piece>>& res, std::vector<int> cur, int curColor, std::set<int> st) {
        if (index == pieceSeq.size() && cur.size() == pieceSeq.size()) {
            res.push_back(cur);
            return;
        }
        for (int i = 0; i < pieceSeq.size(); i++) {
            if (pieceSeq[i].color == curColor && !st.count(i)) {
                st.insert(i);
                cur[index] = pieceSeq[i];
                getSeq(pieceSeq, index + 1, res, cur);
                st.erase(i);
            }
        }
    }

    void remember(std::vector<std::vector<Piece>> &boarder, int row, int col, int color, int stepN, std::vector<std::vector<Piece>>& res) {
        int size = boarder.size();
        int number = (6 * size + 1) * (2 * size + 1) * size / 2;
        for (int i = 0; i < number; i++) {
            //遍历每种排列，不能随便排，要考虑颜色。number < n!
            std::vector<Piece> pieceSeq;
            //getPieceSeqFromBoarder(boarder, pieceSeq, number);
            //这种方式还有利于将错误棋局导向正确棋局
            getNextStep(pieceSeq, DingShiBook, row, col, color, stepN, res);
            showNextNStep(res);
        }
    }

    //已知一种确定的顺序pieceSeq
    //已知下一步要下在哪
    //获取stepN步分支，存入res
    //另外考虑，不同方向，不同角，对称位置，其实是同一种
    //也就是每个Node对应一个piece，和N个branch,其实像前缀树
    void getNextStep(std::vector<Piece> & pieceSeq, SGFTreeNode& root, int row, int col, int color, int stepN, std::vector<std::vector<Piece>>& res) {
        
    }

    //最多显示20种，所以应当先将stepN调小，越往后越大，前边变化多，后边变化少
    void showNextNStep(std::vector<std::vector<Piece>> &res) {
        //将分支以多个方框并列显示在界面上侧
        //按照胜率或者按照常用程度排列
    }

    // 打印棋盘 test BW
    void printBoard2() {
        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                if (board[i][j].color == 0) {
                    std::cout << "B ";
                } else if (board[i][j].color == 1) {
                    std::cout << "W ";
                } else {
                    std::cout << ". ";  // 空格
                }
            }
            std::cout << std::endl;
        }
    }

    //保存棋谱
    // 保存棋谱为 .sgf 格式
//    bool saveSGF(const std::string &filename) {
//        std::ofstream file(filename);
//        if (!file.is_open()) {
//            std::cerr << "can not open: " << filename << std::endl;
//            return false;
//        }
//        // 记录棋谱的前缀
//        file << "(;FF[4]CA[UTF-8]ST[2]GM[1]";
//        // 遍历棋盘并记录每一步棋
//        //bool firstMove = true;  // 标记是否是第一次落子
//        for (auto& piece : pieceSeq) {
//            int x = piece.col;
//            int y = piece.row;
////            if (!firstMove) {
////                file << ";";
////                firstMove = false;
////            }
//            file << ";";
//            if (piece.color == 0) {
//                file << "B[" << indexToChar(x) << indexToChar(y) << "]";
//            } else if (piece.color == 1) {
//                file << "W[" << indexToChar(x) << indexToChar(y) << "]";
//            }
//            //firstMove = false; // 不再是第一次落子
//        }
//        // 结束棋谱
//        file << ")";
//        file.close();
//        return true;
//    }

public:
    void clear() {
        board = zeroBoard;
        pieceSeq.clear();
        while (!history.empty()) {
            history.pop();
        }
        while (!redoStack.empty()) {
            redoStack.pop();
        }
        moveNumber = 0;
        allNumber = 0;
        blackEaten = 0;
        whiteEaten = 0;
        currentPlayer = Qt::black;
        repaint();
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

    std::vector<std::vector<Piece>> board;// x y
    std::vector<std::vector<Piece>> zeroBoard;// x y
    std::stack<std::vector<std::vector<Piece>>> history;  // 历史栈（用于撤销）
    std::stack<std::vector<std::vector<Piece>>> redoStack;  // 重做栈（用于重做）
    std::vector<Piece> pieceSeq;
    int moveNumber;//当前手数
    int allNumber;//总手数
    int blackEaten;
    int whiteEaten;

    std::vector<std::pair<int, int>> blackLiberties;
    std::vector<std::pair<int, int>> whiteLiberties;
    std::vector<std::pair<int, int>> eatenNowList;
    float tiemu;//贴目
    std::shared_ptr<SGFTreeNode> root;
    SGFParser sgfParser;

    QTreeWidget* pieceTree;
};


//TODO:

/*
    存储 存储信息，让子... 贴目 对局双方 时间 对局结果 游戏 ...

    判定胜负和形式判断，形式判断需要在图上显示如何判定的。
    判定胜负简单一点需要先判定是否可以终局数子（是否收完所有单关和劫争）
    如果不能判定胜负，可以使用形式判断的函数给出结果。
    形式判断有很多模棱两可的判断。

    劫争逻辑 双活逻辑

    无胜负

    盘龙眼 摇头劫 长生。。。


    截图 模式识别，入库，组织一颗大树 检索 显示 跳转
*/

#endif

