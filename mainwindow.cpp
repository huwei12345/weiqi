#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    goWidget = new GoBoardWidget(this);
    QObject::connect(this, &MainWindow::keyEventCaptured,
                         goWidget, &GoBoardWidget::onKeyPressEvent);
    //goWidget->show();
    QLayout* layout = ui->panWidget->layout();
    layout->addWidget(goWidget);
    goWidget->setUITree(ui->pieceTree);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_LoadBtn_clicked()
{
    // 弹出文件选择对话框
    /*
            tr("Open Image"),
            "",
            tr("Images (*.png *.jpg *.jpeg *.bmp *.gif);;All Files (*)"));
    */
    QString fileName = QFileDialog::getOpenFileName(this,
                        tr("Open File"),
                        "",
                        tr("All Files (*);;Text Files (*.txt)"));
    //D:/easybcd.zip
    if (!fileName.isEmpty()) {
        qDebug() << "Selected file:" << fileName;
    } else {
        qDebug() << "No file selected.";
        return;
    }
    goWidget->readSGF(fileName.toStdString());
}


void MainWindow::on_storeBtn_clicked()
{
    // 打开文件对话框，选择保存的文件位置和文件名
    QString fileName = QFileDialog::getSaveFileName(
        this, "保存棋谱", "", "SGF Files (*.sgf);;All Files (*)");

    if (fileName.isEmpty()) {
        // 如果没有选择文件名，则返回
        return;
    }

    // 确保文件扩展名是 .sgf
    if (!fileName.endsWith(".sgf", Qt::CaseInsensitive)) {
        fileName += ".sgf";
    }
    goWidget->saveSGF(fileName.toStdString());
}


void MainWindow::on_WinBtn_clicked()
{
    goWidget->calculateScore();
}

void MainWindow::on_clearBtn_clicked()
{
    goWidget->clear();
}


void MainWindow::on_judgeBtn_clicked(bool checked)
{
    qDebug() << (checked ? "open Judge" : "close Judge");
    auto p = goWidget->calculateScore2(checked);
    qDebug() << "black " << p.first << " white " << p.second;
}


void MainWindow::on_toolButton_clicked()
{
    goWidget->clearJudge();
}


void MainWindow::on_pieceTree_itemClicked(QTreeWidgetItem *item, int column)
{
    TreeData data = item->data(0, 1).value<TreeData>();
    qDebug() << data.node->moveNum;
    goWidget->jumptoPiece(data.node);
}


