#ifndef CHOOSESTEPDIALOG_H
#define CHOOSESTEPDIALOG_H

#include "piece.h"

#include <QDialog>

namespace Ui {
class ChooseStepDialog;
}

class ChooseStepDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseStepDialog(QWidget *parent = nullptr);
    ~ChooseStepDialog();

    QString serialList();
    void clear();

    void closeEvent(QCloseEvent *event) override;
public slots:
    void ChoosePieceNow(Piece piece);

signals:
    void closed();
    void dingshiListshow(QString str);
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_pushButton_clicked();

private:
    Ui::ChooseStepDialog *ui;
    std::list<Piece> pieceList;
    QString str;
};

#endif // CHOOSESTEPDIALOG_H
