# BME280 Sensor Data Collection

This project contains code to collect data from a BME280 sensor using Zephyr RTOS. The BME280 sensor measures temperature, pressure, and humidity.

## Files

The project consists of two files:

1. `BME280.c`: This file contains the implementation of the function `BME280()`, which fetches and stores the sensor data in global variables. It also includes a function `get_bme280_device()` to get the device structure from a devicetree node with compatible "bosch,bme280".

2. `BME280.h`: This is the header file for `BME280.c`. It contains the declaration of the `BME280()` function and the external variables used to store the sensor data.

## Usage

To use this code, include `BME280.h` in your main program file. Call the function `BME280()` to fetch the sensor data. The fetched data is stored in the following global variables:

- `temp_val` and `temp_decimal`: Store the integral and decimal parts of the temperature value respectively.
- `press_val` and `press_decimal`: Store the integral and decimal parts of the pressure value respectively.
- `hum_val` and `hum_decimal`: Store the integral and decimal parts of the humidity value respectively.

Please note that you need to have Zephyr RTOS set up in your development environment to use this code.

## Dependencies

This project depends on Zephyr RTOS and its libraries. Make sure you have it installed and properly configured in your development environment.

## License

This project is licensed under Apache-2.0.
