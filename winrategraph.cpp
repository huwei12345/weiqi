#include "winrategraph.h"
#include "boardwidget.h"
WinRateGraph::WinRateGraph(QChart *chart, GoBoardWidget *widget)
    : QChartView(chart)
{
    setRenderHint(QPainter::Antialiasing);
    setMouseTracking(true);
    m_verticalLine = new QGraphicsLineItem();
    m_textItem = new QGraphicsTextItem();
    m_scene = chart->scene();
    m_scene->addItem(m_verticalLine);
    m_scene->addItem(m_textItem);
    goWidget = widget;
}

void WinRateGraph::mouseMoveEvent(QMouseEvent *event)
{
    QPointF scenePos = mapToScene(event->pos());
    QRectF plotArea = chart()->plotArea();
    qreal x = scenePos.x();

    // 更新竖线的位置
    if (x >= plotArea.left() && x <= plotArea.right()) {
       m_verticalLine->setLine(x, plotArea.top(), x, plotArea.bottom());
    }
    else {
       m_verticalLine->clearFocus();
    }
    // 将鼠标点击的坐标转换为图表上的坐标
    QPointF chartPos = this->chart()->mapToValue(event->pos());
    // 获取XY坐标
    qreal xx = chartPos.x();
    int xint = qRound(xx);
    qreal yy = chartPos.y();
    int yint = qRound(yy);
    qDebug() << "zzz" << xint << " " << yint << " " << series1->count();
    // 只在图表区域内更新竖线和文本
    if (xint >= 0 && xint < series1->count()) {
       double winRate = series2->at(xint).y();
       double scoreDiff = series1->at(xint).y();
       QString text = QString("第%1手\n胜率: %2%\n目数差: %3")
           .arg(xint)
           .arg(winRate)
           .arg(scoreDiff);
       m_textItem->setPlainText(text);
       m_textItem->setPos(x + 5, plotArea.top() + 20); // 提示文本位置
    }
}

void WinRateGraph::mousePressEvent(QMouseEvent *event)
{
   if (event->button() == Qt::LeftButton) {
       // 将鼠标点击的坐标转换为图表上的坐标
       QPointF chartPos = this->chart()->mapToValue(event->pos());
       // 获取XY坐标
       qreal xx = chartPos.x();
       int xint = qRound(xx);
       qreal yy = chartPos.y();
       int yint = qRound(yy);
       qDebug() << "zzz" << xint << " " << yint << " " << series1->count();

       if (xint >= 0 && xint < series1->count()) {
           // 根据点击的位置跳转到相应的棋局状态
           goWidget->jumptoPiece(xint);
       }
   }
}
