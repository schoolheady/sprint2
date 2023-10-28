#ifndef BME280_H_
#define BME280_H_

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>

#ifdef __cplusplus
extern "C" {
#endif

int BME280();
extern int temp_val;
extern int press_val;
extern int hum_val;
extern char *time_sensor;


#ifdef __cplusplus
}
#endif

#endif /* BME280_H_ */
