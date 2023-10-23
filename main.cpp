
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

//comment
std::vector<int> Array;
std::vector<float> array2;
std::vector<float> array3;
QVector<QTime> timeArray;

std::vector<int> Array8;
std::vector<float> array9;
std::vector<float> array10;
QVector<QTime> timeArray2;


Database db;
std::unique_ptr<QLineSeries> series1 = std::make_unique<QLineSeries>();
std::unique_ptr<QLineSeries> series2 = std::make_unique<QLineSeries>();
std::unique_ptr<QLineSeries> series3 = std::make_unique<QLineSeries>();


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    databaseConnection();

    db.close();
    AddDataToSeries();

    // Create a QChart object for the data
    auto chart = std::make_unique<QChart>();

    // Add the series to the chart
    chart->addSeries(series1.get());
    chart->addSeries(series2.get());
    chart->addSeries(series3.get());

    chart->setTitle("Weerstation");

    // Call the method to create and set the axes
    createAndSetAxes(chart.get());

    // Set the titles of the series
    series1->setName("Temp");
    series2->setName("Druk");
    series3->setName("Vocht");

    // Create a QChartView object for the chart
    auto chartView = createChartView(chart.get());

    // Create a QVBoxLayout object and add the chart view to it
    QVBoxLayout layout;
    layout.addWidget(chartView.get());

    for (int i = 0; i < timeArray.size(); ++i) {
        qDebug() << "Time: " << timeArray[i].toString("hh:mm") << " Temp: " << Array[i] << " Humidity: " << array2[i] << " Pressure: " << array3[i];
    }


    // Create a QWidget object, set its layout, resize it, and show it
    QWidget window;
    window.setLayout(&layout);
    window.resize(1200, 900);
    window.show();


    // a second venster
    /*

    QWidget window2;
    window2.setWindowTitle("Tweede Leeg Venster");

    // Maak een QLineSeries en voeg gegevens toe
    QLineSeries *series8 = new QLineSeries;
    series8->append(0, 6);
    series8->append(2, 4);
    series8->append(3, 8);
    series8->append(7, 4);
    series8->append(10, 5);
    *series8 << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

    // Maak een QChart en voeg het lijndiagram toe
    QChart *chart8 = new QChart;
    chart8->legend()->hide();
    chart8->addSeries(series8);
    chart8->createDefaultAxes();
    chart8->setTitle("Simple Line Chart");

    // Maak een QChartView en voeg het aan het venster toe
    QChartView *chartView8 = new QChartView(chart8);
    chartView8->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout layout2;
    layout2.addWidget(chartView8);

    window2.setLayout(&layout2);
    window2.show();
*/

    return a.exec();
}
