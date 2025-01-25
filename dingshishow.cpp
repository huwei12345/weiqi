#include "dingshishow.h"

#include <QKeyEvent>
#include <QPainter>
#include <QDebug>
DingShiShow::DingShiShow(QWidget *parent) : QWidget(parent), m_dragging(false)
{
    resize(windowSize, windowSize);
    zoomRatio = (double)windowSize / (double)mainSize;
    qDebug() << windowSize << " / " << mainSize << "zoomRatio " << zoomRatio;
    blackPiece = QPixmap(":/images/black.png"); // 使用资源文件
    blackPiece = blackPiece.scaled(QSize(30 * zoomRatio, 30 * zoomRatio), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    whitePiece = QPixmap(":/images/white.png"); // 使用资源文件
    whitePiece = whitePiece.scaled(QSize(30 * zoomRatio, 30 * zoomRatio), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    board.assign(BOARDWIDTH, std::vector<Piece>(BOARDWIDTH));
    setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
}


QString DingShiShow::colToChar(int col) {
    QString numx;
    if (col >= 8) {
        numx = QString('A' + col + 1);
    }
    else {
        numx = QString('A' + col);
    }
    return numx;
}

void DingShiShow::showDS(int index)
{
    //显示在鼠标位置的上方的 (x + index * windowSize , y - 10)
    show();
    QPoint p = pos();
    p.setX(p.x() + index * windowSize);
    p.setY(p.y() - 15);
    move(p);
}

void DingShiShow::setWindSize(int size)
{
    windowSize = size;
}

DingShiShow::DingShiShow(std::vector<std::vector<Piece> > &boarder, std::vector<Piece> &seq) : DingShiShow()
{
    board = boarder;
    this->seq = seq;
}

void DingShiShow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)
    windowSize = std::min(width(), height());
    zoomRatio = (double)windowSize / (double)mainSize;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    blackPiece = QPixmap(":/images/black.png"); // 使用资源文件
    blackPiece = blackPiece.scaled(QSize(30 * zoomRatio, 30 * zoomRatio), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    whitePiece = QPixmap(":/images/white.png"); // 使用资源文件
    whitePiece = whitePiece.scaled(QSize(30 * zoomRatio, 30 * zoomRatio), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    int boardSize = 19;
    int margin = std::max(windowSize / 50, 3); // 留出30像素的边距
    int gridSize = (std::min(width(), height()) - 2 * margin) / 18; // 计算实际棋盘格子大小

    // 绘制棋盘背景
    painter.fillRect(margin, margin, width() - 2 * margin, height() - 2 * margin, QColor(255, 223, 186));

    // 绘制棋盘线条
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);

    for (int i = 0; i < boardSize; ++i) {
        // 绘制纵向和横向的线
        painter.drawLine(margin + gridSize * i, margin, margin + gridSize * i, margin + gridSize * 18);
        painter.drawLine(margin, margin + gridSize * i, gridSize * 18 + margin, margin + gridSize * i);
    }

    // 标注数字
    QFont font = painter.font();
    font.setPointSize(10);
    painter.setFont(font);

    // 竖线标注
    for (int i = 0; i < boardSize; ++i) {
        int x = margin + gridSize * i + gridSize / 2 - 2;
        int y = margin - 10; // 放在棋盘上方
        // 防止第一个数字标注与棋盘重合
        painter.drawText(x, y, colToChar(i));
    }

    // 横线标注
    for (int i = 0; i < boardSize; ++i) {
        int x = margin - 25; // 放在棋盘左侧
        int y = margin + gridSize * i + gridSize / 2 - 1;
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
    QPen penold = painter.pen();
    for (int i = 0; i < (int)seq.size(); i++) {
        if (seq[i].color == 1) {
            painter.drawPixmap(margin + seq[i].col * gridSize - whitePiece.width() / 2,
                       margin + seq[i].row * gridSize - whitePiece.height() / 2,
                       whitePiece);
        }
        else if (seq[i].color == 0) {
            painter.drawPixmap(margin + seq[i].col * gridSize - blackPiece.width() / 2,
                               margin + seq[i].row * gridSize - blackPiece.height() / 2,
                               blackPiece);
        }
        int row = margin + seq[i].row * gridSize + zoomRatio* 5;
        int col = 0;
        QString text = QString::number(i);
        if (i < 10) {
            col = margin + seq[i].col * gridSize - zoomRatio * 5;
        }
        else if (i >= 10 && i < 100) {
            col = margin + seq[i].col * gridSize - zoomRatio* 10;
        }
        else if (i >= 100) {
            col = margin + seq[i].col * gridSize - zoomRatio* 15;
        }
        QFont font = painter.font();
        //font.setFamily("Arial");           // 设置字体为 Arial
        font.setPointSize(std::max(int(10 * zoomRatio), 4));             // 设置字体大小
        //font.setPixelSize(std::max(int(10 * zoomRatio), 5));
        font.setBold(true);                // 设置加粗

        //font.setWeight(QFont::DemiBold);   // 设置半粗体
        painter.setFont(font);
        // 设置文本颜色
        QPen pen;
        if (seq[i].color == 0) {
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
    }

    painter.setPen(penold);

//    // 绘制鼠标悬浮位置的小方框
//    if (hoverRow != -1 && hoverCol != -1 && isValid(hoverRow, hoverCol)) {
//        if (currentPlayer == Qt::black) {
//            painter.setBrush(QBrush(Qt::black));
//            painter.drawRect(margin + hoverCol * gridSize - 5, margin + hoverRow * gridSize - 5, 10, 10);
//        }
//        else {
//            painter.setBrush(QBrush(Qt::white));
//            painter.drawRect(margin + hoverCol * gridSize - 5, margin + hoverRow * gridSize - 5, 10, 10);
//        }
//    }


//    for (auto p : blackLiberties) {
//        painter.setBrush(QBrush(Qt::black));
//        painter.drawRect(margin + p.second * gridSize - 5, margin + p.first * gridSize - 5, 10, 10);
//    }

//    for (auto p : whiteLiberties) {
//        painter.setBrush(QBrush(Qt::white));
//        painter.drawRect(margin + p.second * gridSize - 5, margin + p.first * gridSize - 5, 10, 10);
//    }

//    for (auto p : eatenNowList) {
//        painter.setBrush(QBrush(Qt::green));
//        painter.drawRect(margin + p.second * gridSize - 6, margin + p.first * gridSize - 6, 10, 12);
//    }
    //当前棋子加一个小红旗标示
}

void DingShiShow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Q) { // 检查是否按下了Q键
        close(); // 调用close()方法来关闭窗口
    } else {
        QWidget::keyPressEvent(event); // 如果不是Q键，则调用基类的keyPressEvent
    }
}

void DingShiShow::updateMoveLabel(QPainter& painter, int gridSize) {


}

    void DingShiShow::mousePressEvent(QMouseEvent *event)  {
        if (event->button() == Qt::LeftButton) {
            m_dragging = true;
            m_dragPosition = event->pos();
            event->accept();
        }
    }
    void DingShiShow::mouseMoveEvent(QMouseEvent *event)  {
        if (m_dragging && (event->buttons() & Qt::LeftButton)) {
            move(pos() + event->pos() - m_dragPosition);
            repaint();
            m_dragPosition = event->pos();
            event->accept();
        }
    }
    void DingShiShow::mouseReleaseEvent(QMouseEvent *event)  {
        if (event->button() == Qt::LeftButton) {
            m_dragging = false;
            event->accept();
        }
    }
