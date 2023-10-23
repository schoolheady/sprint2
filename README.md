# Desktop

## Description
This project is a Qt-based application for visualizing weather station data using Qt Charts. It connects to a MySQL database and fetches temperature, humidity, and pressure data to display on line charts.


## Features
- Fetch and display temperature, humidity,pressure and time data from a MySQL database.
- Create line charts to visualize the data over time.
- Set up axes to display time and value information.

## Files

- `Database.h` and `Database.cpp`: These files define the `Database` class, which is responsible for connecting to the database, checking if the connection is open, fetching data from the database, and closing the connection.

- `chartfunctions.h` and `chartfunctions.cpp`: These files define several functions for handling chart data, including connecting to the database, adding data to the chart series, and creating and setting axes for the chart.

- `Charts.h` and `Charts.cpp`: These files define the `ChartsManager` class and a function for creating a chart view. The `ChartsManager` class has a method for creating a chart with a given series and title.

- `main.cpp`: This is the entry point of the application. It creates an instance of `QApplication`, connects to the database, fetches data, adds it to the chart series, creates and sets axes for the chart, sets series names, creates a chart view, adds it to a layout, and shows it in a window.

  
## Installation
1. Ensure you have the Qt development environment installed.
2. Esure that you have the MySQL drivers installed
3. Clone or download the repository.
4. Open the project in Qt Creator.
5. Build and run the application.


## Usage
- Upon running the application, it will connect to the specified MySQL database.
- Data will be fetched and displayed on the line charts.



