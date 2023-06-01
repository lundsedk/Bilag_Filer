/*****************************************************************************
*
* File                : images_constants.h
* Hardware Environment: Raspberry Pi (Zero)
* Build Environment   : g++
* Version             : V1.0
* Author              : Anette Olesen Lihn
*
******************************************************************************/

#ifndef _IMAGES_CONSTANTS_H_
#define _IMAGES_CONSTANTS_H_

/******** DISPLAY MEASUREMENTS ********/
#define OLED_WIDTH 96
#define OLED_HEIGHT 64

/*********** PLANT CHOICES ************/
#define     FLOWER          0x00
#define     LEAF            0x01
#define     CACTUS          0x02

/*********** IMAGE CHOICES ************/
#define     CLEAR           0x03
#define     START           0x04
#define     PLANT_DATA      0x05
#define     PLANT           0x06
#define     SETUP           0x07
#define     SET_TYPE        0x08
#define     SET_NAME        0x09
#define     LOG_LIGHT       0x0B
#define     LOG_HUMIDITY    0x0C
#define     LOG_WEIGHT      0x0D

/************* RGB COLORS (16-bit) *************/
#define RGB(R,G,B)  (((R >> 3) << 11) | ((G >> 2) << 5) | (B >> 3))
enum Color {
    BLACK = RGB(0, 0, 0), // black
    WHITE = RGB(255, 255, 255), // white
    SILVER = RGB(192, 192, 192), // silver
    GRAY = RGB(128, 128, 128), // gray
    DARK_GRAY = RGB(64, 64, 64), // dark gray
    BLUE = RGB(0, 0, 255), // blue
    NAVY = RGB(0, 0, 128), // navy
    LIGHT_BLUE = RGB(48, 152, 255), // light blue
    CYAN = RGB(0, 255, 255), // cyan
    TURQUIOSE = RGB(64, 224, 208), // turquiose
    GREEN = RGB(0, 204, 0), // green
    LIME = RGB(0, 252, 0), // lime
    LIGHT_GREEN = RGB(96, 252, 96), // light green
    DARK_GREEN = RGB(0, 100, 0), // dark green
    VIOLET = RGB(148, 0, 211), // violet
    PURPLE = RGB(255, 0, 255), // purple
    LIGHT_PURPLE = RGB(128, 0, 128), // light purple
    PINK = RGB(255, 20, 147), // deep pink
    ROSE = RGB(255, 105, 180), // hot pink
    RED = RGB(255, 0, 0), // red
    DARK_RED = RGB(139, 0, 0), // dark red
    YELLOW = RGB(255, 255, 0), // yellow
    GOLDEN = RGB(255, 215, 0), // golden
    ORANGE = RGB(255, 165, 0), // orange
    BROWN = RGB(96, 48, 0), // brown
    DARK_BROWN = RGB(48, 24, 0), // dark brown
    LIGHT_BROWN = RGB(200, 132, 56), // light brown
    CHOCOLATE = RGB(136, 68, 16), // chocolate 
};

#endif