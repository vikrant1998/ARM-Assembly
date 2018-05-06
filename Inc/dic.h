// User defined pin structure
#include <stdint.h>
#include "stm32f0xx_hal.h"

struct gpioPin
{
    char gpio;
    int  pin;
};

//Accepts a list of pins for SSD and the digit to print and prints a digit on SSD
//Doesn't support decimal point!
void segmentLED(uint16_t digit, struct gpioPin ssdPins[]);
