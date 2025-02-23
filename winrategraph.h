#ifndef WINRATEGRAPH_H
#define WINRATEGRAPH_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsScene>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QDebug>
class GoBoardWidget;
QT_CHARTS_USE_NAMESPACE

class WinRateGraph : public QChartView {
public:
    WinRateGraph(QChart *chart, GoBoardWidget* widget);
    QLineSeries *series1;  // 目数差的系列
    QLineSeries *series2;  // 胜率的系列
protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
private:
    QGraphicsLineItem *m_verticalLine;
    QGraphicsTextItem *m_textItem;
    QGraphicsScene *m_scene;
    GoBoardWidget* goWidget;
};

#endif // WINRATEGRAPH_H
