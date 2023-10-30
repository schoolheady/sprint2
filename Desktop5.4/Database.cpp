#include "Database.h" // Include custom Database header file

// Function to connect to the database
void Database::connect(const std::string& dbName)
{
    db = QSqlDatabase::addDatabase("QMYSQL"); // Add a MySQL database
    db.setHostName("127.0.0.1"); // Set the host name to localhost
    db.setDatabaseName(QString::fromStdString(dbName)); // Set the database name
    db.setUserName("root"); // Set the username
    db.setPassword(""); // Set the password
    db.open(); // Open the database connection
}

// Function to check if the database is open
bool Database::isOpen()
{
    return db.isOpen(); // Return true if the database is open, false otherwise
}

// Function to fetch data from the database
void Database::fetchData(std::vector<float>& ArrayTemp, std::vector<float>& array2, std::vector<float>& array3, QVector<QTime>& timeArray)
{
    QSqlQuery queryMaxDate;
    queryMaxDate.exec("SELECT MAX(DataIN) FROM testqt");
    queryMaxDate.next();
    QString maxDate = queryMaxDate.value(0).toString();

    QSqlQuery query; // Create a QSqlQuery object
    QString queryString = "SELECT Tijd2, SensorTemp, SensorDruk, SensorVocht FROM testqt "
                          "WHERE DataIN BETWEEN TIMESTAMP('" + maxDate + "') - INTERVAL 24 HOUR AND TIMESTAMP('" + maxDate + "') "
                                                                                          "ORDER BY Tijd2 ASC"; // Define the SQL query string

    if (query.exec(queryString)) { // Execute the SQL query
        while (query.next()) { // Loop through the query results
            QTime timeValue = QTime::fromString(query.value(0).toString(), "hh:mm:ss"); // Get the time value from the query result
            timeArray.push_back(timeValue); // Add the time value to the timeArray vector
            ArrayTemp.push_back(query.value(1).toFloat()); // Add the temperature value to the ArrayTemp vector
            array2.push_back(query.value(2).toFloat()); // Add the pressure value to the array2 vector
            array3.push_back(query.value(3).toFloat()); // Add the humidity value to the array3 vector
        }
    } else {
        qDebug() << "Error:" << query.lastError().text(); // Print error message if unable to execute the SQL query
    }

    qDebug() << "de eerste array " << timeArray[0]; // Print the first element of timeArray vector
}



// Function to close the database connection
void Database::close()
{
    db.close(); // Close the database connection
}
