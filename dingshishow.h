#ifndef DINGSHISHOW_H
#define DINGSHISHOW_H
#include "piece.h"

#include <QPixmap>
#include <QWidget>

//用于显示后续定式的一个小图19 * 19, 要有之前的棋子，要有后续的棋子及手数标注，暂时可以不可操作，仅显示
class DingShiShow : public QWidget {
    Q_OBJECT
public:
    explicit DingShiShow(QWidget *parent = nullptr);
    DingShiShow(std::vector<std::vector<Piece>>& boarder, std::vector<Piece> &seq);

   public:

    std::vector<std::vector<Piece>> board;
    std::vector<Piece> seq;
    QPixmap blackPiece; // 黑棋图片
    QPixmap whitePiece; // 白棋图片
    void updateMoveLabel(QPainter &painter, int gridSize);
    QString colToChar(int col);
    void showDS(int index);
    void setWindSize(int size);
protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    int windowSize = 240;
    int mainSize = 640;
    double zoomRatio;
    bool m_dragging;
    QPoint m_dragPosition;
};

#endif // DINGSHISHOW_H
