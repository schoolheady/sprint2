#ifndef CHARTS_H
#define CHARTS_H

#include <QChartView>
#include <QLineSeries>
#include <memory>

class ChartsManager{
public:
    std::unique_ptr<QChart> createChart(QLineSeries* series, const QString& title);

};

std::unique_ptr<QChartView> createChartView(QChart* chart);

#endif // CHARTS_H
