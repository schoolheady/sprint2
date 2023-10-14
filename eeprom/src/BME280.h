#ifndef BME280_H_
#define BME280_H_

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>

#ifdef __cplusplus
extern "C" {
#endif

void BME280();
extern int temp_val;
extern int temp_decimal;
extern int press_val;
extern int press_decimal;
extern int hum_val;
extern int hum_decimal;
#ifdef __cplusplus
}
#endif

#endif /* BME280_H_ */
