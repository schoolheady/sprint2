#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/eeprom.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/__assert.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/eeprom.h>
#include "BME280.h"
#include "Database_connect.h"
#include "rtc.h"
#include <stdio.h>
#include <math.h>

#define NODE_EP1    DT_NODELABEL(eeprom1)
#define EEPROM_SIZE 8192 // Size of EEPROMa 24LC64 in bytes



bool check_eeprom_write = false;
int ret;
int index = 0;
int temp = 0;
int pres = 0;
int hum = 0;
int seconde = 0;
int readtime = 0;

int testarr[4];
const struct device *const dev = DEVICE_DT_GET(NODE_EP1);

float IntToFloat(int num1, int num2)
{
	int Value;
	int Length = 0;
	int tempNum = num2;
	while (tempNum != 0) {
		tempNum /= 10;
		Length++;
	}
	Value = num1 + (float)num2 / pow(10, Length);

	return Value;
}

void write_eeprom()
{                     // becomes true when database connection has been made
	int addr = 0; // Start address
	while (1) {
        
        	if (database_connection == 1) {
			break;
		}
        check_eeprom_write = true;
    
printk("%d",check_eeprom_write);
		temp = temp_val;
		pres = press_val;
		hum = hum_val;
        seconde=count;
		printk("temp: %d \n press:%d\n hum:%d\nseconds: %d\n\n", temp_val, press_val,
		       hum_val, seconde);

		for (int i = 0; i < 4; i++) {

			testarr[0] = temp;
			testarr[1] = hum;
			testarr[2] = pres;
			testarr[3] = seconde;

			int ret = eeprom_write(dev, addr, &testarr[i], sizeof(int));
            k_sleep(K_MSEC(100)); // if there is no delay it will fail to write

			if (ret) {
				printk("Failed to write eeprom at address %d (%d)\n", addr, ret);
			} 
				printk("Address written: %d, Value: %d\n", addr, testarr[i]);
			

			// Move to the next EEPROM address for the next value
			addr += sizeof(int);
		}
	
        k_sleep(K_SECONDS(60)); // delay of 3 minutes before sending data to eeprom
	}
    check_eeprom_write = false;
  
    
}

// check if eeprom is not empty;
// send data from eeprom to database
// modifies the variable that enters to the value stored in the eeprom
int address = 0;
int send_eepromval(int *temp, int *hum, int *press)
{
	int values[4] = {*temp, *hum, *press, readtime};
	int null[4] = {0, 0, 0, 0};
	for (int i = 0; i < 4; i++) {
		int read_value;
		ret = eeprom_read(dev, address, (int *)&read_value, sizeof(int));
		eeprom_write(dev, address, &null[i], sizeof(int));
		values[i] = read_value;
		k_sleep(K_MSEC(10));
		address += sizeof(int);
	}

	for (int i = 0; i < 4; i++) {
		printk("Value %d: %d\n", i, values[i]);
	}
	*temp = values[0];
	*hum = values[1];
	*press = values[2];
	readtime = values[3];

	return address;
}

// checks if the eeprom is empty, if not empty return false and keep using the eeprom
// the send data to the database when connected to the internet.
bool eeprom_empty()
{
	int read_value;
	int eeprom_val;

	for (uint16_t addr = 0; addr < EEPROM_SIZE; addr += sizeof(int)) {

		ret = eeprom_read(dev, address, (int *)&read_value, sizeof(int));

		eeprom_val = +read_value;
	}
    
	
	if (eeprom_val == 0) {
		return true;
        printk("empty\n\n");
	} else {
        printk("not empty\n\n");
		return false;
	}
}
