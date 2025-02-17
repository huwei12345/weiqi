#include "mainwindow.h"
#include "screencapture.h"
#include <QApplication>
#include <vector>
#include <boardwidget.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<Piece>("Piece");
    qRegisterMetaType<JudgeInfo>("JudgeInfo");
    qRegisterMetaType<JudgeInfo*>("JudgeInfo*");
    qRegisterMetaType<AnalyzeInfo>("AnalyzeInfo");
    qRegisterMetaType<AnalyzeInfo*>("AnalyzeInfo*");
    qRegisterMetaType<std::vector<std::vector<Piece>>>("std::vector<std::vector<Piece>>");
    qRegisterMetaType<SGFTreeNode>("SGFTreeNode");
    qRegisterMetaType<std::shared_ptr<SGFTreeNode>>("std::shared_ptr<SGFTreeNode>");
    MainWindow w;
    w.show();
    //ScreenCapture capture;
    //capture.resize(100, 100);
    //capture.show();
    //GoBoardWidget widget;
    //widget.show();
    return a.exec();
}
