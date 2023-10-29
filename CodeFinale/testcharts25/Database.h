#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QTime>
#include <QSqlDatabase>
#include <vector>
#include <QSqlError>

// Database class handles all database related operations
class Database
{
public:
    // Connects to the database with the given name
    void connect(const std::string& dbName);

    // Checks if the database connection is open
    bool isOpen();

    // Fetches data from the database and stores it in the provided vectors
    void fetchData(std::vector<float>& Array, std::vector<float>& array2, std::vector<float>& array3, QVector<QTime>& timeArray);

    // Closes the database connection
    void close();

private:
    QSqlDatabase db; // Database object
};

#endif // DATABASE_H
