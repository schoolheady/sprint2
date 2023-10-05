//#include "mainwindow.h"

#include <QtCharts>

#include <QApplication>
#include <QVBoxLayout>
#include <QSqlDatabase>
#include <QWidget>
#include "Database.h"
#include "charts.h"

// Vectors to store temperature and humidity data
std::vector<int> Array;
std::vector<float> array2;
std::vector<float> array3;
std::vector<int> timeArray;

Database db;

// Create QLineSeries objects for the temperature and humidity data
auto series1 = std::make_unique<QLineSeries>();
auto series2 = std::make_unique<QLineSeries>();
auto series3 = std::make_unique<QLineSeries>();

void databaseConnection()
{
    // Setup database connection
    db.connect();

    if (db.isOpen()) // Check if the database is open
    {
        db.fetchData(Array, array2,array3, timeArray);
    }
    else
    {
        qDebug() << "Error : ";
    }
    db.close();
}

void AddDataToSeries(){
    // Add data to the series
    for (size_t i = 0; i < Array.size(); ++i) {
        if(Array[i]!= NULL)
        {
            series1->append(timeArray[i], Array[i]);
        }
        if(array2[i]!= NULL)
        {
            series2->append(timeArray[i], array2[i]);
        }
        if(array3[i]!= NULL)
        {
            series3->append(timeArray[i], array3[i]);
        }
    }
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    databaseConnection();

    AddDataToSeries();


    // Create a QChart object for the data
    auto chart = std::make_unique<QChart>();

    // Add the series to the chart
    chart->addSeries(series1.get());
    chart->addSeries(series2.get());
    chart->addSeries(series3.get());

    // Create axes
    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY1 = new QValueAxis;
    QValueAxis *axisY2 = new QValueAxis;
    QValueAxis *axisY3 = new QValueAxis;

    // Set the ranges of the axes
    axisX->setRange(*std::min_element(timeArray.begin(), timeArray.end()), *std::max_element(timeArray.begin(), timeArray.end()));
    //axisX->setRange(0, 23);
    axisY1->setRange(0, *std::max_element(Array.begin(), Array.end()));
    axisY2->setRange(0, *std::max_element(array2.begin(), array2.end()));
    axisY3->setRange(0, *std::max_element(array3.begin(), array3.end()));

    // Add the axes to the chart
    chart->setAxisX(axisX, series1.get());
    chart->setAxisY(axisY1, series1.get());
    chart->setAxisY(axisY2, series2.get());
    chart->setAxisY(axisY3, series3.get());


    // Set the titles of the series
    series1->setName("Temp");
    series2->setName("Druk");
    series3->setName("Vocht");

    // Set the title of the x-axis
    axisX->setTitleText("Tijd in uren");

    // Set the title of the y-axes
    axisY1->setTitleText("Temperatuur in °C");
    axisY2->setTitleText("Vochtigheid in %");
    axisY3->setTitleText("Druk in Hectopascal");

    // Create a QChartView object for the chart
    auto chartView = createChartView(chart.get());

    // Create a QVBoxLayout object and add the chart view to it
    QVBoxLayout layout;
    layout.addWidget(chartView.get());

    // Create a QWidget object, set its layout, resize it, and show it
    QWidget window;
    window.setLayout(&layout);
    window.resize(1200, 900);
    window.show();

    return a.exec();
}
