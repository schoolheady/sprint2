#ifndef CHARTS_H
#define CHARTS_H

#include <QPainter>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <memory>
#include <QTime>

class ChartsManager{
public:
    std::unique_ptr<QChart> createChart(QLineSeries* series, const QString& title);

};

std::unique_ptr<QChartView> createChartView(QChart* chart);

#endif // CHARTS_H
