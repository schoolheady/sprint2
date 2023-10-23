#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QTime>
#include <QSqlDatabase>
#include <vector>
#include <QSqlError>


class Database
{
public:
    void connect();
    bool isOpen();
    void fetchData(std::vector<int>& Array, std::vector<float>& array2, std::vector<float>& array3, QVector<QTime>& timeArray);
    void close();


private:
    QSqlDatabase db;
};

#endif // DATABASE_H
