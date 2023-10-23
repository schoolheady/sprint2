#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/counter.h>
#include <zephyr/drivers/uart.h>
#include <time.h>
#include <string.h>

#define RTC_NODE DT_NODELABEL(rtc) 
// also add that when a new time is added the ticks need to be reset to 0


// Adjust to your specific configuration
// Set the initial time to 12:00:00 (12 o'clock)
//use ntptime in current time to get the exact time precise

time_t time_in_seconds=12.9999 * 3600;

void main(void)
{
    const struct device *rtc_dev = DEVICE_DT_GET(RTC_NODE);

    if (!rtc_dev) {
        printk("RTC device not found\n");
        return;
    }

    printk("RTC device found\n");

    int ret = counter_start(rtc_dev);
    if (ret < 0) {
        printk("Failed to start RTC: %d\n", ret);
        return;
    }

    while (1) {
        uint32_t rtc_ticks;
        ret = counter_get_value(rtc_dev, &rtc_ticks);
time_t current_time = (time_in_seconds)+rtc_ticks; // 12 hours in seconds
        if (ret == 0) {
            // Convert ticks to seconds
		
        struct tm *tm_info = localtime(&current_time);

        // Print the time in HH:MM:SS format
        printk("Time: %02d:%02d:%02d\n", tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec);

          
        } else {
            printk("Failed to get RTC counter value: %d\n", ret);
            return;
        }
        k_sleep(K_SECONDS(1));
    }
}
