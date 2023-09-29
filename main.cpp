#include "mainwindow.h"

#include <QtCharts>

#include <QApplication>
#include <QVBoxLayout>
#include <QSqlDatabase>
#include <QWidget>
#include "Database.h"
#include "charts.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Vectors to store temperature and humidity data
    std::vector<int> Array;
    std::vector<float> array2;
    std::vector<float> array3;
    std::vector<int> timeArray;

    // Setup database connection
    Database db;
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

    // Create QLineSeries objects for the temperature and humidity data
    auto series1 = std::make_unique<QLineSeries>();
    auto series2 = std::make_unique<QLineSeries>();
    auto series3 = std::make_unique<QLineSeries>();

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
    series2->setName("Humm");
    series3->setName("Druk");

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






//Poging 1
/*
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("weerstationschool.mysql.database.azure.com");
    db.setDatabaseName("test12");
    db.setUserName("Ahmad");
    db.setPassword("Projectweerstation2023");

    if (!db.open()) {
        qDebug() << "Error : " << db.lastError().text();
        //return -1;
    }


    std::vector<int> temperatureData = fetchTemperatureData(db);
    std::vector<float> humidityData = fetchHumidityData(db);

    db.close();

    QVBoxLayout *layout = createLayout(temperatureData, humidityData);



    QWidget window;
    window.setLayout(layout);
    window.resize(400, 600);
    window.show();

    return a.exec();
}
*/



// twee grafieken
/*
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Vectors to store temperature and humidity data
    std::vector<int> Array;
    std::vector<float> array2;

    // Setup database connection
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("weerstationschool.mysql.database.azure.com");
    db.setDatabaseName("test12");
    db.setUserName("Ahmad");
    db.setPassword("Projectweerstation2023");

    if (db.open()) // Check if the database is open
    {
        QSqlQuery query;
        query.exec("SELECT sensorTemp, sensorVocht FROM sensors"); // Fetch temperature and humidity data

        // Store the fetched data in vectors
        while (query.next()) {
            Array.push_back(query.value(0).toInt());
            array2.push_back(query.value(1).toFloat());
        }
    }
    else
    {
        qDebug() << "Error : " << db.lastError().text();
    }
    db.close();

    // Create QLineSeries objects for the temperature and humidity data
    auto series1 = std::make_unique<QLineSeries>();
    auto series2 = std::make_unique<QLineSeries>();

    // Add data to the series
    for (size_t i = 0; i < Array.size(); ++i) {
        series1->append(i, Array[i]);
        series2->append(i, array2[i]);
    }

    // Create QChart objects for the temperature and humidity data
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

    // Create QChartView objects for the charts
    auto chartView1 = std::make_unique<QChartView>(chart1.get());
    chartView1->setRenderHint(QPainter::Antialiasing);

    auto chartView2 = std::make_unique<QChartView>(chart2.get());
    chartView2->setRenderHint(QPainter::Antialiasing);

    // Create a QVBoxLayout object and add the chart views to it
    QVBoxLayout layout;
    layout.addWidget(chartView1.get());
    layout.addWidget(chartView2.get());

    // Create a QWidget object, set its layout, resize it, and show it
    QWidget window;
    window.setLayout(&layout);
    window.resize(400, 600);
    window.show();

    return a.exec();
}
*/

// een grafiek twee lijnen
/*
int Array[6];

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("weerstationschool.mysql.database.azure.com");
    db.setDatabaseName("test12");
    db.setUserName("Ahmad");
    db.setPassword("Projectweerstation2023");
    //bool ok =

    db.open();
    if(!db.isOpen()) {
        qDebug() << "Database is not open!";
        qDebug() << db.lastError().text();
    }
    int Counter = 0;
    if (db.open())
    {
        qDebug() << "Opened!";
        //db.close();
        QSqlQuery query;
        query.exec("SELECT sensor1 FROM sensors"); // replace with your column and table name

        while (query.next()) {
            int columnValue = query.value(0).toInt(); // read the column value Int
            Array[Counter] = columnValue;
            qDebug() << Array[Counter]; // print the column value
            Counter++;
        }
    }
    else
    {
        qDebug() << "Error : " << db.lastError().text();

    }
    db.close();




// Een grafiek twee lijnen

    QLineSeries *series1 = new QLineSeries();
    QLineSeries *series2 = new QLineSeries();
    series1->append(0, Array[0]);
    series1->append(1,  Array[1]);
    series1->append(2,  Array[2]);
    // add more points to the series...
    series2->append(0, 1);
    series2->append(1,  2);
    series2->append(2,  3);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series1);
    chart->addSeries(series2);
    chart->createDefaultAxes();
    chart->setTitle("Temperatuur");

    // Set axis titles
    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText("Tijd");
    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Temperatuur");
    //QValueAxis *axisX2 = new QValueAxis;
    //axisX->setTitleText("Tijd");
    QValueAxis *axisY2 = new QValueAxis;
    axisY->setTitleText("luchtvochtigheid");

    // Add and attach axes
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    //series1->attachAxis(axisX);
    series1->attachAxis(axisY);
    //series2->attachAxis(axisX2);
    series2->attachAxis(axisY2);


    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);


    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(800, 600);
    window.show();



    return app.exec();
}
*/
