
#include "Charts.h"



// Deze functie doet niks ?????
std::unique_ptr<QChart> ChartsManager::createChart(QLineSeries* series, const QString& title)
{
    auto chart = std::make_unique<QChart>();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle(title);
    return chart;
}

std::unique_ptr<QChartView> createChartView(QChart* chart)
{
    auto chartView = std::make_unique<QChartView>(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    return chartView;
}



