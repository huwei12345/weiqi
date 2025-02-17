/********************************************************************************
** Form generated from reading UI file 'judgecalcdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JUDGECALCDIALOG_H
#define UI_JUDGECALCDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_JudgeCalcDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *labelA;
    QLabel *label_3;
    QLabel *labelB;
    QLabel *label_4;
    QLabel *labelC;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *JudgeCalcDialog)
    {
        if (JudgeCalcDialog->objectName().isEmpty())
            JudgeCalcDialog->setObjectName(QString::fromUtf8("JudgeCalcDialog"));
        JudgeCalcDialog->resize(331, 223);
        verticalLayout = new QVBoxLayout(JudgeCalcDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(JudgeCalcDialog);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(16);
        font.setBold(false);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        widget = new QWidget(JudgeCalcDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(100, 0, 7, 0);
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        labelA = new QLabel(widget);
        labelA->setObjectName(QString::fromUtf8("labelA"));

        gridLayout->addWidget(labelA, 0, 1, 1, 1);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        labelB = new QLabel(widget);
        labelB->setObjectName(QString::fromUtf8("labelB"));

        gridLayout->addWidget(labelB, 1, 1, 1, 1);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        labelC = new QLabel(widget);
        labelC->setObjectName(QString::fromUtf8("labelC"));

        gridLayout->addWidget(labelC, 2, 1, 1, 1);


        verticalLayout->addWidget(widget);

        buttonBox = new QDialogButtonBox(JudgeCalcDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setLayoutDirection(Qt::RightToLeft);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(JudgeCalcDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), JudgeCalcDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), JudgeCalcDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(JudgeCalcDialog);
    } // setupUi

    void retranslateUi(QDialog *JudgeCalcDialog)
    {
        JudgeCalcDialog->setWindowTitle(QCoreApplication::translate("JudgeCalcDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("JudgeCalcDialog", "\345\275\223\345\211\215\345\275\242\345\212\277", nullptr));
        label_2->setText(QCoreApplication::translate("JudgeCalcDialog", "\351\242\206\345\205\210", nullptr));
        labelA->setText(QCoreApplication::translate("JudgeCalcDialog", "0", nullptr));
        label_3->setText(QCoreApplication::translate("JudgeCalcDialog", "\347\231\275", nullptr));
        labelB->setText(QCoreApplication::translate("JudgeCalcDialog", "0", nullptr));
        label_4->setText(QCoreApplication::translate("JudgeCalcDialog", "\351\273\221", nullptr));
        labelC->setText(QCoreApplication::translate("JudgeCalcDialog", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class JudgeCalcDialog: public Ui_JudgeCalcDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JUDGECALCDIALOG_H
