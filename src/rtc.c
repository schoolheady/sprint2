#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/counter.h>
#include <zephyr/drivers/uart.h>
#include <time.h>

#define RTC_NODE DT_NODELABEL(rtc) // Adjust to your specific configuration
// Set the initial time to 12:00:00 (12 o'clock)
//use ntptime in current time to get the exact time precise
int ntptime_in_seconds;
time_t current_time = 12.9999 * 3600; // 12 hours in seconds
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

        if (ret == 0) {
            // Convert ticks to seconds
			current_time=current_time+rtc_ticks;
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
