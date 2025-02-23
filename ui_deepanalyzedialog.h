/********************************************************************************
** Form generated from reading UI file 'deepanalyzedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEEPANALYZEDIALOG_H
#define UI_DEEPANALYZEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DeepAnalyzeDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QToolBox *toolBox;
    QWidget *page;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_8;
    QLabel *label_7;
    QLabel *label_9;
    QLabel *label_6;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DeepAnalyzeDialog)
    {
        if (DeepAnalyzeDialog->objectName().isEmpty())
            DeepAnalyzeDialog->setObjectName(QString::fromUtf8("DeepAnalyzeDialog"));
        DeepAnalyzeDialog->resize(856, 643);
        verticalLayout_2 = new QVBoxLayout(DeepAnalyzeDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(DeepAnalyzeDialog);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        label->setFont(font);

        verticalLayout_2->addWidget(label);

        toolBox = new QToolBox(DeepAnalyzeDialog);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        page->setGeometry(QRect(0, 0, 834, 469));
        verticalLayout = new QVBoxLayout(page);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(page);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(page);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(page);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);

        label_5 = new QLabel(page);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout->addWidget(label_5);

        toolBox->addItem(page, QString::fromUtf8("Page 1"));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setGeometry(QRect(0, 0, 834, 469));
        verticalLayout_3 = new QVBoxLayout(page_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_8 = new QLabel(page_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_8);

        label_7 = new QLabel(page_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout_3->addWidget(label_7);

        label_9 = new QLabel(page_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        verticalLayout_3->addWidget(label_9);

        label_6 = new QLabel(page_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_3->addWidget(label_6);

        toolBox->addItem(page_2, QString::fromUtf8("Page 2"));

        verticalLayout_2->addWidget(toolBox);

        buttonBox = new QDialogButtonBox(DeepAnalyzeDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(DeepAnalyzeDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), DeepAnalyzeDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DeepAnalyzeDialog, SLOT(reject()));

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DeepAnalyzeDialog);
    } // setupUi

    void retranslateUi(QDialog *DeepAnalyzeDialog)
    {
        DeepAnalyzeDialog->setWindowTitle(QCoreApplication::translate("DeepAnalyzeDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("DeepAnalyzeDialog", "\351\271\260\347\234\274\347\263\273\347\273\237", nullptr));
        label_2->setText(QCoreApplication::translate("DeepAnalyzeDialog", "\351\273\221\346\226\271", nullptr));
        label_3->setText(QCoreApplication::translate("DeepAnalyzeDialog", "\346\237\261\347\212\266\345\233\276\357\274\214\345\246\231\346\211\213\343\200\201\346\201\266\346\211\213", nullptr));
        label_4->setText(QCoreApplication::translate("DeepAnalyzeDialog", "\346\237\261\347\212\266\345\233\276 \344\270\200\351\200\211\343\200\201\344\272\214\351\200\211\343\200\201\344\270\211\351\200\211\343\200\201\345\205\266\344\273\226", nullptr));
        label_5->setText(QCoreApplication::translate("DeepAnalyzeDialog", "\345\220\273\345\220\210\345\272\246", nullptr));
        toolBox->setItemText(toolBox->indexOf(page), QCoreApplication::translate("DeepAnalyzeDialog", "Page 1", nullptr));
        label_8->setText(QCoreApplication::translate("DeepAnalyzeDialog", "\347\231\275\346\226\271", nullptr));
        label_7->setText(QCoreApplication::translate("DeepAnalyzeDialog", "\346\237\261\347\212\266\345\233\276\357\274\214\345\246\231\346\211\213\343\200\201\346\201\266\346\211\213", nullptr));
        label_9->setText(QCoreApplication::translate("DeepAnalyzeDialog", "\346\237\261\347\212\266\345\233\276 \344\270\200\351\200\211\343\200\201\344\272\214\351\200\211\343\200\201\344\270\211\351\200\211\343\200\201\345\205\266\344\273\226", nullptr));
        label_6->setText(QCoreApplication::translate("DeepAnalyzeDialog", "\345\220\273\345\220\210\345\272\246", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_2), QCoreApplication::translate("DeepAnalyzeDialog", "Page 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DeepAnalyzeDialog: public Ui_DeepAnalyzeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEEPANALYZEDIALOG_H
