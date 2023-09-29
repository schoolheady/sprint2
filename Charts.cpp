#include <QChartView>
#include <QPainter>
#include <QLineSeries>
#include <QChart>
#include "Charts.h"


// Deze functie doet niks ?????
std::unique_ptr<QChart> createChart(QLineSeries* series, const QString& title)
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




/*
#include <QtCharts/QLineSeries>
#include "Charts.h"

QVBoxLayout* createLayout(std::vector<int> &temperatureData, std::vector<float> &humidityData) {
    auto series1 = std::make_unique<QLineSeries>();
    auto series2 = std::make_unique<QLineSeries>();

    for (size_t i = 0; i < temperatureData.size(); ++i) {
        series1->append(i, temperatureData[i]);
        series2->append(i, humidityData[i]);
    }

    auto chart1 = std::make_unique<QChart>();
    chart1->legend()->hide();
    chart1->addSeries(series1.get());
    chart1->createDefaultAxes();
    chart1->setTitle("Grafiek 1");

    auto chart2 = std::make_unique<QChart>();
    chart2->legend()->hide();
    chart2->addSeries(series2.get());
    chart2->createDefaultAxes();
    chart2->setTitle("Grafiek 2");

    auto chartView1 = std::make_unique<QChartView>(chart1.get());
    chartView1->setRenderHint(QPainter::Antialiasing);

    auto chartView2 = std::make_unique<QChartView>(chart2.get());
    chartView2->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(chartView1.get());
    layout->addWidget(chartView2.get());

    return layout;
}
*/
