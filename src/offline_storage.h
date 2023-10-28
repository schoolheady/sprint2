#ifndef OFFLINE_STORAGE_H
#define OFFLINE_STORAGE_H

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/eeprom.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/__assert.h>
#include <zephyr/devicetree.h>


int send_eepromval(int* temp, int* hum, int* press, int* sec);
void write_eeprom(bool status);
bool eeprom_empty();

extern int readtime;

#endif