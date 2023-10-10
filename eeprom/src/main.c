/*
 * Copyright (c) 2023 JSC
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/eeprom.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/__assert.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/eeprom.h>

#define NODE_EP1 DT_NODELABEL(eeprom1)
#define EEPROM_SIZE 8192 // Size of EEPROM 24LC64 in bytes

int main(void)
{
	const struct device *const dev = DEVICE_DT_GET(NODE_EP1);
	int ret;
	uint16_t counter = 0;
	uint8_t eeprom_data[sizeof(uint16_t)];


	// Write and read EEPROM until it is full.
	for (uint16_t addr = 0; addr < EEPROM_SIZE ; addr += sizeof(uint16_t)) {
		printk("Address: %d, Value: %d\n", addr, counter);

		// write data to eeprom device
		ret = eeprom_write(dev, addr, &counter, sizeof(counter));
		if (ret) {
			printk("Failed to write eeprom at address %d (%d)\n", addr, ret);
			continue;
		}
		else{
			printk("Succes to write eeprom at address %d (%d)\n", addr, ret);
			//continue;
		}


        // a delay to ti give time to write data to eeprom device
		//k_sleep(K_MSEC(10)); 


		// read data from eeprom device
		k_sleep(K_MSEC(100));
		ret = eeprom_read(dev, addr, eeprom_data, sizeof(eeprom_data));
		if (ret) {
			printk("Failed to read eeprom at address %d (%d)\n", addr, ret);
			continue;
		}

		// check
		if (counter != (uint16_t)(*eeprom_data)){
			printk("Failed to read back eeprom at address %d (%d) (%d)\n", addr, counter, (uint16_t)(*eeprom_data));
		} else {
			printk("Success reading back eeprom at address %d (%d) (%d)\n", addr, counter, (uint16_t)(*eeprom_data));
		}

		counter++;
		if (counter == 254)// cannot write more than 254
		{
			counter = 1;
		}
		
	}
	return 0;
}
