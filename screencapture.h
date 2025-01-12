#ifndef SCREENCAPTURE_H
#define SCREENCAPTURE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

#include <QApplication>
#include <QScreen>
#include <QPixmap>
#include <QBitmap>
#include <QCursor>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class ScreenCapture : public QWidget {
    Q_OBJECT

public:
    ScreenCapture(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
        setAttribute(Qt::WA_TranslucentBackground);
        grabMouse();
    }

    ~ScreenCapture() {
        releaseMouse();
    }

protected:
    void mouseMoveEvent(QMouseEvent *event) override {
        move(event->globalPos() - dragPos);
    }

    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            dragPos = event->globalPos() - frameGeometry().topLeft();
        }
    }

    void mouseReleaseEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            QScreen *screen = QGuiApplication::primaryScreen();
            QRect rect = QRect(mapFromGlobal(dragStartPos), mapFromGlobal(event->globalPos()));
            QPixmap pixmap = screen->grabWindow(0, rect.x(), rect.y(), rect.width(), rect.height());
            // 保存或处理截图...
            // 例如显示截图
            setPixmap(pixmap);
        }
    }

    void setPixmap(const QPixmap &pixmap) {
        QPainter painter(this);
        painter.drawPixmap(0, 0, pixmap);
    }

private:
    QPoint dragPos;
    QPoint dragStartPos;
};

#endif // SCREENCAPTURE_H
