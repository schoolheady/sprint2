#ifndef Database_connect_H
#define Database_connect_H
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void TCP_INIT();
void Database_init();
void WIFI_INIT();
extern int uur;
extern int min;
extern int sec;
extern bool database_connection;


#endif
