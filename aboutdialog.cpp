#include "aboutdialog.h"
#include "ui_aboutdialog.h"

#include <QIcon>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("关于"));
    QIcon windowIcon(QPixmap(":/images/appIcon.jpg")); // 假设你的图标文件位于资源文件中或者项目目录下
    setWindowIcon(windowIcon);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_buttonBox_accepted()
{

}

