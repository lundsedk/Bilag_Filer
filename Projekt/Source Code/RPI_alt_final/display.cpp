/*****************************************************************************
*
* File                : display.cpp
* Hardware Environment: Raspberry Pi (Zero)
* Build Environment   : GCC
* Version             : V1.0
* Author              : Anette Olesen Lihn
*
******************************************************************************/

#include "display.h"

display::display(images* imagesPtr) :imagesPtr_(imagesPtr) {}

display::~display() {}

void display::init() {
    ssd1331_.init();    // Initializes SSD1331 driver
    show(CLEAR);        // Ensures black screen at startup
}

void display::show(char choice) {

    imagesPtr_->setImage(choice);   // Bitmaps image
    ssd1331_.displayImage(imagesPtr_->getImageBuf(), imagesPtr_->getImageSize()); // Displays image
}

void display::turnOn() {
    ssd1331_.sendCommand(DISPLAY_ON_NORMAL);
}

void display::turnOff() {
    ssd1331_.sendCommand(DISPLAY_OFF);
    show(CLEAR);    // Ensures black screen at startup
}