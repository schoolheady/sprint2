#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include "BME280.h"
#include "offline_storage.h"
#include "rtc.h"
#include "Database_connect.h"

#define T_SIZE 1024

void K_rtc(void)
{
	while (1) {

		run_rtc(uur, min, sec);
		k_sleep(K_SECONDS(1));
	}
}

void K_Sensor(void)
{
	while (1) {

		BME280();
		k_sleep(K_SECONDS(60*3)); //set to 3 mins

	}
}

void K_check(void)
{
	while (1) {
			printk("test",check_eeprom_write);
		if (check_eeprom_write == true) {
            printk("quick check : %d\n",check_eeprom_write);
			WIFI_INIT();
			k_sleep(K_SECONDS(10));
			TCP_INIT();
		}
	}
}

//K_THREAD_DEFINE(id_check, T_SIZE, K_check, NULL, NULL, NULL, 3, 0, 0);

K_THREAD_DEFINE(id_Sensor, T_SIZE, K_Sensor, NULL, NULL, NULL, 0, 0, 0);

K_THREAD_DEFINE(id_rtc, T_SIZE, K_rtc, NULL, NULL, NULL, -1, K_ESSENTIAL, 0);

int main()
{

	while (1) {

		Database_init();
	}
}

// kthread resume when in eeprom write
