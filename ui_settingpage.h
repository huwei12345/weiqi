/********************************************************************************
** Form generated from reading UI file 'settingpage.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGPAGE_H
#define UI_SETTINGPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingPage
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QWidget *widget;
    QFormLayout *formLayout;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QComboBox *comboBox_2;
    QLabel *label_3;
    QFontComboBox *fontComboBox;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QWidget *SettingPage)
    {
        if (SettingPage->objectName().isEmpty())
            SettingPage->setObjectName(QString::fromUtf8("SettingPage"));
        SettingPage->resize(524, 237);
        verticalLayout = new QVBoxLayout(SettingPage);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_4 = new QLabel(SettingPage);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setMinimumSize(QSize(0, 30));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_4);

        widget = new QWidget(SettingPage);
        widget->setObjectName(QString::fromUtf8("widget"));
        formLayout = new QFormLayout(widget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        comboBox = new QComboBox(widget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        formLayout->setWidget(0, QFormLayout::FieldRole, comboBox);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        comboBox_2 = new QComboBox(widget);
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        formLayout->setWidget(1, QFormLayout::FieldRole, comboBox_2);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        fontComboBox = new QFontComboBox(widget);
        fontComboBox->setObjectName(QString::fromUtf8("fontComboBox"));

        formLayout->setWidget(2, QFormLayout::FieldRole, fontComboBox);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(SettingPage);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(234, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(widget_2);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout->addWidget(buttonBox);


        verticalLayout->addWidget(widget_2);


        retranslateUi(SettingPage);

        QMetaObject::connectSlotsByName(SettingPage);
    } // setupUi

    void retranslateUi(QWidget *SettingPage)
    {
        SettingPage->setWindowTitle(QCoreApplication::translate("SettingPage", "Form", nullptr));
        label_4->setText(QCoreApplication::translate("SettingPage", "Setting", nullptr));
        label->setText(QCoreApplication::translate("SettingPage", "\344\270\273\351\242\230", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("SettingPage", "\345\216\237\345\247\213", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("SettingPage", "\347\273\217\345\205\270", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("SettingPage", "\351\273\221\347\231\275", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("SettingPage", "\345\212\250\346\274\253", nullptr));

        label_2->setText(QCoreApplication::translate("SettingPage", "\350\257\255\350\250\200", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("SettingPage", "\344\270\255\346\226\207", nullptr));

        label_3->setText(QCoreApplication::translate("SettingPage", "\345\255\227\344\275\223", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingPage: public Ui_SettingPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGPAGE_H
