#ifndef DINGSHISHOWWIDGET_H
#define DINGSHISHOWWIDGET_H

#include "dingshishow.h"

#include <QObject>
#include <QWidget>
class QHBoxLayout;
class DingShiShowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DingShiShowWidget(QWidget *parent = nullptr);
    void showDS();
    void addItem(DingShiShow* ds);
signals:


private:
    std::vector<DingShiShow*> dsList;
    QWidget* mainWidget;
    QHBoxLayout *mainLayout;
    QHBoxLayout *layout;
};

#endif // DINGSHISHOWWIDGET_H
