/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 * Copyright (c) 2021 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include "BME280.h"
#include "rtc.h"
#include "string.h"
/*
 * Get a device structure from a devicetree node with compatible
 * "bosch,bme280". (If there are multiple, just pick one.)
 */
int temp_val = 0;
int press_val = 0;
int hum_val = 0;
int store_temp = 0;
char *time_sensor = 0;
static const struct device *get_bme280_device(void)
{
	const struct device *const dev = DEVICE_DT_GET_ANY(bosch_bme280);

	if (dev == NULL) {
		/* No such node, or the node does not have status "okay". */
		printk("\nError: no device found.\n");
		return NULL;
	}

	if (!device_is_ready(dev)) {
		printk("\n\n\n Restart device or check the \"%s\"  pin connections\n\n\n",
		       dev->name);
		return NULL;
	}
else{
	//printk("Found device \"%s\", getting sensor data\n", dev->name);
}
	return dev;
}

int DoublleIntToInt(int a, int b)
{
	int result, temp1 = 0;
	temp1 = a * 100;
	result = temp1 + b;
	return result;
}
void cijfersachter(int num, int *pa)
{
	while (num >= 100) {
		num = num / 10;
	}

	*pa = DoublleIntToInt(*pa, num);
}

void BME280()
{
	const struct device *dev = get_bme280_device();
	if (dev == NULL) {
		return;
	}
	struct sensor_value temp, press, humidity;

	sensor_sample_fetch(dev);
	sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temp);
	sensor_channel_get(dev, SENSOR_CHAN_PRESS, &press);
	sensor_channel_get(dev, SENSOR_CHAN_HUMIDITY, &humidity);

	press_val = press.val1;
	hum_val = humidity.val1;
	temp_val = temp.val1;

	store_temp = temp.val2;
	cijfersachter(store_temp, &temp_val);

	store_temp = humidity.val2;
	cijfersachter(store_temp, &hum_val);

	store_temp = press.val2;
	cijfersachter(store_temp, &press_val);
	time_sensor = getTimeString();

		
}
