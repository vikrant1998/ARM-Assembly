#include "dic.h"

void _display0(struct gpioPin ssdPins[]);
void _display1(struct gpioPin ssdPins[]);
void _display2(struct gpioPin ssdPins[]);
void _display3(struct gpioPin ssdPins[]);
void _display4(struct gpioPin ssdPins[]);
void _display5(struct gpioPin ssdPins[]);
void _display6(struct gpioPin ssdPins[]);
void _display7(struct gpioPin ssdPins[]);
void _display8(struct gpioPin ssdPins[]);
void _display9(struct gpioPin ssdPins[]);
void _displayDash(struct gpioPin ssdPins[]);
uint16_t pinDecode(uint16_t pinNum);
GPIO_TypeDef* gpioDecode(char GPIO);
void segmentLED(uint16_t digit, struct gpioPin ssdPins[]);

void segmentLED(uint16_t digit, struct gpioPin ssdPins[])
{
    switch(digit)
    {
        case 0:
            _display0(ssdPins);
            break;
        case 1:
            _display1(ssdPins);
            break;
        case 2:
            _display2(ssdPins);
            break;
        case 3:
            _display3(ssdPins);
            break;
        case 4:
            _display4(ssdPins);
            break;
        case 5:
            _display5(ssdPins);
            break;
        case 6:
            _display6(ssdPins);
            break;
        case 7:
            _display7(ssdPins);
            break;
        case 8:
            _display8(ssdPins);
            break;
        case 9:
            _display9(ssdPins);
            break;
        default:
            _displayDash(ssdPins);
            break;
    }
}
void _displayDash(struct gpioPin ssdPins[])
{
    int i = 0;
    for(i = 1; i < 8; i++)
    {
        if(i == 6)
        {
            HAL_GPIO_WritePin(gpioDecode(ssdPins[i - 1].gpio), 
                              pinDecode(ssdPins[i - 1].pin),
                              GPIO_PIN_SET);
        }
        else
        {
            HAL_GPIO_WritePin(gpioDecode(ssdPins[i - 1].gpio), 
                              pinDecode(ssdPins[i - 1].pin),
                              GPIO_PIN_RESET);
        }
    }
}
void _display9(struct gpioPin ssdPins[])
{
    int i = 0;
    for(i = 1; i < 8; i++)
    {
        if(i == 3 || i == 4)
        {
            HAL_GPIO_WritePin(gpioDecode(ssdPins[i - 1].gpio), 
                              pinDecode(ssdPins[i - 1].pin),
                              GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(gpioDecode(ssdPins[i - 1].gpio), 
                              pinDecode(ssdPins[i - 1].pin),
                              GPIO_PIN_SET);
        }
    }
}
void _display8(struct gpioPin ssdPins[])
{
    int i = 0;
    for(i = 1; i < 8; i++)
    {
        HAL_GPIO_WritePin(gpioDecode(ssdPins[i - 1].gpio), 
                          pinDecode(ssdPins[i - 1].pin),
                          GPIO_PIN_SET);
    }
}
void _display7(struct gpioPin ssdPins[])
{
    int i = 0;
    for(i = 1; i < 8; i++)
    {
        if(i == 1 || i == 5 || i == 7)
        {
            HAL_GPIO_WritePin(gpioDecode(ssdPins[i - 1].gpio), 
                              pinDecode(ssdPins[i - 1].pin),
                              GPIO_PIN_SET);
        }
        else
        {
            HAL_GPIO_WritePin(gpioDecode(ssdPins[i - 1].gpio), 
                              pinDecode(ssdPins[i - 1].pin),
                              GPIO_PIN_RESET);
        }
    }
}
void _display6(struct gpioPin ssdPins[])
{
    int i = 0;
    for(i = 1; i < 8; i++)
    {
        if(i == 7)
        {
            HAL_GPIO_WritePin(gpioDecode(ssdPins[i - 1].gpio), 
                              pinDecode(ssdPins[i - 1].pin),
                              GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(gpioDecode(ssdPins[i - 1].gpio), 
                              pinDecode(ssdPins[i - 1].pin),
                              GPIO_PIN_SET);
        }
    }
}
void _display5(struct gpioPin ssdPins[])
{
    int i = 0;
    for(i = 1; i < 8; i++)
    {
        if(i == 3 || i == 7)
        {
            HAL_GPIO_WritePin(gpioDecode(ssdPins[i - 1].gpio), 
                              pinDecode(ssdPins[i - 1].pin),
                              GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(gpioDecode(ssdPins[i - 1].gpio), 
                              pinDecode(ssdPins[i - 1].pin),
                              GPIO_PIN_SET);
        }
    }
}
void _display4(struct gpioPin ssdPins[])
{
    int i = 0;
    for(i = 1; i < 8; i++)
    {
        if(i == 1 || i == 3 || i == 4)
        {
            HAL_GPIO_WritePin(gpioDecode(ssdPins[i - 1].gpio), 
                              pinDecode(ssdPins[i - 1].pin),
                              GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(gpioDecode(ssdPins[i - 1].gpio), 
                              pinDecode(ssdPins[i - 1].pin),
                              GPIO_PIN_SET);
        }
    }
}
void _display3(struct gpioPin ssdPins[])
{
    int i = 0;
    for(i = 1; i < 8; i++)
    {
        if(i == 2 || i == 3)
        {
            HAL_GPIO_WritePin(gpioDecode(ssdPins[i - 1].gpio), 
                              pinDecode(ssdPins[i - 1].pin),
                              GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(gpioDecode(ssdPins[i - 1].gpio), 
                              pinDecode(ssdPins[i - 1].pin),
                              GPIO_PIN_SET);
        }
    }
}
void _display2(struct gpioPin ssdPins[])
{
    int i = 0;
    for(i = 1; i < 8; i++)
    {
        if(i == 2 || i == 5)
        {
            HAL_GPIO_WritePin(gpioDecode(ssdPins[i - 1].gpio), 
                              pinDecode(ssdPins[i - 1].pin),
                              GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(gpioDecode(ssdPins[i - 1].gpio), 
                              pinDecode(ssdPins[i - 1].pin),
                              GPIO_PIN_SET);
        }
    }
}

void _display1(struct gpioPin ssdPins[])
{
    int i = 0;
    for(i = 1; i < 8; i++)
    {
        if(i == 5 || i == 7)
        {
            HAL_GPIO_WritePin(gpioDecode(ssdPins[i - 1].gpio), 
                              pinDecode(ssdPins[i - 1].pin),
                              GPIO_PIN_SET);
        }
        else
        {
            HAL_GPIO_WritePin(gpioDecode(ssdPins[i - 1].gpio), 
                              pinDecode(ssdPins[i - 1].pin),
                              GPIO_PIN_RESET);
        }
    }
}

void _display0(struct gpioPin ssdPins[])
{
    int i = 0;
    for(i = 1; i < 8; i++)
    {
        if(i == 6)
        {
            HAL_GPIO_WritePin(gpioDecode(ssdPins[i - 1].gpio), 
                              pinDecode(ssdPins[i - 1].pin),
                              GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(gpioDecode(ssdPins[i - 1].gpio), 
                              pinDecode(ssdPins[i - 1].pin),
                              GPIO_PIN_SET);
        }
    }
}

//Returns GPIOx macro
GPIO_TypeDef* gpioDecode(char GPIO)
{
    if(GPIO == 'A')
        return GPIOA;
    else if(GPIO == 'B')
        return GPIOB;
    else if(GPIO == 'C')
        return GPIOC;
    else if(GPIO == 'D')
        return GPIOD;
    else if(GPIO == 'F')
        return GPIOF;
    return GPIOB;
}

// Returns pin macro
uint16_t pinDecode(uint16_t pinNum)
{
    if(pinNum == 0)
        return GPIO_PIN_0;
    else if(pinNum == 1)
        return GPIO_PIN_1;
    else if(pinNum == 2)
        return GPIO_PIN_2;
    else if(pinNum == 3)
        return GPIO_PIN_3;
    else if(pinNum == 4)
        return GPIO_PIN_4;
    else if(pinNum == 5)
        return GPIO_PIN_5;
    else if(pinNum == 6)
        return GPIO_PIN_6;
    else if(pinNum == 7)
        return GPIO_PIN_7;
    else if(pinNum == 8)
        return GPIO_PIN_8;
    else if(pinNum == 9)
        return GPIO_PIN_9;
    else if(pinNum == 10)
        return GPIO_PIN_10;
    else if(pinNum == 11)
        return GPIO_PIN_11;
    else if(pinNum == 12)
        return GPIO_PIN_12;
    else if(pinNum == 13)
        return GPIO_PIN_14;
    else if(pinNum == 15)
        return GPIO_PIN_15;
    return GPIO_PIN_5;
}
