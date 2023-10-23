#include <QtCharts>
#include <QTime>
#include <QVector>
#include <QApplication>
#include <QVBoxLayout>
#include <QSqlDatabase>
#include <QWidget>
#include "Database.h"
#include "charts.h"
#include "chartfunctions.h"


// Declare and initialize vectors to store data
std::vector<int> Array;
std::vector<float> array2;
std::vector<float> array3;
QVector<QTime> timeArray;

// Create a Database object
Database db;


// Create unique pointers to QLineSeries objects to store series data for the chart
std::unique_ptr<QLineSeries> series1 = std::make_unique<QLineSeries>();
std::unique_ptr<QLineSeries> series2 = std::make_unique<QLineSeries>();
std::unique_ptr<QLineSeries> series3 = std::make_unique<QLineSeries>();



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Connect to the database and fetch data
    databaseConnection();

    // Add fetched data to the series
    addDataToSeries();

    // Create a QChart object
    auto chart = std::make_unique<QChart>();

    // Add series to the chart
    chart->addSeries(series1.get());
    chart->addSeries(series2.get());
    chart->addSeries(series3.get());

    // Set the title of the chart
    chart->setTitle("Weerstation");

    // Create and set axes for the char
    createAndSetAxes(chart.get());

    // Set names for the series
    series1->setName("Temp");
    series2->setName("Druk");
    series3->setName("Vocht");


    // Create a QChartView object
    auto chartView = createChartView(chart.get());


    // Add the chart view to the layout
    QVBoxLayout layout;
    layout.addWidget(chartView.get());


    // Print fetched data to the console
    for (int i = 0; i < timeArray.size(); ++i) {
        qDebug() << "Time: " << timeArray[i].toString("hh:mm") << " Temp: " << Array[i] << " Humidity: " << array2[i] << " Pressure: " << array3[i];
    }

    QWidget window;
    window.setLayout(&layout); // Set the layout for the window
    window.resize(1200, 900);
    window.show();  // Show the window

    return a.exec();
}
