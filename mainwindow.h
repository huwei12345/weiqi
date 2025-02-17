#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "imagerecognition.h"
#include "settingpage.h"

#include <QMainWindow>
#include <boardwidget.h>
class Kata;
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
    bool getAIPiece(Piece piece, int color);
    void getAIPieceSuccess(Piece *piece);
    void calculateScoreSuccess();
    void calculateEndResultSuccess();
signals:
    void keyEventCaptured(QKeyEvent *event);

protected:
    // 假设在主线程中控制子线程
    void closeEvent(QCloseEvent *event) override;

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

    void on_actionxuandian_triggered(bool checked);

    void on_toolButton_22_clicked();

    void on_BAlwaysBtn_clicked();

    void on_WAlwaysBtn_clicked();

    void on_toolButton_25_clicked();

    void on_RetractPiece_clicked();

    void on_giveUpBtn_clicked();

    void on_toolButton_20_clicked();

    void on_autoPlay_clicked(bool checked);

    void on_setting_triggered();

    void on_AIBtn_clicked();

    void on_toolButton_11_clicked();

    void on_AIPlayBtn_clicked(bool checked);

    void on_AIJudge_clicked();

    void on_actionfindDS_triggered();

    void on_toolButton_11_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    GoBoardWidget* goWidget;
    ImageRecognition* recTool;
    QPixmap blackPiece; // 黑棋图片
    QPixmap whitePiece; // 白棋图片
    QTimer* mRunAutoTimer;
    SettingPage* mSoftSetting;
    Kata* mKata;
    QThread *mKataThread;
};
#endif // MAINWINDOW_H
