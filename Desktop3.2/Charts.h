#ifndef CHARTS_H
#define CHARTS_H

#include <QPainter>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <memory>
#include <QTime>

// ChartsManager class handles all chart related operations
class ChartsManager{
public:
    std::unique_ptr<QChart> createChart(QLineSeries* series, const QString& title); // Function to create a chart with the given series and title
};

std::unique_ptr<QChartView> createChartView(QChart* chart); // Function to create a chart view with the given chart

#endif // CHARTS_H
