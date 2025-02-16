#include "judgecalcdialog.h"
#include "ui_judgecalcdialog.h"

JudgeCalcDialog::JudgeCalcDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JudgeCalcDialog)
{
    ui->setupUi(this);
}

JudgeCalcDialog::JudgeCalcDialog(JudgeInfo *info, QWidget *parent) : JudgeCalcDialog(parent)
{
    QString a = info->whiteLead > 0 ? QString("白") + QString::number(info->whiteLead)
                                                       : QString("黑") + QString::number(0.0 - info->whiteLead);
    ui->labelA->setText(a);
    ui->labelB->setText(QString::number(info->whiteground));
    ui->labelC->setText(QString::number(info->blackground));
}

JudgeCalcDialog::~JudgeCalcDialog()
{
    delete ui;
}
