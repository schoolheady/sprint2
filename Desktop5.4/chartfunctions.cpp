#include "chartfunctions.h"
//Define the name of th edatabse
#define NameDatabase "test"

// Function to connect to the database and fetch data
void databaseConnection() {
    // Connect to the database
    db.connect(NameDatabase);

    if (db.isOpen()) { // Check if the database is open
        qDebug() << "Database connection : ok";
        db.fetchData(Array, array2, array3, timeArray);// Fetch data from the database
    } else {
        qDebug() << "Error: Unable to connect to the database.";  // Print error message if unable to connect to the database
    }

    db.close(); // Close the database connection
}

// Function to add fetched data to the series
void addDataToSeries() {
    qreal elapsedTime = 0;

    for (size_t i = 0; i < Array.size(); ++i) { // Loop through the fetched data
        qreal currentHour = timeArray[i].hour() + timeArray[i].minute() / 60.0;

        if (currentHour < elapsedTime) {
            elapsedTime += 24;
        } else {
            elapsedTime = currentHour;
        }
        if (Array[i] != -1) { // Add data to the series if it is not -1(NULL)
            series1->append(elapsedTime, Array[i]);
            qDebug() << "Added to series1 - Time: " << timeArray[i].toString("hh:mm") << " Temp: " << Array[i];
        }
        if (array2[i] != -1) {
            series2->append(elapsedTime, array2[i]);
            qDebug() << "Added to series2 - Time: " << timeArray[i].toString("hh:mm") << " Humidity: " << array2[i];
        }
        if (array3[i] != -1) {
            series3->append(elapsedTime, array3[i]);
            qDebug() << "Added to series3 - Time: " << timeArray[i].toString("hh:mm") << " Pressure: " << array3[i];
        }
    }
}

// Function to create and set axes for the chart
void createAndSetAxes(QChart* chart) {
    QValueAxis *axisX = new QValueAxis; // Create a new QValueAxis object for the x-axis
    QValueAxis *axisY1 = new QValueAxis; // Create a new QValueAxis object for the y-axis of series1
    QValueAxis *axisY2 = new QValueAxis; // Create a new QValueAxis object for the y-axis of series2
    QValueAxis *axisY3 = new QValueAxis; // Create a new QValueAxis object for the y-axis of series3

    axisX->setRange(1, 24); // Set the range of the x-axis

    axisY1->setTickCount(10); // Set the tick count of the y-axis of series1
    axisY2->setTickCount(10); // Set the tick count of the y-axis of series2
    axisY3->setTickCount(10); // Set the tick count of the y-axis of series3

    axisX->setTickCount(13);// Set the tick count of the x-axis
    axisX->setLabelFormat("%d"); // Set the label format of the x-axis

    QList<QAbstractSeries*> seriesList = chart->series();
    for (int i = 0; i < seriesList.size(); ++i) {
        chart->setAxisX(axisX, seriesList.at(i));
        chart->setAxisY(i == 0 ? axisY1 : (i == 1 ? axisY2 : axisY3), seriesList.at(i));
    }

    // setting the titles
    axisX->setTitleText("Time (hours)");
    axisY1->setTitleText("Temperature in °C");
    axisY2->setTitleText("Humidity in %");
    axisY3->setTitleText("Pressure in Hectopascal");
}
