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

/* change this to any other UART peripheral if desired */
#define UART_DEVICE_NODE DT_NODELABEL(usart1) // 8 && 3
#define SIZE    200

char tx_buf[SIZE];
char rx_buffer[SIZE];

static const struct device *const uart_dev = DEVICE_DT_GET(UART_DEVICE_NODE);
// temperature and humidity values are stored in here
int temperature = 1;
int humidity = 2;
// Convert temperature and humidity to strings
char temperatureStr[20];
char humidityStr[20];
char content_lengthSTR[20];
int content_length = 0;

char string[SIZE];
char string2[SIZE];


//converts int to string
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
void send_data(const char *at_command)
{
	// Send the data from the tx_buffer using uart_poll_out
	snprintf(tx_buf, SIZE, "%s\r\n", at_command);
	for (size_t i = 0; i < strlen(tx_buf); i++) {
		uart_poll_out(uart_dev, tx_buf[i]);
	}
}
//stores the command in a array
void AT_SEND(const char *data)
{
	size_t len = strlen(data);
	if (len >= SIZE) {
		// Handle error: Input data is too large for the buffer
		return;
	}

	send_data(data);
	for (size_t i = 0; i < SIZE; i++) {
		tx_buf[i] = 0;
	}
}

typedef enum {
	ESTABLLISH_CONNECTION,
	ESTABLISH_TCP_IP,
	SEND_DATABASE
} Database;
int status = ESTABLLISH_CONNECTION;

void WIFI_INIT()
{
	k_sleep(K_MSEC(2000));
	printk("wifi init");
	AT_SEND("AT+CWJAP=\"i\",\"bqmi8806\"\r\n"); // insert wifi name && ssid
	k_sleep(K_MSEC(2000));
	// add if wifi is connected status == ESTABLISH_TCP_IP
	status = ESTABLISH_TCP_IP;
}
void TCP_INIT()
{
	k_sleep(K_MSEC(3000));
	AT_SEND("AT+CIPSTART=\"TCP\",\"192.168.243.157\",80\r\n"); // insert wifi name && ssid;//
								  // insert wifi name && ssid
	k_sleep(K_MSEC(3000));

	// add if database is connected status == SEND_DATABASE
	status = SEND_DATABASE;
}

void SEND_INIT()
{

	// converts integer to string
	itoa(temperature, temperatureStr, 10);
	itoa(humidity, humidityStr, 10);


	// calculate CIPSEND size
	content_length = strlen(humidityStr) + strlen(temperatureStr) + 72;
	itoa(content_length, content_lengthSTR, 10);

	sprintf(string, "AT+CIPSEND=%s\r\n", content_lengthSTR);
	sprintf(string2,"GET /file.php?temperature=%s&humidity=%s HTTP/1.1\r\nHost: localhost\r\n\r\n",temperatureStr, humidityStr);
	k_sleep(K_MSEC(3000));
	AT_SEND(string);
	k_sleep(K_MSEC(3000));
	AT_SEND(string2);
	k_sleep(K_MSEC(3000));

	// AT_SEND(string2);
	status = ESTABLISH_TCP_IP;
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

	default:
		printk("Unknown WiFi status\n");
	}
}

int main(void){
while(1)
{

Database_init();

}
	
	}

