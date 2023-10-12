#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/rtc.h>

#define NODE_rtc DT_NODELABEL(rtc)

void main(void) {
    const struct device *rtc_dev = DEVICE_DT_GET(NODE_rtc);

    if (!rtc_dev) {
        printk("Could not find RTC device!\n");
        return;
    }

    printk("RTC initialized\n");

    while (1) {
        struct rtc_time current_time;

        // Get the RTC time
        int ret = rtc_get_time(rtc_dev, &current_time);
        if (ret < 0) {
            printk("Error getting RTC time: %d\n", ret);
            return;
        }

        // Print the current RTC time
        printk("Current RTC time: %04d-%02d-%02d %02d:%02d:%02d\n",
               current_time.tm_year,
               current_time.tm_mon,
               current_time.tm_mday,
               current_time.tm_hour,
               current_time.tm_min,
               current_time.tm_sec);

        k_sleep(K_SECONDS(5));  // Sleep for 5 seconds
    }
}
