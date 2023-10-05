#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include "Database.h"

void Database::connect()
{
    /*
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("weerstationschool.mysql.database.azure.com");
    db.setDatabaseName("test12");
    db.setUserName("Ahmad");
    db.setPassword("Projectweerstation2023");
    db.open();
*/

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("test");
    db.setUserName("root");
    db.setPassword("");
    db.open();
}

bool Database::isOpen()
{
    return db.isOpen();
}

void Database::fetchData(std::vector<int>& ArrayTemp, std::vector<float>& array2, std::vector<float>& array3, std::vector<int>& timeArray)
{
    QSqlQuery query;
    //query.exec("SELECT HOUR(Tijd), sensorTemp, sensorVocht, Sensor3 FROM sensors"); // Fetch hour, temperature and humidity data
    query.exec("SELECT Tijd, SensorTemp, SensorDruk, SensorVocht FROM testqt");
    // Store the fetched data in vectors
    while (query.next()) {
        timeArray.push_back(query.value(0).toInt());
        ArrayTemp.push_back(query.value(1).toInt());
        array2.push_back(query.value(2).toFloat());
        array3.push_back(query.value(3).toFloat());
    }
}



void Database::close()
{
    db.close();
}
