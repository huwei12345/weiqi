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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
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
    QTextEdit *textEdit;
    QWidget *gameWidget;
    QHBoxLayout *horizontalLayout_4;
    QWidget *panWidget;
    QHBoxLayout *horizontalLayout_5;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_6;
    QTreeWidget *pieceTree;
    QLabel *ImageLabel;
    QSpacerItem *horizontalSpacer;
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
    QToolButton *judgeBtn;
    QToolButton *toolButton_10;
    QToolButton *toolButton_11;
    QSpacerItem *horizontalSpacer_7;
    QToolButton *addDSBtn;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_4;
    QToolButton *toolButton_6;
    QToolButton *toolButton_8;
    QToolButton *toolButton_19;
    QToolButton *toolButton_9;
    QToolButton *toolButton_7;
    QSpacerItem *horizontalSpacer_5;
    QWidget *testWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *toolButton_20;
    QToolButton *toolButton_21;
    QToolButton *toolButton_22;
    QToolButton *toolButton_23;
    QToolButton *toolButton_24;
    QToolButton *toolButton_25;
    QSpacerItem *horizontalSpacer_2;
    QWidget *watchWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSlider *horizontalSlider;
    QToolButton *Begin;
    QToolButton *leftFive;
    QToolButton *leftOne;
    QToolButton *rightOne;
    QToolButton *rightFive;
    QToolButton *End;
    QLineEdit *pieceEdit;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1058, 688);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy);
        textEdit->setMaximumSize(QSize(16777215, 30));

        verticalLayout->addWidget(textEdit);

        gameWidget = new QWidget(centralwidget);
        gameWidget->setObjectName(QString::fromUtf8("gameWidget"));
        horizontalLayout_4 = new QHBoxLayout(gameWidget);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 0, -1, 0);
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

        ImageLabel = new QLabel(widget_2);
        ImageLabel->setObjectName(QString::fromUtf8("ImageLabel"));

        horizontalLayout_6->addWidget(ImageLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);


        horizontalLayout_4->addWidget(widget_2);


        verticalLayout->addWidget(gameWidget);

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

        judgeBtn = new QToolButton(processWidget);
        judgeBtn->setObjectName(QString::fromUtf8("judgeBtn"));
        judgeBtn->setCheckable(true);
        judgeBtn->setChecked(false);

        horizontalLayout->addWidget(judgeBtn);

        toolButton_10 = new QToolButton(processWidget);
        toolButton_10->setObjectName(QString::fromUtf8("toolButton_10"));

        horizontalLayout->addWidget(toolButton_10);

        toolButton_11 = new QToolButton(processWidget);
        toolButton_11->setObjectName(QString::fromUtf8("toolButton_11"));

        horizontalLayout->addWidget(toolButton_11);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);

        addDSBtn = new QToolButton(processWidget);
        addDSBtn->setObjectName(QString::fromUtf8("addDSBtn"));

        horizontalLayout->addWidget(addDSBtn);


        verticalLayout->addWidget(processWidget);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_7 = new QHBoxLayout(widget);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_7->addWidget(label_3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_4);

        toolButton_6 = new QToolButton(widget);
        toolButton_6->setObjectName(QString::fromUtf8("toolButton_6"));

        horizontalLayout_7->addWidget(toolButton_6);

        toolButton_8 = new QToolButton(widget);
        toolButton_8->setObjectName(QString::fromUtf8("toolButton_8"));

        horizontalLayout_7->addWidget(toolButton_8);

        toolButton_19 = new QToolButton(widget);
        toolButton_19->setObjectName(QString::fromUtf8("toolButton_19"));

        horizontalLayout_7->addWidget(toolButton_19);

        toolButton_9 = new QToolButton(widget);
        toolButton_9->setObjectName(QString::fromUtf8("toolButton_9"));

        horizontalLayout_7->addWidget(toolButton_9);

        toolButton_7 = new QToolButton(widget);
        toolButton_7->setObjectName(QString::fromUtf8("toolButton_7"));

        horizontalLayout_7->addWidget(toolButton_7);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);


        verticalLayout->addWidget(widget);

        testWidget = new QWidget(centralwidget);
        testWidget->setObjectName(QString::fromUtf8("testWidget"));
        horizontalLayout_3 = new QHBoxLayout(testWidget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 0, -1, 0);
        label_2 = new QLabel(testWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

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

        toolButton_23 = new QToolButton(testWidget);
        toolButton_23->setObjectName(QString::fromUtf8("toolButton_23"));

        horizontalLayout_3->addWidget(toolButton_23);

        toolButton_24 = new QToolButton(testWidget);
        toolButton_24->setObjectName(QString::fromUtf8("toolButton_24"));

        horizontalLayout_3->addWidget(toolButton_24);

        toolButton_25 = new QToolButton(testWidget);
        toolButton_25->setObjectName(QString::fromUtf8("toolButton_25"));

        horizontalLayout_3->addWidget(toolButton_25);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(testWidget);

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


        verticalLayout->addWidget(watchWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1058, 25));
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
        ImageLabel->setText(QCoreApplication::translate("MainWindow", "Image", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\347\240\224\347\251\266", nullptr));
        storeBtn->setText(QCoreApplication::translate("MainWindow", "\345\255\230\345\202\250", nullptr));
        LoadBtn->setText(QCoreApplication::translate("MainWindow", "\350\257\273\345\217\226", nullptr));
        WinBtn->setText(QCoreApplication::translate("MainWindow", "\345\210\244\345\256\232\350\203\234\350\264\237", nullptr));
        toolButton_2->setText(QCoreApplication::translate("MainWindow", "\350\257\273\345\217\226\345\256\232\345\274\217", nullptr));
        toolButton_27->setText(QCoreApplication::translate("MainWindow", "\350\277\221\344\274\274\345\256\232\345\274\217", nullptr));
        toolButton_4->setText(QCoreApplication::translate("MainWindow", "\350\257\225\344\270\213", nullptr));
        clearBtn->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272", nullptr));
        toolButton->setText(QCoreApplication::translate("MainWindow", "reset", nullptr));
        judgeBtn->setText(QCoreApplication::translate("MainWindow", "\345\275\242\345\274\217\345\210\244\346\226\255", nullptr));
        toolButton_10->setText(QCoreApplication::translate("MainWindow", "\346\231\272\350\203\275\350\243\201\345\210\244", nullptr));
        toolButton_11->setText(QCoreApplication::translate("MainWindow", "\346\231\272\350\203\275\345\210\206\346\236\220", nullptr));
        addDSBtn->setText(QCoreApplication::translate("MainWindow", "\345\205\245\345\272\223", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\346\257\224\350\265\233", nullptr));
        toolButton_6->setText(QCoreApplication::translate("MainWindow", "\346\202\224\346\243\213", nullptr));
        toolButton_8->setText(QCoreApplication::translate("MainWindow", "\345\222\214\346\243\213", nullptr));
        toolButton_19->setText(QCoreApplication::translate("MainWindow", "\345\201\234\344\270\200\346\211\213", nullptr));
        toolButton_9->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        toolButton_7->setText(QCoreApplication::translate("MainWindow", "\350\256\244\350\276\223", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\351\273\221\347\231\275", nullptr));
        toolButton_20->setText(QCoreApplication::translate("MainWindow", "\346\211\213\346\225\260", nullptr));
        toolButton_21->setText(QCoreApplication::translate("MainWindow", "\347\247\273\345\212\250", nullptr));
        toolButton_22->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        toolButton_23->setText(QCoreApplication::translate("MainWindow", "\346\221\206\351\273\221", nullptr));
        toolButton_24->setText(QCoreApplication::translate("MainWindow", "\346\221\206\347\231\275", nullptr));
        toolButton_25->setText(QCoreApplication::translate("MainWindow", "\344\272\244\346\233\277", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\350\277\233\345\272\246\346\235\241", nullptr));
        Begin->setText(QCoreApplication::translate("MainWindow", "|<", nullptr));
        leftFive->setText(QCoreApplication::translate("MainWindow", "<<", nullptr));
        leftOne->setText(QCoreApplication::translate("MainWindow", "<", nullptr));
        rightOne->setText(QCoreApplication::translate("MainWindow", ">", nullptr));
        rightFive->setText(QCoreApplication::translate("MainWindow", ">>", nullptr));
        End->setText(QCoreApplication::translate("MainWindow", "|>", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\350\267\263\350\275\254", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
