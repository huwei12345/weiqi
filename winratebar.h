#ifndef WINRATEBAR_H
#define WINRATEBAR_H

#include <QObject>

#include <QWidget>
#include <QPainter>
#include <QTimer>

class WinRateBar : public QWidget
{
    Q_OBJECT

public:
    WinRateBar(QWidget *parent = nullptr)
        : QWidget(parent), blackWinRate(50), whiteWinRate(50)
    {
        setFixedSize(200, 50); // 设置长方形的尺寸
    }
    void setWinRate(float black, float white)
    {
        blackWinRate = black;
        whiteWinRate = white;
        repaint(); // 触发重绘
    }
protected:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter painter(this);

        // 绘制黑棋部分（左边）
        painter.setBrush(Qt::black);
        painter.drawRect(0, 0, width() * blackWinRate / 100, height());

        // 绘制白棋部分（右边）
        painter.setBrush(Qt::white);
        painter.drawRect(width() * blackWinRate / 100, 0, width() * whiteWinRate / 100, height());
    }
private:
    float blackWinRate; // 黑棋胜率
    float whiteWinRate; // 白棋胜率
};


#endif // WINRATEBAR_H
