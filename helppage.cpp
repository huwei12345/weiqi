#include "helppage.h"
#include "ui_helppage.h"

#include <QIcon>

HelpPage::HelpPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpPage)
{
    ui->setupUi(this);
    setWindowTitle(tr("帮助"));
    QIcon windowIcon(QPixmap(":/images/appIcon.jpg")); // 假设你的图标文件位于资源文件中或者项目目录下
    setWindowIcon(windowIcon);
}

HelpPage::~HelpPage()
{
    delete ui;
}
