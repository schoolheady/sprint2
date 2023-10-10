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
#include "Conversion.h"
/*
 * Get a device structure from a devicetree node with compatible
 * "bosch,bme280". (If there are multiple, just pick one.)
 */
static const struct device *get_bme280_device(void)
{
	const struct device *const dev = DEVICE_DT_GET_ANY(bosch_bme280);

	if (dev == NULL) {
		/* No such node, or the node does not have status "okay". */
		printk("\nError: no device found.\n");
		return NULL;
	}

	if (!device_is_ready(dev)) {
		printk("\nError: Device \"%s\" is not ready; "
		       "check the driver initialization logs for errors.\n",
		       dev->name);
		return NULL;
	}

	printk("Found device \"%s\", getting sensor data\n", dev->name);
	return dev;
}

void BME280(float *t,float *p,float *h)
{
	const struct device *dev = get_bme280_device();
	if (dev == NULL) {
		return 0;
	}
	struct sensor_value temp, press, humidity;

	sensor_sample_fetch(dev);
	sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temp);
	sensor_channel_get(dev, SENSOR_CHAN_PRESS, &press);
	sensor_channel_get(dev, SENSOR_CHAN_HUMIDITY, &humidity);
	*t = conversion(temp.val1,temp.val2);
	*p = conversion(press.val1,press.val2);
	*h = conversion(humidity.val1,humidity.val2);
	return 0;
}
