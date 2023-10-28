#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/eeprom.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/__assert.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/eeprom.h>
#include "BME280.h" 
#include "rtc.h"
#include<stdio.h>
#include<math.h>


#define NODE_EP1 DT_NODELABEL(eeprom1)
#define EEPROM_SIZE 8192 // Size of EEPROMa 24LC64 in bytes

int ret;
int index = 0;
   int temp=0;
   int pres=0;
   int hum= 0;
   int seconde=0;
 
int testarr[4];
const struct device *const dev = DEVICE_DT_GET(NODE_EP1);

float IntToFloat(int num1, int num2){
	int Value;
    int Length = 0;
    int tempNum = num2;
    while(tempNum != 0) {
        tempNum /= 10;
        Length++;
    }
    Value = num1 + (float)num2 / pow(10, Length);

    return Value;
}

int u=0;
int m=0;
int s=1;
void write_eeprom(bool status) { // becomes true when database connection has been made
    int addr = 0;  // Start address
while(status==false){
    for (int i = 0; i < 4; i++) {
        run_rtc(u,m,s);
        seconde=BME280();
        temp = temp_val;
        pres = press_val;
        hum = hum_val;
        
        testarr[0] = temp;
        testarr[1] = pres;
        testarr[2] = hum;
        testarr[3] = seconde;
        printk("temp: %d \n press:%d\n hum:%d\n", temp_val, press_val, hum_val);
        
        // Calculate index based on address in bytes
        printk("%d\n", testarr[i]);

        int ret = eeprom_write(dev, addr, &testarr[i], sizeof(int));
        printk("Address: %d, Value: %d\n", addr, testarr[i]);

        if (ret) {
            printk("Failed to write eeprom at address %d (%d)\n", addr, ret);
        } else {
            printk("Success to write eeprom at address %d (%d)\n", addr, ret);
        }

        // Move to the next EEPROM address for the next value
        addr += sizeof(int);

        k_sleep(K_MSEC(100));
    }
    }
}


// check eeprom is not empty;
// send data from eeprom to database
// modifies the variable that enters to the value stored in the eeprom
int address=0;
int send_eepromval(int* temp, int* hum, int* press, int* sec)
{
    int values[4]={*temp,*hum,*press,*sec};
    int null[4]={0,0,0,0};
for (int i = 0; i < 4; i++) {
    int read_value;
    ret = eeprom_read(dev, address, (int*)&read_value, sizeof(int));
    eeprom_write(dev, address,&null[i], sizeof(int));
    values[i] = read_value;
    k_sleep(K_MSEC(10));
    address += sizeof(int);
}

for (int i = 0; i < 4; i++) {
    printk("Value %d: %d\n", i, values[i]);
}
    *temp = values[0];
    *hum = values[1];
    *press = values[2];
    *sec = values[3];

return address;
}

// checks if the eeprom is empty, if not empty return false and keep using the eeprom 
// the send data to the database when connected to the internet.
bool eeprom_empty()
{

 int read_value;
 int eeprom_val;

    for (uint16_t addr = 0; addr < EEPROM_SIZE; addr += sizeof(int)) 
    {

ret = eeprom_read(dev, address, (int*)&read_value, sizeof(int));

eeprom_val=+read_value;

    }
    
    printk("value: %d",eeprom_val);
if(eeprom_val == 0){
return true;
}
else
{
return false;
}
}

/*void main(void) { 
    
	while(1){
    // Call the appropriate function based on your application logic
    
  //write_eeprom(false);
 send_eepromval(&temp,&hum,&pres,&seconde);
 //printk("temp: %d\n seconde: %d \n",temp,seconde);
  //eeprom_empty();

 
   }
}
*/