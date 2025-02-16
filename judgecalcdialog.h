#ifndef JUDGECALCDIALOG_H
#define JUDGECALCDIALOG_H

#include <QDialog>
#include "piece.h"
namespace Ui {
class JudgeCalcDialog;
}

class JudgeCalcDialog : public QDialog
{
    Q_OBJECT

public:
    explicit JudgeCalcDialog(QWidget *parent = nullptr);
    explicit JudgeCalcDialog(JudgeInfo* info, QWidget *parent = nullptr);
    ~JudgeCalcDialog();

private:
    Ui::JudgeCalcDialog *ui;
};

#endif // JUDGECALCDIALOG_H
