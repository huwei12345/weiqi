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
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *gameWidget;
    QHBoxLayout *horizontalLayout_4;
    QWidget *panWidget;
    QHBoxLayout *horizontalLayout_5;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_6;
    QTreeWidget *pieceTree;
    QWidget *processWidget;
    QHBoxLayout *horizontalLayout;
    QToolButton *storeBtn;
    QToolButton *LoadBtn;
    QToolButton *WinBtn;
    QToolButton *toolButton_26;
    QToolButton *toolButton_27;
    QToolButton *toolButton_4;
    QToolButton *clearBtn;
    QToolButton *judgeBtn;
    QToolButton *toolButton_6;
    QToolButton *toolButton_19;
    QToolButton *toolButton_7;
    QToolButton *toolButton_8;
    QToolButton *toolButton_9;
    QToolButton *toolButton_10;
    QToolButton *toolButton;
    QToolButton *toolButton_11;
    QWidget *testWidget;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *toolButton_20;
    QToolButton *toolButton_21;
    QToolButton *toolButton_22;
    QToolButton *toolButton_23;
    QToolButton *toolButton_24;
    QToolButton *toolButton_25;
    QWidget *watchWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSlider *horizontalSlider;
    QToolButton *toolButton_14;
    QToolButton *toolButton_12;
    QToolButton *toolButton_13;
    QToolButton *toolButton_16;
    QToolButton *toolButton_17;
    QToolButton *toolButton_15;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1117, 661);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gameWidget = new QWidget(centralwidget);
        gameWidget->setObjectName(QString::fromUtf8("gameWidget"));
        horizontalLayout_4 = new QHBoxLayout(gameWidget);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        panWidget = new QWidget(gameWidget);
        panWidget->setObjectName(QString::fromUtf8("panWidget"));
        horizontalLayout_5 = new QHBoxLayout(panWidget);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));

        horizontalLayout_4->addWidget(panWidget);

        widget_2 = new QWidget(gameWidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_6 = new QHBoxLayout(widget_2);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        pieceTree = new QTreeWidget(widget_2);
        pieceTree->setObjectName(QString::fromUtf8("pieceTree"));

        horizontalLayout_6->addWidget(pieceTree);


        horizontalLayout_4->addWidget(widget_2);


        verticalLayout->addWidget(gameWidget);

        processWidget = new QWidget(centralwidget);
        processWidget->setObjectName(QString::fromUtf8("processWidget"));
        horizontalLayout = new QHBoxLayout(processWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        storeBtn = new QToolButton(processWidget);
        storeBtn->setObjectName(QString::fromUtf8("storeBtn"));

        horizontalLayout->addWidget(storeBtn);

        LoadBtn = new QToolButton(processWidget);
        LoadBtn->setObjectName(QString::fromUtf8("LoadBtn"));

        horizontalLayout->addWidget(LoadBtn);

        WinBtn = new QToolButton(processWidget);
        WinBtn->setObjectName(QString::fromUtf8("WinBtn"));

        horizontalLayout->addWidget(WinBtn);

        toolButton_26 = new QToolButton(processWidget);
        toolButton_26->setObjectName(QString::fromUtf8("toolButton_26"));
        QFont font;
        font.setBold(true);
        toolButton_26->setFont(font);

        horizontalLayout->addWidget(toolButton_26);

        toolButton_27 = new QToolButton(processWidget);
        toolButton_27->setObjectName(QString::fromUtf8("toolButton_27"));

        horizontalLayout->addWidget(toolButton_27);

        toolButton_4 = new QToolButton(processWidget);
        toolButton_4->setObjectName(QString::fromUtf8("toolButton_4"));

        horizontalLayout->addWidget(toolButton_4);

        clearBtn = new QToolButton(processWidget);
        clearBtn->setObjectName(QString::fromUtf8("clearBtn"));

        horizontalLayout->addWidget(clearBtn);

        judgeBtn = new QToolButton(processWidget);
        judgeBtn->setObjectName(QString::fromUtf8("judgeBtn"));
        judgeBtn->setCheckable(true);
        judgeBtn->setChecked(false);

        horizontalLayout->addWidget(judgeBtn);

        toolButton_6 = new QToolButton(processWidget);
        toolButton_6->setObjectName(QString::fromUtf8("toolButton_6"));

        horizontalLayout->addWidget(toolButton_6);

        toolButton_19 = new QToolButton(processWidget);
        toolButton_19->setObjectName(QString::fromUtf8("toolButton_19"));

        horizontalLayout->addWidget(toolButton_19);

        toolButton_7 = new QToolButton(processWidget);
        toolButton_7->setObjectName(QString::fromUtf8("toolButton_7"));

        horizontalLayout->addWidget(toolButton_7);

        toolButton_8 = new QToolButton(processWidget);
        toolButton_8->setObjectName(QString::fromUtf8("toolButton_8"));

        horizontalLayout->addWidget(toolButton_8);

        toolButton_9 = new QToolButton(processWidget);
        toolButton_9->setObjectName(QString::fromUtf8("toolButton_9"));

        horizontalLayout->addWidget(toolButton_9);

        toolButton_10 = new QToolButton(processWidget);
        toolButton_10->setObjectName(QString::fromUtf8("toolButton_10"));

        horizontalLayout->addWidget(toolButton_10);

        toolButton = new QToolButton(processWidget);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));

        horizontalLayout->addWidget(toolButton);

        toolButton_11 = new QToolButton(processWidget);
        toolButton_11->setObjectName(QString::fromUtf8("toolButton_11"));

        horizontalLayout->addWidget(toolButton_11);


        verticalLayout->addWidget(processWidget);

        testWidget = new QWidget(centralwidget);
        testWidget->setObjectName(QString::fromUtf8("testWidget"));
        horizontalLayout_3 = new QHBoxLayout(testWidget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        toolButton_20 = new QToolButton(testWidget);
        toolButton_20->setObjectName(QString::fromUtf8("toolButton_20"));

        horizontalLayout_3->addWidget(toolButton_20);

        toolButton_21 = new QToolButton(testWidget);
        toolButton_21->setObjectName(QString::fromUtf8("toolButton_21"));

        horizontalLayout_3->addWidget(toolButton_21);

        toolButton_22 = new QToolButton(testWidget);
        toolButton_22->setObjectName(QString::fromUtf8("toolButton_22"));

        horizontalLayout_3->addWidget(toolButton_22);

        toolButton_23 = new QToolButton(testWidget);
        toolButton_23->setObjectName(QString::fromUtf8("toolButton_23"));

        horizontalLayout_3->addWidget(toolButton_23);

        toolButton_24 = new QToolButton(testWidget);
        toolButton_24->setObjectName(QString::fromUtf8("toolButton_24"));

        horizontalLayout_3->addWidget(toolButton_24);

        toolButton_25 = new QToolButton(testWidget);
        toolButton_25->setObjectName(QString::fromUtf8("toolButton_25"));

        horizontalLayout_3->addWidget(toolButton_25);


        verticalLayout->addWidget(testWidget);

        watchWidget = new QWidget(centralwidget);
        watchWidget->setObjectName(QString::fromUtf8("watchWidget"));
        horizontalLayout_2 = new QHBoxLayout(watchWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(watchWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        horizontalSlider = new QSlider(watchWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider);

        toolButton_14 = new QToolButton(watchWidget);
        toolButton_14->setObjectName(QString::fromUtf8("toolButton_14"));

        horizontalLayout_2->addWidget(toolButton_14);

        toolButton_12 = new QToolButton(watchWidget);
        toolButton_12->setObjectName(QString::fromUtf8("toolButton_12"));

        horizontalLayout_2->addWidget(toolButton_12);

        toolButton_13 = new QToolButton(watchWidget);
        toolButton_13->setObjectName(QString::fromUtf8("toolButton_13"));

        horizontalLayout_2->addWidget(toolButton_13);

        toolButton_16 = new QToolButton(watchWidget);
        toolButton_16->setObjectName(QString::fromUtf8("toolButton_16"));

        horizontalLayout_2->addWidget(toolButton_16);

        toolButton_17 = new QToolButton(watchWidget);
        toolButton_17->setObjectName(QString::fromUtf8("toolButton_17"));

        horizontalLayout_2->addWidget(toolButton_17);

        toolButton_15 = new QToolButton(watchWidget);
        toolButton_15->setObjectName(QString::fromUtf8("toolButton_15"));

        horizontalLayout_2->addWidget(toolButton_15);

        lineEdit = new QLineEdit(watchWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);

        pushButton = new QPushButton(watchWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout->addWidget(watchWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1117, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = pieceTree->headerItem();
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("MainWindow", "moveNum", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("MainWindow", "point", nullptr));
        storeBtn->setText(QCoreApplication::translate("MainWindow", "\345\255\230\345\202\250", nullptr));
        LoadBtn->setText(QCoreApplication::translate("MainWindow", "\350\257\273\345\217\226", nullptr));
        WinBtn->setText(QCoreApplication::translate("MainWindow", "\345\210\244\345\256\232\350\203\234\350\264\237", nullptr));
        toolButton_26->setText(QCoreApplication::translate("MainWindow", "\344\270\213\344\270\200\346\255\245", nullptr));
        toolButton_27->setText(QCoreApplication::translate("MainWindow", "\350\277\221\344\274\274\345\256\232\345\274\217", nullptr));
        toolButton_4->setText(QCoreApplication::translate("MainWindow", "\350\257\225\344\270\213", nullptr));
        clearBtn->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272", nullptr));
        judgeBtn->setText(QCoreApplication::translate("MainWindow", "\345\275\242\345\274\217\345\210\244\346\226\255", nullptr));
        toolButton_6->setText(QCoreApplication::translate("MainWindow", "\346\202\224\346\243\213", nullptr));
        toolButton_19->setText(QCoreApplication::translate("MainWindow", "\345\201\234\344\270\200\346\211\213", nullptr));
        toolButton_7->setText(QCoreApplication::translate("MainWindow", "\350\256\244\350\276\223", nullptr));
        toolButton_8->setText(QCoreApplication::translate("MainWindow", "\345\222\214\346\243\213", nullptr));
        toolButton_9->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        toolButton_10->setText(QCoreApplication::translate("MainWindow", "\346\231\272\350\203\275\350\243\201\345\210\244", nullptr));
        toolButton->setText(QCoreApplication::translate("MainWindow", "reset", nullptr));
        toolButton_11->setText(QCoreApplication::translate("MainWindow", "\346\231\272\350\203\275\345\210\206\346\236\220", nullptr));
        toolButton_20->setText(QCoreApplication::translate("MainWindow", "\346\211\213\346\225\260", nullptr));
        toolButton_21->setText(QCoreApplication::translate("MainWindow", "\347\247\273\345\212\250", nullptr));
        toolButton_22->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        toolButton_23->setText(QCoreApplication::translate("MainWindow", "\346\221\206\351\273\221", nullptr));
        toolButton_24->setText(QCoreApplication::translate("MainWindow", "\346\221\206\347\231\275", nullptr));
        toolButton_25->setText(QCoreApplication::translate("MainWindow", "\344\272\244\346\233\277", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\350\277\233\345\272\246\346\235\241", nullptr));
        toolButton_14->setText(QCoreApplication::translate("MainWindow", "|<", nullptr));
        toolButton_12->setText(QCoreApplication::translate("MainWindow", "<", nullptr));
        toolButton_13->setText(QCoreApplication::translate("MainWindow", ">", nullptr));
        toolButton_16->setText(QCoreApplication::translate("MainWindow", "<<", nullptr));
        toolButton_17->setText(QCoreApplication::translate("MainWindow", ">>", nullptr));
        toolButton_15->setText(QCoreApplication::translate("MainWindow", "|>", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\350\267\263\350\275\254", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
