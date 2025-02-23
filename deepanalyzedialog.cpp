#include "deepanalyzedialog.h"

#include "ui_deepanalyzedialog.h"


DeepAnalyzeDialog::DeepAnalyzeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeepAnalyzeDialog)
{
    ui->setupUi(this);
}

void DeepAnalyzeDialog::showAnalyzeResult(QList<MoveAnalysis> analysis)
{
    // 创建 QBarSet，分别表示 妙手、恶手、俗手
    QBarSet *set1 = new QBarSet("妙手");
    QBarSet *set2 = new QBarSet("恶手");
    QBarSet *set3 = new QBarSet("俗手");

    // 填充每种类型的手数（这里假设数据：妙手 20，恶手 15，俗手 10）
    *set1 << 10;
    *set2 << 15;
    *set3 << 10;

    // 创建 QBarSeries，并将 QBarSet 添加到系列中
    QBarSeries *series = new QBarSeries();
    series->append(set1);
    series->append(set2);
    series->append(set3);

    // 创建图表
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("棋局妙手、恶手、俗手统计");

    // 创建 X 轴（类别轴），分别为 妙手、恶手、俗手
    QCategoryAxis *axisX = new QCategoryAxis();
    axisX->append("妙手", 0);
    axisX->append("恶手", 1);
    axisX->append("俗手", 2);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // 创建 Y 轴（值轴），表示每种手的数量
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 30);  // 设置 Y 轴范围
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // 创建图表视图
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->page->layout()->addWidget(chartView);
    chartView->show();
}


DeepAnalyzeDialog::~DeepAnalyzeDialog()
{
    delete ui;
}
