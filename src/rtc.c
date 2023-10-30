#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/counter.h>
#include <zephyr/drivers/uart.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "rtc.h"
#include "offline_storage.h"
#define RTC_NODE DT_NODELABEL(rtc) 
// also add that when a new time is added the ticks need to be reset to 0

// Adjust to your specific configuration
// Set the initial time to 12:00:00 (12 o'clock)
//use ntptime in current time to get the exact time precise
int store=0;
    static int last_uur = 0;
    static int last_min = 0;
    static int last_sec = 0;
     int count = 0;

     struct tm *tm_info;
     time_t current_time;
void run_rtc(int uur, int min, int sec)
{
    //printk("uur: %d\n",uur);
    //printk("sec nieuw: %d\n",sec);
    last_uur=last_uur;
    last_min=last_min;
    last_sec=last_sec;
    time_t time_in_seconds = (uur * 3600) + (min * 60) + sec;

    const struct device *rtc_dev = DEVICE_DT_GET(RTC_NODE);

    if (!rtc_dev) {
        printk("RTC device not found\n");
        return;
    }

  //  printk("RTC device found\n");

    uint32_t rtc_ticks;
    int ret = counter_get_value(rtc_dev, &rtc_ticks);
  

    // Check if uur, min, and sec have changed or are all zeros
    if ((uur == 0 && min == 0 && sec == 0) ||last_sec-sec != 0 ) {
        // Reset the count and store the original rtc_ticks value'
       // printk("reset");
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

    
  current_time = (time_in_seconds) + count;
    if (ret == 0) {
        // Convert ticks to seconds
        tm_info = localtime(&current_time);

        // Print the time in HH:MM:SS format


    } else {
        printk("Failed to get RTC counter value: %d\n", ret);
        return;
    }


}
void rtcTimeconv(int rtcValue, int *prtcuur,int *prtcmin,int *prtcsec)
{
    int temp = 0;
    *prtcuur = rtcValue / 3600;
    temp = *prtcuur * 3600;
    //printf("Uur in sec:%d\n", temp);
    rtcValue -= temp;
    *prtcmin = rtcValue / 60;
    temp = *prtcmin * 60;
    //printf("Min in sec:%d\n", temp);
    rtcValue -= temp;
    *prtcsec = rtcValue;
}
char time_string[10]; 
char* getTimeString()
{
  int rtcuur=0;
  int rtcminuut=0;
  int rtcseconde=0;

  int uur2;
  int minuut2;
  int seconde2;
  
 if(eeprom_empty()!= true)
{
    uur2=tm_info->tm_hour;
  minuut2=tm_info->tm_min;
   seconde2=tm_info->tm_sec;
  

    printk("uur:%d minuut:%d seconde:%d\n",uur2,minuut2,seconde2);
    rtcTimeconv(readtime, &rtcuur,&rtcminuut,&rtcseconde);
    
    uur2+=rtcuur;
    minuut2+=rtcminuut;
    seconde2+=rtcseconde;

     sprintf(time_string, "%02d:%02d:%02d", uur2, minuut2, seconde2);
}
    else
    {
    sprintf(time_string, "%02d:%02d:%02d", tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec);
    }
   
   
    return time_string;




















}