#ifndef CHARTFUNCTIONS_H
#define CHARTFUNCTIONS_H

#include <QtCharts>
#include <QTime>
#include <QVector>
#include <QValueAxis>
#include "Database.h"

extern std::vector<int> Array;
extern std::vector<float> array2;
extern std::vector<float> array3;
extern QVector<QTime> timeArray;
extern Database db;
extern std::unique_ptr<QLineSeries> series1;
extern std::unique_ptr<QLineSeries> series2;
extern std::unique_ptr<QLineSeries> series3;

void databaseConnection();
void AddDataToSeries();
void createAndSetAxes(QChart* chart);

#endif // CHARTFUNCTIONS_H
