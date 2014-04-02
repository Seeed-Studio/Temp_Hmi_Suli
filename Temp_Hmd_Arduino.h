/*
  Temp_Hmd_Arduino.h
  
  For Arduino Only

  2014 Copyright (c) Seeed Technology Inc.  All right reserved.
  
  Loovee
  2013-4-2

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef __TEMP_HMD_ARDUINO_H__
#define __TEMP_HMD_ARDUINO_H__

#include "Temp_Hmd.h"

class Temp_Hmd{


public:

    Temp_Hmd(int pin, uint8 dht_version)
    {
        dht_init(pin, dht_version);
    }
    
    bool measure()
    {
        return dht_measure();
    }
    
    float temp(eScale scale)
    {
        return dht_read_temp(scale);
    }
    
    float humidity()
    {
        return dht_read_hmd();
    }
    
    
    /*
     * get temperature and humidity
     */
    bool get(float * temp, float * hm, eScale scale)
    {
        
        if(!dht_measure())              // get data
        {
            return 0;
        }
        *temp = dht_read_temp(scale);    // get temperature
        *hm   = dht_read_hmd();
        
        return 1;
    }





};


#endif
