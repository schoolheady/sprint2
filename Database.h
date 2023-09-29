#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <vector>

class Database
{
public:
    void connect();
    bool isOpen();
    void fetchData(std::vector<int>& Array, std::vector<float>& array2, std::vector<float>& array3, std::vector<int>& timeArray);
    void close();


private:
    QSqlDatabase db;
};

#endif // DATABASE_H




//Poging 1
/*
#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <vector>

std::vector<int> fetchTemperatureData(QSqlDatabase &db);
std::vector<float> fetchHumidityData(QSqlDatabase &db);

#endif // DATABASE_H
*/
