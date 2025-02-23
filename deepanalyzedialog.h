#ifndef DEEPANALYZEDIALOG_H
#define DEEPANALYZEDIALOG_H
#include <QDialog>
#include "kata.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QtCharts/QCategoryAxis>
QT_CHARTS_USE_NAMESPACE

namespace Ui {
class DeepAnalyzeDialog;
}

class DeepAnalyzeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeepAnalyzeDialog(QWidget *parent = nullptr);
    void showAnalyzeResult(QList<MoveAnalysis> analysis);
    ~DeepAnalyzeDialog();

private:
    Ui::DeepAnalyzeDialog *ui;
};

#endif // DEEPANALYZEDIALOG_H
