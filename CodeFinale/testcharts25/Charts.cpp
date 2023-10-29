#include "Charts.h"

// Function to create a chart with the given series and title
std::unique_ptr<QChart> ChartsManager::createChart(QLineSeries* series, const QString& title)
{
    auto chart = std::make_unique<QChart>(); // Create a QChart object
    chart->legend()->hide(); // Hide the legend of the chart
    chart->addSeries(series); // Add the given series to the chart
    chart->createDefaultAxes(); // Create default axes for the chart
    chart->setTitle(title); // Set the title of the chart

    return chart; // Return the created chart
}

// Function to create a chart view with the given chart
std::unique_ptr<QChartView> createChartView(QChart* chart)
{
    auto chartView = std::make_unique<QChartView>(chart); // Create a QChartView object with the given chart

    chartView->setRenderHint(QPainter::Antialiasing); // Set the render hint to antialiasing for smoother lines

    return chartView; // Return the created chart view
}
