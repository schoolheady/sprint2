/*
 * Copyright (c) 2022 Libre Solar Technologies GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "BME280.h"

/* change this to any other UART peripheral if desired */
#define UART_DEVICE_NODE DT_NODELABEL(usart1) // 8 && 3
#define SIZE             200

static int received_data_len = 0;
static uint8_t received_data[1024];



static const struct device *const uart_dev = DEVICE_DT_GET(UART_DEVICE_NODE);

// temperature and humidity values will be stored in here
uint8_t temperature = 0;
uint8_t temperature_decimal = 0;
uint8_t pressure = 0;
uint8_t pressure_decimal = 0;
uint8_t humidity = 0;
uint8_t humidity_decimal = 0;

// Convert temperature and humidity to strings
char temperatureStr[20];
char humidityStr[20];
char content_lengthSTR[20];
int content_length = 0;

char string[SIZE];
char string2[SIZE];

// converts int to string function
char *itoa(int num, char *buffer, int base)
{
	int current = 0;
	if (num == 0) {
		buffer[current++] = '0';
		buffer[current] = '\0';
		return buffer;
	}
	int num_digits = 0;
	if (num < 0) {
		if (base == 10) {
			num_digits++;
			buffer[current] = '-';
			current++;
			num *= -1;
		} else {
			return NULL;
		}
	}
	num_digits += (int)floor(log(num) / log(base)) + 1;
	while (current < num_digits) {
		int base_val = (int)pow(base, num_digits - 1 - current);
		int num_val = num / base_val;
		char value = num_val + '0';
		buffer[current] = value;
		current++;
		num -= base_val * num_val;
	}
	buffer[current] = '\0';
	return buffer;
}

// sends the command via uart
void send_data(const char *at_command,uint8_t *tx_buf)
{
	
	// Sends the data from the tx_buffer using uart_poll_out
	snprintf(tx_buf, SIZE, "%s\r\n", at_command);
	for (size_t i = 0; i < strlen(tx_buf); i++) {
		uart_poll_out(uart_dev, tx_buf[i]);
	}
}
// stores the command in a array
void AT_SEND(const char *data)
{
	 uint8_t tx_buf[SIZE];
	size_t len = strlen(data);
	if (len >= SIZE) {
		// Handle error: Input data is too large for the buffer
		return;
	}

	send_data(data,tx_buf);
	for (size_t i = 0; i < SIZE; i++) {
		tx_buf[i] = 0;
	}
}

typedef enum {
	ESTABLLISH_CONNECTION,
	ESTABLISH_TCP_IP,
	SEND_DATABASE,
	NO_CONNECTION
} Database;
int status = ESTABLLISH_CONNECTION;

static void uart_cb(const struct device *x, void *user_data)
{
	static uint8_t rx_buf[SIZE];

	uart_irq_update(x);

	if (uart_irq_rx_ready(x)) {
		int data_length = uart_fifo_read(x, rx_buf, sizeof(rx_buf));

		// Copy the received data to the buffer
		if (received_data_len + data_length < sizeof(received_data)) {
			memcpy(&received_data[received_data_len], rx_buf, data_length);
			received_data_len += data_length;
		}
	}
}

bool check_connection()
{
	bool connection = false;
	if (received_data_len > 0) {
		printk("Received data: %s\n", received_data);
	}
	if (strstr(received_data, "CONNECTED") != NULL || strstr(received_data, "CONNECTED") != NULL ) {
		connection = true;
	}

	return connection;
}

void return_time()
{

const char *prefix = "current time: ";
    char *time_ptr = strstr(received_data, prefix);

    if (time_ptr) {
        time_ptr += strlen(prefix); // Move the pointer past the prefix
        char time[9]; // Assuming the time format is hh:mm:ss
        strncpy(time, time_ptr, 8);
        time[8] = '\0'; // Null-terminate the extracted time
        printf("Extracted time: %s\n", time);
    } else {
        printf("Time not found in the text.\n");
    }
	
}
void WIFI_INIT()
{
	k_sleep(K_MSEC(600));
	printk("establishing wifi connection...\n");
	AT_SEND("AT+CWJAP=\"i\",\"bqmi8806\"\r\n"); // insert wifi name && ssid
	k_sleep(K_MSEC(3000));
	if (check_connection() == true) {
		printk("WiFi is connected.\n");
		status = ESTABLISH_TCP_IP;
	}

	else {
		printk("Wifi connection failed\n");
		status = NO_CONNECTION;
	}
	k_sleep(K_MSEC(2000));
	// add if wifi is connected status == ESTABLISH_TCP_IP
}
void TCP_INIT()
{
	printk("Conecting to database...\n");
	k_sleep(K_MSEC(300));
	AT_SEND("AT+CIPSTART=\"TCP\",\"192.168.61.157\",80\r\n"); // insert wifi name && ssid;//
	k_sleep(K_MSEC(3000));
	if (check_connection() == true) {
		printk("connected to database.\n");
		status = SEND_DATABASE;
	} else {
		printk("TCP connection failed.\n");

		status = NO_CONNECTION;
	}
	
}

void SEND_INIT()
{

	// converts integer to string
	itoa(temperature, temperatureStr, 10);
	itoa(humidity, humidityStr, 10);
printk("Sending Data: %d.%d, %d.%d, and %d.%d\n", temperature, temperature_decimal, humidity, humidity_decimal, pressure, pressure_decimal);

	// calculate CIPSEND size
	content_length = strlen(humidityStr) + strlen(temperatureStr) + 72;
	itoa(content_length, content_lengthSTR, 10);

	sprintf(string, "AT+CIPSEND=%s\r\n", content_lengthSTR);
	sprintf(string2,
		"GET /file.php?temperature=%s&humidity=%s HTTP/1.1\r\nHost: localhost\r\n\r\n",
		temperatureStr, humidityStr);
	k_sleep(K_MSEC(30));
	AT_SEND(string);
	k_sleep(K_MSEC(300));
	AT_SEND(string2);
	k_sleep(K_MSEC(4000));
check_connection();
return_time();
	status = ESTABLISH_TCP_IP;
}

void offline_init()
{
	printk("offline_init");
	k_sleep(K_MSEC(3000));
	// write sensor values to eeprom


	// after 1 minute check if internet is connected do this when measuring a new value this is when a value becomes high
	// imaginary value goes high in if statement that yet has to be implemented
	status = ESTABLLISH_CONNECTION;
}

void Database_init()
{

	switch (status) {
	case ESTABLLISH_CONNECTION:
		WIFI_INIT();
		break;
	case ESTABLISH_TCP_IP:
		TCP_INIT();
		break;

	case SEND_DATABASE:
		SEND_INIT();
		break;
	case NO_CONNECTION:
		offline_init();
		break;
	default:
		printk("Unknown WiFi status\n");
	}
}

void main(void)
{
	int uart1_data = 3;
	uart_irq_callback_user_data_set(uart_dev, uart_cb, &uart1_data);
	uart_irq_rx_enable(uart_dev);
	while (1) {

		Database_init();
	}
}
