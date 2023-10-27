#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/counter.h>
#include <zephyr/drivers/uart.h>
#include <time.h>
#include <string.h>
#include "rtc.h"

#define RTC_NODE DT_NODELABEL(rtc) 
// also add that when a new time is added the ticks need to be reset to 0

// Adjust to your specific configuration
// Set the initial time to 12:00:00 (12 o'clock)
//use ntptime in current time to get the exact time precise
int store=0;
    static int last_uur = 0;
    static int last_min = 0;
    static int last_sec = 0;
    static int count = 0;
void run_rtc(int uur, int min, int sec)
{
    printk("sec: %d\n",last_sec);
    printk("sec nieuw: %d\n",sec);
    last_uur=last_uur;
    last_min=last_min;
    last_sec=last_sec;
    time_t time_in_seconds = (uur * 3600) + (min * 60) + sec;

    const struct device *rtc_dev = DEVICE_DT_GET(RTC_NODE);

    if (!rtc_dev) {
        printk("RTC device not found\n");
        return;
    }

    printk("RTC device found\n");

    uint32_t rtc_ticks;
    int ret = counter_get_value(rtc_dev, &rtc_ticks);
  

    // Check if uur, min, and sec have changed or are all zeros
    if (uur == 0 && min == 0 && sec == 0 ||last_sec-sec != 0 ) {
        // Reset the count and store the original rtc_ticks value'
        printk("reset");
        store=rtc_ticks-1;
        count = 0;
        
    }
    else
    {
       count=store;
        count=rtc_ticks-count;
    }

    last_uur = uur;
    last_min = min;
    last_sec = sec;

    printk("%d\n", count);
  time_t current_time = (time_in_seconds) + count;
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
