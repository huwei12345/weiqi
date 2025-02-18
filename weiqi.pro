QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


#OPENCV_DIR = D:/cv/opencv/build
## 设置 OpenCV 的 include 目录和 lib 目录
#INCLUDEPATH += $$OPENCV_DIR/include
#LIBS += -L$$OPENCV_DIR/x64/mingw/lib
## 添加 OpenCV 库文件
#LIBS += -lopencv_world4100

SOURCES += \
    MyProtocolStream.cpp \
    aboutdialog.cpp \
    boardwidget.cpp \
    dingshishow.cpp \
    dingshishowwidget.cpp \
    gameresearch.cpp \
    gamesettings.cpp \
    helppage.cpp \
    imagerecognition.cpp \
    judgecalcdialog.cpp \
    kata.cpp \
    main.cpp \
    mainwindow.cpp \
    piece.cpp \
    screencapture.cpp \
    screenshot.cpp \
    settingpage.cpp \
    sgfparser.cpp \
    threadsafequeue.cpp \
    timecontrol.cpp

HEADERS += \
    MyProtocolStream.h \
    aboutdialog.h \
    boardwidget.h \
    dingshishow.h \
    dingshishowwidget.h \
    gameresearch.h \
    gamesettings.h \
    helppage.h \
    imagerecognition.h \
    judgecalcdialog.h \
    kata.h \
    mainwindow.h \
    piece.h \
    screencapture.h \
    screenshot.h \
    settingpage.h \
    sgfparser.h \
    threadsafequeue.h \
    timecontrol.h

FORMS += \
    aboutdialog.ui \
    helppage.ui \
    judgecalcdialog.ui \
    mainwindow.ui \
    settingpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc

LIBS += -L$$PWD/../cvbuild/install/x64/mingw/lib/ -llibopencv_world4100.dll
INCLUDEPATH += $$PWD/../cvbuild/install/include
DEPENDPATH += $$PWD/../cvbuild/install/x64/mingw/bin
