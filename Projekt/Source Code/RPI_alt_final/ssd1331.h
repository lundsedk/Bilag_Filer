/*****************************************************************************
*
* File                : ssd1331.h
* Hardware Environment: Raspberry Pi (Zero)
* Build Environment   : g++
* Version             : V1.0
* Author              : Anette Olesen Lihn
*
******************************************************************************/

#ifndef _SSD1331_H_
#define _SSD1331_H_

#include "ssd1331_constants.h"
#include <unistd.h>
#include <stdio.h>
#include <cstdint>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/ioctl.h>

class ssd1331
{
private:
    int gpio_write(int pin, int value);
    int spi_transfer_cmd(char cmd);
    int spi_transfer_data(char* buffer, int size);
public:
    ssd1331();
    ~ssd1331();
    void init();                                // Initialize display with initial settings
    void displayImage(char* buffer, int size);  // Sends imageBuffer to screen
    void sendCommand(char cmd);                 // Sends command
};

#endif