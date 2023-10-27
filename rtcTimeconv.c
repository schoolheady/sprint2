#include <stdio.h>
#include <stdlib.h>

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
int main()
{
    int rtcuur = 0;
    int rtcmin = 0;
    int rtcsec = 0;
    int rtcValue = 56857;
    rtcTimeconv(rtcValue,&rtcuur,&rtcmin,&rtcsec);
    printf("Uur:%d\n", rtcuur);
    printf("Min:%d\n", rtcmin);
    printf("Sec:%d\n", rtcsec);
}
