/*
 * temp & humi sensor demo code
 *
 * Note:
 * - this is a Suli-compatible Library
 * - You should download Suli for Arduino first
 * - More details, please refer to http://www.seeedstudio.com/wiki/Suli
 */
 
#include <Suli.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#include "Temp_Hmd_Arduino.h"


// choos sensor type

#define DHTTYPE DHT11             // DHT 11 
//#define DHTTYPE DHT22               // DHT 22  (AM2302)
//#define DHTTYPE DHT21             // DHT 21 (AM2301)or


const int pinHmd = A4;


Temp_Hmd thd(pinHmd, DHTTYPE);

void setup()
{
    Serial.begin(115200);
    Serial.println("hello world");
}

void loop()
{
    float temp = 0.0;
    float humi = 0.0;
    
    if(thd.get(&temp, &humi, CELCIUS))          // if get data ok
    {
        Serial.print(temp);
        Serial.print(" oC\t");
        Serial.print(humi);
        Serial.println('%');
    }
    else
    {
        // get error data
        // Serial.println("data err");
    }

    delay(100);
}