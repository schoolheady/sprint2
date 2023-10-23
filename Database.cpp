
#include "Database.h"


void Database::connect()
{
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


/*
void Database::fetchData(std::vector<int>& ArrayTemp, std::vector<float>& array2, std::vector<float>& array3, QVector<QTime>& timeArray)
{
    QSqlQuery query;

    QString queryString = "SELECT Tijd2, SensorTemp, SensorDruk, SensorVocht "
                          "FROM testqt "
                          "WHERE Tijd2 >= '01:00:00' "
                          "AND id = (SELECT MAX(id) FROM testqt WHERE Tijd2 >= '01:00:00')";

    QSqlQuery mainQuery;

    if (mainQuery.exec(queryString)) {
        while (mainQuery.next()) {
            QTime timeValue = QTime::fromString(mainQuery.value(0).toString(), "hh:mm:ss");
            timeArray.push_back(timeValue);
            ArrayTemp.push_back(mainQuery.value(1).toInt());
            array2.push_back(mainQuery.value(2).toFloat());
            array3.push_back(mainQuery.value(3).toFloat());
        }
    } else {
        qDebug() << "Error:" << mainQuery.lastError().text();
    }
    qDebug() << "de eerste array " << timeArray[0];
}
*/





//leest alleen de hoogste id
/*
void Database::fetchData(std::vector<int>& ArrayTemp, std::vector<float>& array2, std::vector<float>& array3, QVector<QTime>& timeArray)
{
    QSqlQuery query;
    QString queryString = "SELECT Tijd2, SensorTemp, SensorDruk, SensorVocht "
                          "FROM testqt "
                          "WHERE Tijd2 >= '01:00:00' "  // Alleen gegevens na 01:00:00
                          "AND Tijd2 >= NOW() - INTERVAL 24 HOUR "  // Binnen de laatste 24 uur
                          "AND id = (SELECT MAX(id) FROM testqt WHERE Tijd2 >= '01:00:00') "
                          "ORDER BY Tijd2 ASC";  // Sorteer op Tijd2 in oplopende volgorde

    if (query.exec(queryString)) {
        while (query.next()) {
            QTime timeValue = QTime::fromString(query.value(0).toString(), "hh:mm:ss");
            timeArray.push_back(timeValue);
            ArrayTemp.push_back(query.value(1).toInt());
            array2.push_back(query.value(2).toFloat());
            array3.push_back(query.value(3).toFloat());
        }
    } else {
        qDebug() << "Error:" << query.lastError().text();
    }
    qDebug() << "de eerste array " << timeArray[0];
}
*/


/*
void Database::fetchData(std::vector<int>& ArrayTemp, std::vector<float>& array2, std::vector<float>& array3, QVector<QTime>& timeArray)
{
    QSqlQuery query;
    QString queryString = "SELECT Tijd2, SensorTemp, SensorDruk, SensorVocht FROM testqt "
                          "WHERE Tijd2 >= '01:00:00' "  // Alleen gegevens na 01:00:00
                          "AND Tijd2 >= NOW() - INTERVAL 24 HOUR "  // Binnen de laatste 24 uur
                          "ORDER BY id DESC "  // Sorteer op de hoogste 'id' waarden eerst
                          "LIMIT 50";  // Beperk het aantal rijen tot 50

    if (query.exec(queryString)) {
        while (query.next()) {
            QTime timeValue = QTime::fromString(query.value(0).toString(), "hh:mm:ss");
            timeArray.push_back(timeValue);
            ArrayTemp.push_back(query.value(1).toInt());
            array2.push_back(query.value(2).toFloat());
            array3.push_back(query.value(3).toFloat());
        }
    } else {
        qDebug() << "Error:" << query.lastError().text();
    }
    qDebug() << "de eerste array " << timeArray[0];
}
*/



/*
void Database::fetchData(std::vector<int>& ArrayTemp, std::vector<float>& array2, std::vector<float>& array3, QVector<QTime>& timeArray)
{
    QSqlQuery query;
    QString queryString = "SELECT Tijd2, SensorTemp, SensorDruk, SensorVocht FROM testqt "
                          "WHERE Tijd2 >= NOW() - INTERVAL 24 HOUR "
                          "ORDER BY id DESC "  // Sorteer op de hoogste 'id' waarden eerst
                          "LIMIT 50";  // Beperk het aantal rijen tot 50

    if (query.exec(queryString)) {
        while (query.next()) {
            QTime timeValue = QTime::fromString(query.value(0).toString(), "hh:mm:ss");
            timeArray.push_back(timeValue);
            ArrayTemp.push_back(query.value(1).toInt());
            array2.push_back(query.value(2).toFloat());
            array3.push_back(query.value(3).toFloat());
        }
    } else {
        qDebug() << "Error:" << query.lastError().text();
    }
    qDebug() << "de eerste array " << timeArray[0];
}
*/



void Database::fetchData(std::vector<int>& ArrayTemp, std::vector<float>& array2, std::vector<float>& array3, QVector<QTime>& timeArray)
{
    QSqlQuery query;
    QString queryString = "SELECT Tijd2, SensorTemp, SensorDruk, SensorVocht FROM testqt "
                          "WHERE Tijd2 >= NOW() - INTERVAL 24 HOUR "
                          "ORDER BY Tijd2 ASC";

    if (query.exec(queryString)) {
        while (query.next()) {
            QTime timeValue = QTime::fromString(query.value(0).toString(), "hh:mm:ss");
            timeArray.push_back(timeValue);
            ArrayTemp.push_back(query.value(1).toInt());
            array2.push_back(query.value(2).toFloat());
            array3.push_back(query.value(3).toFloat());
        }
    } else {
        qDebug() << "Error:" << query.lastError().text();
    }
    qDebug() << "de eerste array " << timeArray[0];
}




/*
void Database::fetchData(std::vector<int>& ArrayTemp, std::vector<float>& array2, std::vector<float>& array3, QVector<QTime>& timeArray)
{
    QSqlQuery query;
   // QString queryString = "SELECT Tijd2, SensorTemp, SensorDruk, SensorVocht FROM testqt ORDER BY id ASC LIMIT 10";
    QString queryString = "SELECT Tijd2, SensorTemp, SensorDruk, SensorVocht FROM testqt";
    if (query.exec(queryString)) {
        while (query.next()) {
            QTime timeValue = QTime::fromString(query.value(0).toString(), "hh:mm:ss");
            timeArray.push_back(timeValue);
            ArrayTemp.push_back(query.value(1).toInt());
            array2.push_back(query.value(2).toFloat());
            array3.push_back(query.value(3).toFloat());
        }
    } else {
        qDebug() << "Error:" << query.lastError().text();
    }
    qDebug() << "de eerste array "<<timeArray[0];
}
*/

void Database::close()
{
    db.close();
}
