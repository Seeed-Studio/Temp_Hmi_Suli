/*
* Digital Temperature and Humidity (regular and pro) Sensor
*/

#ifndef __TEMP_HMD_H__
#define __TEMP_HMD_H__

#include "Suli.h"

#define MAXTIMINGS 85

enum dht_ver_t
{
    DHT11,  //regular version
    DHT22,  //pro version
    DHT21
};

typedef enum {
    CELCIUS   =0 ,
    FARENHEIT =1,
} eScale;

void dht_init(PIN_T pin, uint8 dht_version); 
uint8 dht_measure();
float dht_read_temp(eScale scale);
float dht_read_hmd(); 


#endif
