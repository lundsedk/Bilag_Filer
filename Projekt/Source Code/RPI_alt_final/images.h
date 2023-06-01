/*****************************************************************************
*
* File                : images.h
* Hardware Environment: Raspberry Pi (Zero)
* Build Environment   : g++
* Version             : V1.0
* Author              : A. Lihn
*
******************************************************************************/

#ifndef _IMAGES_H_
#define _IMAGES_H_

#include <unistd.h>
#include <stdio.h>
#include <cstdint>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/ioctl.h>
#include <string>
#include "images_constants.h"
#include "bitmaps.h"
//#include "Plantedata.h"
#include "log.h"
#include "PlanteID.hpp"

class images
{
private:
    char imageBuf_[OLED_WIDTH * OLED_HEIGHT * 2];
    int position_;
    char image_;
    PlanteID* planteIDPtr_;
    Log* logPtr_;

    void clear();   // Clear buffer (black screen)
    void drawPoint(int x, int y, uint16_t color); // draw point at certain position with specified color
    void bitmapImage(uint8_t x, uint8_t y, const uint8_t* bmp, char width, char height, uint16_t color); // Draw bitmap
    void bitmapChar(uint8_t x, uint8_t y, char acsii, char size, char mode, uint16_t hwColor);
    void bitmapString(uint8_t x, uint8_t y, const char* pString, uint8_t size, uint8_t mode, uint16_t hwColor);

    void bitmapStart();
    void bitmapPlantdata();
    void bitmapPlant();
    void bitmapSetup();
    void bitmapType();
    void bitmapName();
    void bitmapLogHum();
    void bitmapLogLight();
    void bitmapLogWeight();

    void bitmapImgBackground(uint16_t color);
    void bitmapImgPlant(uint8_t x, uint8_t y, uint8_t image);
    void bitmapImgLogo(uint8_t x, uint8_t);

public:
    images(Log* logPtr = NULL, PlanteID* pdPtr = NULL);
    ~images();
    void setImage(char choice);   // Creates image in imageBuf_
    char getImage();
    char* getImageBuf();                           // Gets imageBuf_
    int getImageSize();                         // Gets size of imageBuf_
    int getPosition();
    void setPosition(int pos);
};

#endif