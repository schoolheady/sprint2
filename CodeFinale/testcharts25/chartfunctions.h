#ifndef CHARTFUNCTIONS_H
#define CHARTFUNCTIONS_H

#include <QtCharts>
#include <QTime>
#include <QVector>
#include <QValueAxis>
#include <QDebug>
#include "Database.h"

// Global variables for storing fetched data and database object
extern std::vector<float> Array;
extern std::vector<float> array2;
extern std::vector<float> array3;
extern QVector<QTime> timeArray;
extern Database db;

// Unique pointers to QLineSeries objects for storing series data for the chart
extern std::unique_ptr<QLineSeries> series1;
extern std::unique_ptr<QLineSeries> series2;
extern std::unique_ptr<QLineSeries> series3;

// Connects to the database and fetches data
void databaseConnection();

// Adds fetched data to the series
void addDataToSeries();

// Creates and sets axes for the chart
void createAndSetAxes(QChart* chart);

#endif // CHARTFUNCTIONS_H
