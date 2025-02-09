/********************************************************************************
** Form generated from reading UI file 'helppage.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELPPAGE_H
#define UI_HELPPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HelpPage
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QPlainTextEdit *plainTextEdit;

    void setupUi(QWidget *HelpPage)
    {
        if (HelpPage->objectName().isEmpty())
            HelpPage->setObjectName(QString::fromUtf8("HelpPage"));
        HelpPage->resize(399, 532);
        verticalLayout = new QVBoxLayout(HelpPage);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        label = new QLabel(HelpPage);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        plainTextEdit = new QPlainTextEdit(HelpPage);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setEnabled(true);
        plainTextEdit->setLineWidth(1);
        plainTextEdit->setTabChangesFocus(false);
        plainTextEdit->setReadOnly(true);
        plainTextEdit->setBackgroundVisible(true);
        plainTextEdit->setCenterOnScroll(false);

        verticalLayout->addWidget(plainTextEdit);


        retranslateUi(HelpPage);

        QMetaObject::connectSlotsByName(HelpPage);
    } // setupUi

    void retranslateUi(QWidget *HelpPage)
    {
        HelpPage->setWindowTitle(QCoreApplication::translate("HelpPage", "Form", nullptr));
        label->setText(QCoreApplication::translate("HelpPage", "\345\277\253\346\215\267\351\224\256\350\256\260\345\275\225", nullptr));
        plainTextEdit->setPlainText(QCoreApplication::translate("HelpPage", "Ctrl + Z \346\222\244\351\224\200\n"
"Ctrl + X \351\207\215\345\201\232\n"
"Ctrl + E \345\210\244\346\226\255\346\237\220\347\251\272\346\230\257\345\220\246\346\230\257\347\234\274\n"
"Ctrl + R \345\210\244\346\226\255\345\256\232\345\274\217\344\270\213\344\270\200\346\255\245\357\274\210\345\277\205\351\241\273\350\257\273\345\205\245\357\274\211\n"
"Ctrl + B \350\220\275\344\270\213\351\273\221\345\255\220\n"
"Ctrl + W \350\220\275\344\270\213\347\231\275\345\255\220\n"
"Ctrl + G \347\273\210\345\261\200\345\210\244\345\256\232\n"
"Ctrl + D \345\210\240\351\231\244\346\243\213\345\255\220\346\240\221\344\270\212\347\232\204\346\237\220\345\255\220\346\210\226\346\237\220\345\210\206\346\224\257\n"
"Ctrl + T \345\201\234\344\270\200\346\211\213\n"
"\344\270\212\344\270\213\345\267\246\345\217\263\345\217\257\344\273\245\345\220\221\346\243\213\345\261\200\344\270\213\344\270\200\346\255\245\350\265\260\357\274\210\347\204\246\347\202\271\345\277\205\351\241\273\345\234\250\346\240\221\344\270\212\357\274\211", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HelpPage: public Ui_HelpPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELPPAGE_H
