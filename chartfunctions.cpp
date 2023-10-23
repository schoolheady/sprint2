#include "chartfunctions.h"
#include <QDebug>

void databaseConnection() {
    // Setup database connection
    db.connect();

    if (db.isOpen()) // Check if the database is open
    {
        qDebug() << "Database connection : ok";
        db.fetchData(Array, array2, array3, timeArray);
    }
    else
    {
        qDebug() << "Error: Unable to connect to the database.";
    }
    db.close();
}


void AddDataToSeries() {
    qreal elapsedTime = 0; // Variable to keep track of the total elapsed time

    // Add data to the series
    for (size_t i = 0; i < Array.size(); ++i) {
        qreal currentHour = timeArray[i].hour() + timeArray[i].minute() / 60.0; // Hours + Minutes/60

        // Check if current hour is less than elapsed time
        if (currentHour < elapsedTime) {
            elapsedTime += 24; // Add 24 to elapsed time
        } else {
            elapsedTime = currentHour;
        }

        if (Array[i] != -1) // Assuming -1 represents "null"
        {
            series1->append(elapsedTime, Array[i]);
            qDebug() << "Added to series1 - Time: " << timeArray[i].toString("hh:mm") << " Temp: " << Array[i];
        }
        if (array2[i] != -1) // Assuming -1 represents "null"
        {
            series2->append(elapsedTime, array2[i]);
            qDebug() << "Added to series2 - Time: " << timeArray[i].toString("hh:mm") << " Humidity: " << array2[i];
        }
        if (array3[i] != -1) // Assuming -1 represents "null"
        {
            series3->append(elapsedTime, array3[i]);
            qDebug() << "Added to series3 - Time: " << timeArray[i].toString("hh:mm") << " Pressure: " << array3[i];
        }
    }
}


// begint bij begin
/*
void AddDataToSeries() {
    // Add data to the series
    for (size_t i = 0; i < Array.size(); ++i) {
        if (Array[i] != NULL) // Assuming -1 represents "null"
        {
            qreal x = timeArray[i].hour() + timeArray[i].minute() / 60.0; // Hours + Minutes/60
            series1->append(x, Array[i]);
            //qDebug() << "Added to series1 - Time: " << timeArray[i].toString("hh:mm") << " Temp: " << Array[i];
        }
        if (array2[i] != NULL) // Assuming -1 represents "null"
        {
            qreal x = timeArray[i].hour() + timeArray[i].minute() / 60.0; // Hours + Minutes/60
            series2->append(x, array2[i]);
            //qDebug() << "Added to series2 - Time: " << timeArray[i].toString("hh:mm") << " Humidity: " << array2[i];
        }
        if (array3[i] != NULL) // Assuming -1 represents "null"
        {
            qreal x = timeArray[i].hour() + timeArray[i].minute() / 60.0; // Hours + Minutes/60
            series3->append(x, array3[i]);
            //qDebug() << "Added to series3 - Time: " << timeArray[i].toString("hh:mm") << " Pressure: " << array3[i];
        }
    }
}
*/




void createAndSetAxes(QChart* chart) {
    // Create axes
    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY1 = new QValueAxis;
    QValueAxis *axisY2 = new QValueAxis;
    QValueAxis *axisY3 = new QValueAxis;

    // Set the range for the x-axis in hours
    axisX->setRange(1, 24); // Set fixed range from 1 to 24

    axisY1->setTickCount(10);
    axisY2->setTickCount(10);
    axisY3->setTickCount(10);

    axisX->setTickCount(13); // 12 intervals of 2 hours, plus 1 for the starting point


    // Define a custom label format for the x-axis to show hours
    axisX->setLabelFormat("%d"); // Format to show hours

    // Add the axes to the chart
    QList<QAbstractSeries*> seriesList = chart->series();
    for (int i = 0; i < seriesList.size(); ++i) {
        chart->setAxisX(axisX, seriesList.at(i));
        chart->setAxisY(i == 0 ? axisY1 : (i == 1 ? axisY2 : axisY3), seriesList.at(i));
    }

    // Set the title of the x-axis
    axisX->setTitleText("Time (hours)");

    // Set the titles of the y-axes
    axisY1->setTitleText("Temperature in °C");
        axisY2->setTitleText("Humidity in %");
    axisY3->setTitleText("Pressure in Hectopascal");
}



