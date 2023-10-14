#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/eeprom.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/__assert.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/eeprom.h>
#include "BME280.h"

#define NODE_EP1 DT_NODELABEL(eeprom1)
#define EEPROM_SIZE 8192 // Size of EEPROM 24LC64 in bytes

int ret;
int index = 0;
const struct device *const dev = DEVICE_DT_GET(NODE_EP1);

void write_eeprom() {
    for (uint16_t addr = 0; addr < EEPROM_SIZE; addr += sizeof(uint16_t)) {
        BME280();

        uint16_t val1 = temp_val;
        uint16_t val2 = temp_decimal;
        uint16_t val3 = press_val;
        uint16_t val4 = press_decimal;
        uint16_t val5 = hum_val;
        uint16_t val6 = hum_decimal;

        uint16_t testarr[6] = { val1, val2, val3, val4, val5, val6 };

        // Calculate index based on address in bytes
        printk("%d\n", testarr[index]);

        ret = eeprom_write(dev, addr, &testarr[index], sizeof(uint16_t));
        printk("Address: %d, Value: %d\n", addr, testarr[index]);

        if (ret) {
            printk("Failed to write eeprom at address %d (%d)\n", addr, ret);
        } else {
            printk("Success to write eeprom at address %d (%d)\n", addr, ret);
        }

        index = (index + 1) % 6;

        k_sleep(K_MSEC(6000));
    }
}

void read_eeprom() {
    uint16_t read_value;

    printk("Reading from EEPROM:\n");

    for (uint16_t addr = 0; addr < EEPROM_SIZE; addr += sizeof(uint16_t)) {
        // Read data from EEPROM
        ret = eeprom_read(dev, addr, (uint8_t*)&read_value, sizeof(uint16_t));
        if (ret) {
            printk("Failed to read from EEPROM at address %d (%d)\n", addr, ret);
            return;
        }

        printk("Success reading back eeprom at address %d  (%d)\n", addr, (uint16_t)read_value);

        k_sleep(K_MSEC(6000));
    }
}

void main(void) {
    // Call the appropriate function based on your application logic
    write_eeprom();
    //read_eeprom();
}
