/********************************************************************************
** Form generated from reading UI file 'choosestepdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSESTEPDIALOG_H
#define UI_CHOOSESTEPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChooseStepDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QTextEdit *textEdit;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ChooseStepDialog)
    {
        if (ChooseStepDialog->objectName().isEmpty())
            ChooseStepDialog->setObjectName(QString::fromUtf8("ChooseStepDialog"));
        ChooseStepDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(ChooseStepDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(ChooseStepDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

        widget_2 = new QWidget(ChooseStepDialog);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(widget_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        textEdit = new QTextEdit(widget_2);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        horizontalLayout_2->addWidget(textEdit);


        verticalLayout->addWidget(widget_2);

        widget = new QWidget(ChooseStepDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        buttonBox = new QDialogButtonBox(widget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);

        horizontalLayout->addWidget(buttonBox);


        verticalLayout->addWidget(widget);


        retranslateUi(ChooseStepDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ChooseStepDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ChooseStepDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ChooseStepDialog);
    } // setupUi

    void retranslateUi(QDialog *ChooseStepDialog)
    {
        ChooseStepDialog->setWindowTitle(QCoreApplication::translate("ChooseStepDialog", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("ChooseStepDialog", "\345\256\232\345\274\217\350\207\252\351\200\211\345\270\256\345\212\251", nullptr));
        label->setText(QCoreApplication::translate("ChooseStepDialog", "\351\200\211\346\213\251\346\255\245\346\225\260", nullptr));
        pushButton->setText(QCoreApplication::translate("ChooseStepDialog", "\345\256\232\345\274\217\351\233\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChooseStepDialog: public Ui_ChooseStepDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSESTEPDIALOG_H
