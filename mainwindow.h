#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <boardwidget.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *event) override {
            // 发射信号，将键盘事件传递给子窗口
            emit keyEventCaptured(event);
        }

signals:
    void keyEventCaptured(QKeyEvent *event);

private slots:

    void on_LoadBtn_clicked();

    void on_storeBtn_clicked();

    void on_WinBtn_clicked();

    void on_clearBtn_clicked();

    void on_judgeBtn_clicked(bool checked);

    void on_toolButton_clicked();

    void on_pieceTree_itemClicked(QTreeWidgetItem *item, int column);

    void on_toolButton_2_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_Begin_clicked();

    void on_End_clicked();

    void on_leftFive_clicked();

    void on_leftOne_clicked();

    void on_rightFive_clicked();

    void on_rightOne_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    GoBoardWidget* goWidget;

};
#endif // MAINWINDOW_H
