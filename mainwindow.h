#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "imagerecognition.h"

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

    void showSetupInfo(std::map<std::string, std::string> setupInfo);

    void Quit();
signals:
    void keyEventCaptured(QKeyEvent *event);

public slots:
    void playerChange(int currentPlayer);

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

    void on_toolButton_27_clicked();

    void on_addDSBtn_clicked();
    void on_pieceTree_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);


    void on_pieceTree_customContextMenuRequested(const QPoint &pos);

    void on_toolButton_4_clicked(bool checked);
    void on_WinBtn_clicked(bool checked);

    void on_toolButton_19_clicked();


    void on_toolButton_9_clicked();

    void on_autoPlay_clicked();

    void on_actiontuichu_triggered();
    void on_actionguanyu_triggered();


    void on_action_triggered();

    void on_actionsearchStep_triggered();

    void on_actioncunchu_triggered();

    void on_actionduqu_triggered();

    void on_actionjudgeWin_triggered();

    void on_actionnextStep_triggered();

    void on_actionundo_triggered();

    void on_actionredo_triggered();

    void on_actionjump_triggered();

    void on_actiondelete_triggered();

    void on_actiontry_triggered(bool checked);

    void on_actionshezhi_2_triggered();

    void on_actionshezhi_triggered();

    void on_actiontheme_triggered();

private:
    Ui::MainWindow *ui;
    GoBoardWidget* goWidget;
    ImageRecognition* recTool;
    QPixmap blackPiece; // 黑棋图片
    QPixmap whitePiece; // 白棋图片
};
#endif // MAINWINDOW_H
