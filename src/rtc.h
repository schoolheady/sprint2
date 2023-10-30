#ifndef RTC_H
#define RTC_H

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/counter.h>
#include <zephyr/drivers/uart.h>
#include <time.h>
#include <string.h>


void run_rtc(int uur, int min, int sec);
char* getTimeString(); 
extern int count;
#endif /* BME280_H_ */
