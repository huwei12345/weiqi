#include "choosestepdialog.h"
#include "ui_choosestepdialog.h"
#include <QDebug>
ChooseStepDialog::ChooseStepDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseStepDialog)
{
    ui->setupUi(this);
}

ChooseStepDialog::~ChooseStepDialog()
{
    delete ui;
}

void ChooseStepDialog::ChoosePieceNow(Piece piece)
{
    auto iter = std::find(pieceList.begin(), pieceList.end(), piece);
    if (iter == pieceList.end()) {
        pieceList.push_back(piece);
    }
    else {
        pieceList.erase(iter);
    }
    str = serialList();
    if (str.size() != 0) {
        ui->textEdit->setText(str);
    }
    else {
        ui->textEdit->clear();
    }
}



QString ChooseStepDialog::serialList() {
    str.clear();
    for (auto r : pieceList) {
        qDebug() << showPiece(r);
        str += r.toStringcolor() + "  ";
    }
    return str;
}

void ChooseStepDialog::clear()
{
    pieceList.clear();
    str.clear();
    ui->textEdit->setText("");
}

void ChooseStepDialog::closeEvent(QCloseEvent *event)
{
    qDebug() << "close";
    clear();
    emit closed();
    QDialog::closeEvent(event);
}

void ChooseStepDialog::on_buttonBox_accepted()
{
    qDebug() << "accept";
    clear();
    emit closed();
}


void ChooseStepDialog::on_buttonBox_rejected()
{
    qDebug() << "reject";
    clear();
    emit closed();
}


void ChooseStepDialog::on_pushButton_clicked()
{
    emit dingshiListshow(str);
}

