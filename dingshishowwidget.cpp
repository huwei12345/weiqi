#include "dingshishowwidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QScrollArea>

DingShiShowWidget::DingShiShowWidget(QWidget *parent)
    : QWidget{parent}
{
    layout = new QHBoxLayout();
    layout->setSpacing(10);  // 设置卡片之间的间隔
    layout->setContentsMargins(10, 10, 10, 10);  // 设置容器的内边距
    mainWidget = new QWidget(this);
    mainWidget->setLayout(layout);
    // 创建一个QScrollArea来包含卡片容器
    QScrollArea *scrollArea = new QScrollArea(this);

    scrollArea->setWidget(mainWidget);
    scrollArea->setWidgetResizable(true);  // 使得内容区域可自适应

    // 设置滚动条的方向为水平
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    mainLayout = new QHBoxLayout();
    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);
}

void DingShiShowWidget::showDS()
{
    for (size_t i = 0; i < dsList.size(); i++) {
        dsList[i]->setParent(this);
        //dsList[i]->resize(1000 / dsList.size(), 1000 / dsList.size());
        //dsList[i]->setWindSize(1000 / dsList.size());
        QWidget* w = new QWidget(this);
        QLayout* lay = new QVBoxLayout(this);
        lay->addWidget(dsList[i]);
        QLabel* lab = new QLabel(this);
        lab->setText(QString::number(i + 1));
        lay->addWidget(lab);
        lab->setAlignment(Qt::AlignHCenter);
        QFont font;
        font.setBold(true);
        font.setPointSize(10);
        lab->setFont(font);
        w->setLayout(lay);
        layout->addWidget(w);
    }
    resize(1280, 360);
    show();
}

void DingShiShowWidget::addItem(DingShiShow *ds)
{
    if (ds == nullptr) {
        return;
    }
    dsList.push_back(ds);
}
