#include "Temp_Hmd.h"

static uint8 _type = DHT22;             //pro
static uint8 firstreading = true;

static uint32 _lastreadtime = 0;
static uint8 _count = 8;
static uint8 data[6];
// static uint8 _last_succ = false;

static IO_T __pin;

void dht_init(PIN_T pin, uint8 dht_version)
{

    _type = dht_version;
    firstreading = true;

    suli_pin_init(&__pin, pin);
    suli_pin_dir(&__pin, HAL_PIN_OUTPUT);
    suli_pin_write(&__pin, HAL_PIN_HIGH);
    _lastreadtime = 0;
}

static float convertCtoF(float c) {
    return c * 9 / 5 + 32;
}

uint8 dht_measure()
{
    uint8 laststate = HAL_PIN_HIGH;
    uint8 counter = 0;
    uint8 j = 0, i;
    unsigned long currenttime;

    // pull the pin high and wait 250 milliseconds
    suli_pin_write(&__pin, HAL_PIN_HIGH);

    suli_delay_ms(250);

    currenttime = millis();
    if (currenttime < _lastreadtime) {
        // ie there was a rollover
        _lastreadtime = 0;
    }
    if (!firstreading && ((currenttime - _lastreadtime) < 2000))
    {
        return true;        // return last correct measurement

    }
    firstreading = false;

    _lastreadtime = millis();

    data[0] = data[1] = data[2] = data[3] = data[4] = 0;

    // now pull it low for ~20 milliseconds

    suli_pin_dir(&__pin, HAL_PIN_OUTPUT);
    suli_pin_write(&__pin, HAL_PIN_LOW);
    suli_delay_ms(20);
    // cli();
    suli_pin_write(&__pin, HAL_PIN_HIGH);
    suli_delay_us(40);

    suli_pin_dir(&__pin, HAL_PIN_INPUT);


    // read in timings
    for ( i=0; i< MAXTIMINGS; i++) {
        counter = 0;
        while (suli_pin_read(&__pin) == laststate) {
            counter++;
            suli_delay_us(1);
            if (counter == 255) {
                break;
            }
        }

        laststate = suli_pin_read(&__pin);

        if (counter == 255) break;

        // ignore first 3 transitions
        if ((i >= 4) && (i%2 == 0)) {
            // shove each bit into the storage bytes
            data[j/8] <<= 1;
            if (counter > _count)
            data[j/8] |= 1;
            j++;
        }
    }

    if ((j >= 40) &&
    (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) ) {
        return true;
    }


    return false;

}


// get temperature
float dht_read_temp(eScale scale)
{
    float f;

    switch (_type)
    {
        case DHT11:
        f = data[2];
        if (scale)
        f = convertCtoF(f);

        return f;
        case DHT22:
        case DHT21:
        f = data[2] & 0x7F;
        f *= 256;
        f += data[3];
        f /= 10;
        if (data[2] & 0x80)
        f *= -1;
        if (scale)
        f = convertCtoF(f);

        return f;
    }
    return -1;
}

// get humi...
float dht_read_hmd()
{
    float f;

    switch (_type)
    {
        case DHT11:
        f = data[0];
        return f;
        case DHT22:
        case DHT21:
        f = data[0];
        f *= 256;
        f += data[1];
        f /= 10;
        return f;
    }
    return -1;
}
