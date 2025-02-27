/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <winratebar.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionguanyu;
    QAction *action;
    QAction *actionduqu;
    QAction *actioncunchu;
    QAction *actiontuichu;
    QAction *actionyonghu;
    QAction *actionundo;
    QAction *actionredo;
    QAction *actionjump;
    QAction *actiondelete;
    QAction *actiontry;
    QAction *actionsearchStep;
    QAction *actionjudgeWin;
    QAction *actionjudgeSituation;
    QAction *actionAIAnalysis;
    QAction *actionnextStep;
    QAction *setting;
    QAction *actionAIjudge;
    QAction *actionxuandian;
    QAction *actionfindDS;
    QAction *deepsearch;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTextEdit *textEdit;
    QWidget *processWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_6;
    QToolButton *storeBtn;
    QToolButton *LoadBtn;
    QToolButton *WinBtn;
    QToolButton *toolButton_2;
    QToolButton *toolButton_27;
    QToolButton *toolButton_4;
    QToolButton *clearBtn;
    QToolButton *toolButton;
    QSpacerItem *horizontalSpacer_8;
    QToolButton *judgeBtn;
    QToolButton *AIJudge;
    QToolButton *toolButton_11;
    QToolButton *AIBtn;
    QToolButton *AIPlayBtn;
    QSpacerItem *horizontalSpacer_7;
    QToolButton *addDSBtn;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_4;
    QToolButton *RetractPiece;
    QToolButton *toolButton_8;
    QToolButton *toolButton_19;
    QToolButton *toolButton_9;
    QToolButton *giveUpBtn;
    QSpacerItem *horizontalSpacer_5;
    QWidget *testWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *pieceLabel;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *toolButton_20;
    QToolButton *toolButton_21;
    QToolButton *toolButton_22;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_2;
    QToolButton *BAlwaysBtn;
    QToolButton *WAlwaysBtn;
    QToolButton *toolButton_25;
    QSpacerItem *horizontalSpacer_2;
    QWidget *watchWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSlider *horizontalSlider;
    QToolButton *Begin;
    QToolButton *leftFive;
    QToolButton *leftOne;
    QPushButton *autoPlay;
    QToolButton *rightOne;
    QToolButton *rightFive;
    QToolButton *End;
    QLineEdit *pieceEdit;
    QPushButton *pushButton;
    QWidget *gameWidget;
    QHBoxLayout *horizontalLayout_4;
    QWidget *analyzePanel;
    QVBoxLayout *verticalLayout;
    WinRateBar *rateBar;
    QWidget *widget_3;
    QGridLayout *gridLayout_2;
    QLabel *label_5;
    QLabel *label_7;
    QLabel *winLabel;
    QLabel *terrLabel;
    QLabel *calcLabel;
    QLabel *label_9;
    QSpacerItem *verticalSpacer;
    QWidget *panWidget;
    QHBoxLayout *horizontalLayout_5;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_6;
    QTreeWidget *pieceTree;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_2;
    QPlainTextEdit *plainTextEdit;
    QSpacerItem *verticalSpacer_2;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QMenu *menu_5;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1058, 688);
        actionguanyu = new QAction(MainWindow);
        actionguanyu->setObjectName(QString::fromUtf8("actionguanyu"));
        action = new QAction(MainWindow);
        action->setObjectName(QString::fromUtf8("action"));
        actionduqu = new QAction(MainWindow);
        actionduqu->setObjectName(QString::fromUtf8("actionduqu"));
        actioncunchu = new QAction(MainWindow);
        actioncunchu->setObjectName(QString::fromUtf8("actioncunchu"));
        actiontuichu = new QAction(MainWindow);
        actiontuichu->setObjectName(QString::fromUtf8("actiontuichu"));
        actionyonghu = new QAction(MainWindow);
        actionyonghu->setObjectName(QString::fromUtf8("actionyonghu"));
        actionundo = new QAction(MainWindow);
        actionundo->setObjectName(QString::fromUtf8("actionundo"));
        actionredo = new QAction(MainWindow);
        actionredo->setObjectName(QString::fromUtf8("actionredo"));
        actionjump = new QAction(MainWindow);
        actionjump->setObjectName(QString::fromUtf8("actionjump"));
        actiondelete = new QAction(MainWindow);
        actiondelete->setObjectName(QString::fromUtf8("actiondelete"));
        actiontry = new QAction(MainWindow);
        actiontry->setObjectName(QString::fromUtf8("actiontry"));
        actiontry->setCheckable(true);
        actionsearchStep = new QAction(MainWindow);
        actionsearchStep->setObjectName(QString::fromUtf8("actionsearchStep"));
        actionjudgeWin = new QAction(MainWindow);
        actionjudgeWin->setObjectName(QString::fromUtf8("actionjudgeWin"));
        actionjudgeSituation = new QAction(MainWindow);
        actionjudgeSituation->setObjectName(QString::fromUtf8("actionjudgeSituation"));
        actionAIAnalysis = new QAction(MainWindow);
        actionAIAnalysis->setObjectName(QString::fromUtf8("actionAIAnalysis"));
        actionnextStep = new QAction(MainWindow);
        actionnextStep->setObjectName(QString::fromUtf8("actionnextStep"));
        setting = new QAction(MainWindow);
        setting->setObjectName(QString::fromUtf8("setting"));
        actionAIjudge = new QAction(MainWindow);
        actionAIjudge->setObjectName(QString::fromUtf8("actionAIjudge"));
        actionxuandian = new QAction(MainWindow);
        actionxuandian->setObjectName(QString::fromUtf8("actionxuandian"));
        actionxuandian->setCheckable(true);
        actionfindDS = new QAction(MainWindow);
        actionfindDS->setObjectName(QString::fromUtf8("actionfindDS"));
        deepsearch = new QAction(MainWindow);
        deepsearch->setObjectName(QString::fromUtf8("deepsearch"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy);
        textEdit->setMaximumSize(QSize(16777215, 30));
        textEdit->setReadOnly(true);

        gridLayout->addWidget(textEdit, 0, 0, 1, 1);

        processWidget = new QWidget(centralwidget);
        processWidget->setObjectName(QString::fromUtf8("processWidget"));
        horizontalLayout = new QHBoxLayout(processWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 0, -1, 0);
        label_4 = new QLabel(processWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout->addWidget(label_4);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        storeBtn = new QToolButton(processWidget);
        storeBtn->setObjectName(QString::fromUtf8("storeBtn"));

        horizontalLayout->addWidget(storeBtn);

        LoadBtn = new QToolButton(processWidget);
        LoadBtn->setObjectName(QString::fromUtf8("LoadBtn"));

        horizontalLayout->addWidget(LoadBtn);

        WinBtn = new QToolButton(processWidget);
        WinBtn->setObjectName(QString::fromUtf8("WinBtn"));
        WinBtn->setCheckable(true);

        horizontalLayout->addWidget(WinBtn);

        toolButton_2 = new QToolButton(processWidget);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));

        horizontalLayout->addWidget(toolButton_2);

        toolButton_27 = new QToolButton(processWidget);
        toolButton_27->setObjectName(QString::fromUtf8("toolButton_27"));

        horizontalLayout->addWidget(toolButton_27);

        toolButton_4 = new QToolButton(processWidget);
        toolButton_4->setObjectName(QString::fromUtf8("toolButton_4"));

        horizontalLayout->addWidget(toolButton_4);

        clearBtn = new QToolButton(processWidget);
        clearBtn->setObjectName(QString::fromUtf8("clearBtn"));

        horizontalLayout->addWidget(clearBtn);

        toolButton = new QToolButton(processWidget);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));

        horizontalLayout->addWidget(toolButton);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_8);

        judgeBtn = new QToolButton(processWidget);
        judgeBtn->setObjectName(QString::fromUtf8("judgeBtn"));
        judgeBtn->setCheckable(true);
        judgeBtn->setChecked(false);

        horizontalLayout->addWidget(judgeBtn);

        AIJudge = new QToolButton(processWidget);
        AIJudge->setObjectName(QString::fromUtf8("AIJudge"));

        horizontalLayout->addWidget(AIJudge);

        toolButton_11 = new QToolButton(processWidget);
        toolButton_11->setObjectName(QString::fromUtf8("toolButton_11"));
        toolButton_11->setCheckable(true);

        horizontalLayout->addWidget(toolButton_11);

        AIBtn = new QToolButton(processWidget);
        AIBtn->setObjectName(QString::fromUtf8("AIBtn"));

        horizontalLayout->addWidget(AIBtn);

        AIPlayBtn = new QToolButton(processWidget);
        AIPlayBtn->setObjectName(QString::fromUtf8("AIPlayBtn"));
        AIPlayBtn->setCheckable(true);

        horizontalLayout->addWidget(AIPlayBtn);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);

        addDSBtn = new QToolButton(processWidget);
        addDSBtn->setObjectName(QString::fromUtf8("addDSBtn"));

        horizontalLayout->addWidget(addDSBtn);


        gridLayout->addWidget(processWidget, 2, 0, 1, 1);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_7 = new QHBoxLayout(widget);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_7->addWidget(label_3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_4);

        RetractPiece = new QToolButton(widget);
        RetractPiece->setObjectName(QString::fromUtf8("RetractPiece"));

        horizontalLayout_7->addWidget(RetractPiece);

        toolButton_8 = new QToolButton(widget);
        toolButton_8->setObjectName(QString::fromUtf8("toolButton_8"));

        horizontalLayout_7->addWidget(toolButton_8);

        toolButton_19 = new QToolButton(widget);
        toolButton_19->setObjectName(QString::fromUtf8("toolButton_19"));

        horizontalLayout_7->addWidget(toolButton_19);

        toolButton_9 = new QToolButton(widget);
        toolButton_9->setObjectName(QString::fromUtf8("toolButton_9"));

        horizontalLayout_7->addWidget(toolButton_9);

        giveUpBtn = new QToolButton(widget);
        giveUpBtn->setObjectName(QString::fromUtf8("giveUpBtn"));

        horizontalLayout_7->addWidget(giveUpBtn);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);


        gridLayout->addWidget(widget, 3, 0, 1, 1);

        testWidget = new QWidget(centralwidget);
        testWidget->setObjectName(QString::fromUtf8("testWidget"));
        horizontalLayout_3 = new QHBoxLayout(testWidget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 0, -1, 0);
        pieceLabel = new QLabel(testWidget);
        pieceLabel->setObjectName(QString::fromUtf8("pieceLabel"));

        horizontalLayout_3->addWidget(pieceLabel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        toolButton_20 = new QToolButton(testWidget);
        toolButton_20->setObjectName(QString::fromUtf8("toolButton_20"));

        horizontalLayout_3->addWidget(toolButton_20);

        toolButton_21 = new QToolButton(testWidget);
        toolButton_21->setObjectName(QString::fromUtf8("toolButton_21"));

        horizontalLayout_3->addWidget(toolButton_21);

        toolButton_22 = new QToolButton(testWidget);
        toolButton_22->setObjectName(QString::fromUtf8("toolButton_22"));

        horizontalLayout_3->addWidget(toolButton_22);

        horizontalSpacer_9 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_9);

        label_2 = new QLabel(testWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        BAlwaysBtn = new QToolButton(testWidget);
        BAlwaysBtn->setObjectName(QString::fromUtf8("BAlwaysBtn"));

        horizontalLayout_3->addWidget(BAlwaysBtn);

        WAlwaysBtn = new QToolButton(testWidget);
        WAlwaysBtn->setObjectName(QString::fromUtf8("WAlwaysBtn"));

        horizontalLayout_3->addWidget(WAlwaysBtn);

        toolButton_25 = new QToolButton(testWidget);
        toolButton_25->setObjectName(QString::fromUtf8("toolButton_25"));

        horizontalLayout_3->addWidget(toolButton_25);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        gridLayout->addWidget(testWidget, 4, 0, 1, 1);

        watchWidget = new QWidget(centralwidget);
        watchWidget->setObjectName(QString::fromUtf8("watchWidget"));
        horizontalLayout_2 = new QHBoxLayout(watchWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(11, 0, -1, 0);
        label = new QLabel(watchWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        horizontalSlider = new QSlider(watchWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider);

        Begin = new QToolButton(watchWidget);
        Begin->setObjectName(QString::fromUtf8("Begin"));

        horizontalLayout_2->addWidget(Begin);

        leftFive = new QToolButton(watchWidget);
        leftFive->setObjectName(QString::fromUtf8("leftFive"));

        horizontalLayout_2->addWidget(leftFive);

        leftOne = new QToolButton(watchWidget);
        leftOne->setObjectName(QString::fromUtf8("leftOne"));

        horizontalLayout_2->addWidget(leftOne);

        autoPlay = new QPushButton(watchWidget);
        autoPlay->setObjectName(QString::fromUtf8("autoPlay"));
        autoPlay->setMaximumSize(QSize(30, 25));
        autoPlay->setCheckable(true);

        horizontalLayout_2->addWidget(autoPlay);

        rightOne = new QToolButton(watchWidget);
        rightOne->setObjectName(QString::fromUtf8("rightOne"));

        horizontalLayout_2->addWidget(rightOne);

        rightFive = new QToolButton(watchWidget);
        rightFive->setObjectName(QString::fromUtf8("rightFive"));

        horizontalLayout_2->addWidget(rightFive);

        End = new QToolButton(watchWidget);
        End->setObjectName(QString::fromUtf8("End"));

        horizontalLayout_2->addWidget(End);

        pieceEdit = new QLineEdit(watchWidget);
        pieceEdit->setObjectName(QString::fromUtf8("pieceEdit"));

        horizontalLayout_2->addWidget(pieceEdit);

        pushButton = new QPushButton(watchWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_2->addWidget(pushButton);


        gridLayout->addWidget(watchWidget, 5, 0, 1, 1);

        gameWidget = new QWidget(centralwidget);
        gameWidget->setObjectName(QString::fromUtf8("gameWidget"));
        horizontalLayout_4 = new QHBoxLayout(gameWidget);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 0, -1, 0);
        analyzePanel = new QWidget(gameWidget);
        analyzePanel->setObjectName(QString::fromUtf8("analyzePanel"));
        verticalLayout = new QVBoxLayout(analyzePanel);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        rateBar = new WinRateBar(analyzePanel);
        rateBar->setObjectName(QString::fromUtf8("rateBar"));

        verticalLayout->addWidget(rateBar);

        widget_3 = new QWidget(analyzePanel);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        gridLayout_2 = new QGridLayout(widget_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_5 = new QLabel(widget_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 2, 0, 1, 1);

        label_7 = new QLabel(widget_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 3, 0, 1, 1);

        winLabel = new QLabel(widget_3);
        winLabel->setObjectName(QString::fromUtf8("winLabel"));

        gridLayout_2->addWidget(winLabel, 2, 1, 1, 1);

        terrLabel = new QLabel(widget_3);
        terrLabel->setObjectName(QString::fromUtf8("terrLabel"));

        gridLayout_2->addWidget(terrLabel, 3, 1, 1, 1);

        calcLabel = new QLabel(widget_3);
        calcLabel->setObjectName(QString::fromUtf8("calcLabel"));

        gridLayout_2->addWidget(calcLabel, 4, 1, 1, 1);

        label_9 = new QLabel(widget_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 4, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 6, 0, 1, 1);


        verticalLayout->addWidget(widget_3);


        horizontalLayout_4->addWidget(analyzePanel);

        panWidget = new QWidget(gameWidget);
        panWidget->setObjectName(QString::fromUtf8("panWidget"));
        horizontalLayout_5 = new QHBoxLayout(panWidget);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);

        horizontalLayout_4->addWidget(panWidget);

        widget_2 = new QWidget(gameWidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_6 = new QHBoxLayout(widget_2);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        pieceTree = new QTreeWidget(widget_2);
        pieceTree->setObjectName(QString::fromUtf8("pieceTree"));

        horizontalLayout_6->addWidget(pieceTree);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        widget_4 = new QWidget(widget_2);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        verticalLayout_2 = new QVBoxLayout(widget_4);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        plainTextEdit = new QPlainTextEdit(widget_4);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));

        verticalLayout_2->addWidget(plainTextEdit);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout_6->addWidget(widget_4);


        horizontalLayout_4->addWidget(widget_2);


        gridLayout->addWidget(gameWidget, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1058, 25));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu_4 = new QMenu(menubar);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        menu_5 = new QMenu(menubar);
        menu_5->setObjectName(QString::fromUtf8("menu_5"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menubar->addAction(menu_4->menuAction());
        menubar->addAction(menu_5->menuAction());
        menu->addAction(actionduqu);
        menu->addAction(actioncunchu);
        menu->addAction(setting);
        menu->addAction(actionyonghu);
        menu->addSeparator();
        menu->addAction(actiontuichu);
        menu_2->addAction(actionundo);
        menu_2->addAction(actionredo);
        menu_2->addAction(actionjump);
        menu_2->addAction(actiondelete);
        menu_2->addAction(actiontry);
        menu_3->addAction(actionjudgeWin);
        menu_3->addAction(actionjudgeSituation);
        menu_3->addAction(actionAIjudge);
        menu_3->addAction(actionAIAnalysis);
        menu_3->addSeparator();
        menu_3->addAction(actionnextStep);
        menu_3->addAction(actionxuandian);
        menu_3->addAction(actionfindDS);
        menu_3->addAction(deepsearch);
        menu_4->addAction(actionsearchStep);
        menu_4->addAction(setting);
        menu_5->addAction(action);
        menu_5->addSeparator();
        menu_5->addAction(actionguanyu);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionguanyu->setText(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216", nullptr));
        action->setText(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251\345\206\205\345\256\271", nullptr));
        actionduqu->setText(QCoreApplication::translate("MainWindow", "\350\257\273\345\217\226", nullptr));
        actioncunchu->setText(QCoreApplication::translate("MainWindow", "\345\255\230\345\202\250", nullptr));
        actiontuichu->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        actionyonghu->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267", nullptr));
        actionundo->setText(QCoreApplication::translate("MainWindow", "\346\222\244\351\224\200", nullptr));
        actionredo->setText(QCoreApplication::translate("MainWindow", "\351\207\215\345\201\232", nullptr));
        actionjump->setText(QCoreApplication::translate("MainWindow", "\350\267\263\350\275\254", nullptr));
        actiondelete->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
#if QT_CONFIG(shortcut)
        actiondelete->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+D", nullptr));
#endif // QT_CONFIG(shortcut)
        actiontry->setText(QCoreApplication::translate("MainWindow", "\350\257\225\344\270\213", nullptr));
        actionsearchStep->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256\346\220\234\347\264\242\346\255\245\346\225\260", nullptr));
        actionjudgeWin->setText(QCoreApplication::translate("MainWindow", "\345\210\244\345\256\232\350\203\234\350\264\237", nullptr));
        actionjudgeSituation->setText(QCoreApplication::translate("MainWindow", "\345\275\242\345\212\277\345\210\244\346\226\255", nullptr));
        actionAIAnalysis->setText(QCoreApplication::translate("MainWindow", "\346\231\272\350\203\275\345\210\206\346\236\220", nullptr));
        actionnextStep->setText(QCoreApplication::translate("MainWindow", "\345\256\232\345\274\217\344\270\213\344\270\200\346\255\245", nullptr));
        setting->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        actionAIjudge->setText(QCoreApplication::translate("MainWindow", "\346\231\272\350\203\275\350\243\201\345\210\244", nullptr));
        actionxuandian->setText(QCoreApplication::translate("MainWindow", "\345\256\232\345\274\217\351\200\211\347\202\271", nullptr));
        actionfindDS->setText(QCoreApplication::translate("MainWindow", "\346\241\206\351\200\211\346\237\245\345\256\232\345\274\217", nullptr));
        deepsearch->setText(QCoreApplication::translate("MainWindow", "\351\271\260\347\234\274\345\210\206\346\236\220", nullptr));
#if QT_CONFIG(tooltip)
        deepsearch->setToolTip(QCoreApplication::translate("MainWindow", "\351\271\260\347\234\274\345\210\206\346\236\220", nullptr));
#endif // QT_CONFIG(tooltip)
        label_4->setText(QCoreApplication::translate("MainWindow", "\347\240\224\347\251\266", nullptr));
        storeBtn->setText(QCoreApplication::translate("MainWindow", "\345\255\230\345\202\250", nullptr));
        LoadBtn->setText(QCoreApplication::translate("MainWindow", "\350\257\273\345\217\226", nullptr));
        WinBtn->setText(QCoreApplication::translate("MainWindow", "\345\210\244\345\256\232\350\203\234\350\264\237", nullptr));
        toolButton_2->setText(QCoreApplication::translate("MainWindow", "\350\257\273\345\217\226\345\256\232\345\274\217", nullptr));
        toolButton_27->setText(QCoreApplication::translate("MainWindow", "\350\277\221\344\274\274\345\256\232\345\274\217", nullptr));
        toolButton_4->setText(QCoreApplication::translate("MainWindow", "\350\257\225\344\270\213", nullptr));
        clearBtn->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272", nullptr));
#if QT_CONFIG(tooltip)
        toolButton->setToolTip(QCoreApplication::translate("MainWindow", "\344\273\205\346\270\205\347\251\272\345\275\242\345\212\277\345\210\244\346\226\255\346\256\213\344\275\231", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton->setText(QCoreApplication::translate("MainWindow", "reset", nullptr));
        judgeBtn->setText(QCoreApplication::translate("MainWindow", "\345\275\242\345\274\217\345\210\244\346\226\255", nullptr));
        AIJudge->setText(QCoreApplication::translate("MainWindow", "\346\231\272\350\203\275\350\243\201\345\210\244", nullptr));
        toolButton_11->setText(QCoreApplication::translate("MainWindow", "\346\231\272\350\203\275\345\210\206\346\236\220", nullptr));
        AIBtn->setText(QCoreApplication::translate("MainWindow", "AI", nullptr));
        AIPlayBtn->setText(QCoreApplication::translate("MainWindow", "AIplay", nullptr));
        addDSBtn->setText(QCoreApplication::translate("MainWindow", "\345\205\245\345\272\223", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\346\257\224\350\265\233", nullptr));
        RetractPiece->setText(QCoreApplication::translate("MainWindow", "\346\202\224\346\243\213", nullptr));
        toolButton_8->setText(QCoreApplication::translate("MainWindow", "\345\222\214\346\243\213", nullptr));
        toolButton_19->setText(QCoreApplication::translate("MainWindow", "\345\201\234\344\270\200\346\211\213", nullptr));
        toolButton_9->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        giveUpBtn->setText(QCoreApplication::translate("MainWindow", "\350\256\244\350\276\223", nullptr));
        pieceLabel->setText(QCoreApplication::translate("MainWindow", "\351\273\221\347\231\275", nullptr));
        toolButton_20->setText(QCoreApplication::translate("MainWindow", "\346\211\213\346\225\260", nullptr));
        toolButton_21->setText(QCoreApplication::translate("MainWindow", "\347\247\273\345\212\250", nullptr));
        toolButton_22->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\347\212\266\346\200\201", nullptr));
        BAlwaysBtn->setText(QCoreApplication::translate("MainWindow", "\346\221\206\351\273\221", nullptr));
        WAlwaysBtn->setText(QCoreApplication::translate("MainWindow", "\346\221\206\347\231\275", nullptr));
        toolButton_25->setText(QCoreApplication::translate("MainWindow", "\344\272\244\346\233\277", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\350\277\233\345\272\246\346\235\241", nullptr));
        Begin->setText(QCoreApplication::translate("MainWindow", "|<", nullptr));
        leftFive->setText(QCoreApplication::translate("MainWindow", "<<", nullptr));
        leftOne->setText(QCoreApplication::translate("MainWindow", "<", nullptr));
        autoPlay->setText(QCoreApplication::translate("MainWindow", "\342\226\266", nullptr));
        rightOne->setText(QCoreApplication::translate("MainWindow", ">", nullptr));
        rightFive->setText(QCoreApplication::translate("MainWindow", ">>", nullptr));
        End->setText(QCoreApplication::translate("MainWindow", "|>", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\350\267\263\350\275\254", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\350\203\234\347\216\207", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\347\233\256\346\225\260\345\267\256", nullptr));
        winLabel->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        terrLabel->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        calcLabel->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\350\256\241\347\256\227\351\207\217", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = pieceTree->headerItem();
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("MainWindow", "moveNum", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("MainWindow", "point", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221", nullptr));
        menu_3->setTitle(QCoreApplication::translate("MainWindow", "\345\267\245\345\205\267", nullptr));
        menu_4->setTitle(QCoreApplication::translate("MainWindow", "\351\200\211\351\241\271", nullptr));
        menu_5->setTitle(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
