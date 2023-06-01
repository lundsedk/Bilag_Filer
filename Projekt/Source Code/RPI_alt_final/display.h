/*****************************************************************************
*
* File                : display.h
* Hardware Environment: Raspberry Pi (Zero)
* Build Environment   : GCC
* Version             : V1.0
* Author              : Anette Olesen Lihn
*
******************************************************************************/

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "ssd1331.h"
#include "images.h"
#include <stdio.h>

class display
{
private:
    ssd1331 ssd1331_;
    images* imagesPtr_;

public:
    display(images* imagePtr);
    ~display();
    void init();                // Initializes display
    void turnOn();              // Turns on display
    void turnOff();             // Turns off display
    void show(char choice);     // Displays image

};

#endif