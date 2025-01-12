#include "mainwindow.h"
#include "screencapture.h"
#include <QApplication>

#include <boardwidget.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //ScreenCapture capture;
    //capture.resize(100, 100);
    //capture.show();
    //GoBoardWidget widget;
    //widget.show();
    return a.exec();
}
