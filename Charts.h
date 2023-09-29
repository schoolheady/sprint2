#ifndef CHARTS_H
#define CHARTS_H

#include <QChartView>
#include <QLineSeries>
#include <memory>

std::unique_ptr<QChart> createChart(QLineSeries* series, const QString& title);
std::unique_ptr<QChartView> createChartView(QChart* chart);

#endif // CHARTS_H



//Poging 1
/*
#ifndef CHART_H
#define CHART_H

#include <QChartView>
#include <QVBoxLayout>

QVBoxLayout* createLayout(std::vector<int> &temperatureData,
                          std::vector<float> &humidityData);

#endif // CHART_H
*/
