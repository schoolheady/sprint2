#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include "BME280.h"
int main(void)
{
    float temp;
    float press;
    float hum;
    while(1)
    {
        BME280(&temp,&press,&hum);
        // send mearsurement
        k_sleep(K_MSEC(60000));
        printk("Temp:",temp,"Press:",press,"Humidity:",hum)
    }
    return 0;
}