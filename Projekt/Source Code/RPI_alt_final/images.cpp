/*****************************************************************************
*
* File                : images.cpp
* Hardware Environment: Raspberry Pi (Zero)
* Build Environment   : g++
* Version             : V1.0
* Author              : A. Lihn
*
******************************************************************************/

#include "images.h"
#include <stdlib.h>

/****** Public methods ******/

images::images(Log* logPtr, PlanteID* pdPtr)
    : logPtr_(logPtr), planteIDPtr_(pdPtr)
{
    position_ = 0;
}

images::~images() {}

void images::setImage(char choice)
{
    clear();

    switch (choice) {

    case START:
        bitmapStart();
        break;

    case PLANT_DATA:
        bitmapPlantdata();
        break;

    case PLANT:
        bitmapPlant();
        break;

    case SETUP:
        bitmapSetup();
        break;

    case SET_TYPE:
        bitmapType();
        break;

    case SET_NAME:
        bitmapName();
        break;

    case LOG_LIGHT:
        bitmapLogLight();
        break;

    case LOG_HUMIDITY:
        bitmapLogHum();
        break;

    case LOG_WEIGHT:
        bitmapLogWeight();
        break;

    default:
        break;
    }
    image_ = choice;
}

char images::getImage()
{
    return image_;
}

char* images::getImageBuf()
{
    return imageBuf_;
}

int images::getImageSize()
{
    return sizeof(imageBuf_);
}

int images::getPosition()
{
    return position_;
}

void images::setPosition(int pos)
{
    position_ = pos >= 0 ? pos : 0;
    switch (getImage()) {
    case PLANT_DATA:
        if (logPtr_->isEmpty())
        {
            if (pos > 0)
                position_ = 1;
        }
        else
        {
            if (pos > 3)
                position_ = 3;
        }
        break;

    case SETUP:
    case PLANT:
        if (pos > 1)
            position_ = 1;
        break;

    case SET_TYPE:
        if (pos > 2)
            position_ = 2;
        break;

    case SET_NAME:
        if (pos > 7)
            position_ = 7;
        break;

    default:
        break;
    }

}

/****** Private methods ******/

void images::clear()
{
    bitmapImgBackground(BLACK);
}

void images::drawPoint(int x, int y, uint16_t color)
{
    if (x >= OLED_WIDTH || y >= OLED_HEIGHT) // if x or y coordinates are invalid, do nothing
        return;

    // 16-bit pixel data is set to chosen color
    imageBuf_[x * 2 + y * OLED_WIDTH * 2] = color >> 8;
    imageBuf_[x * 2 + y * OLED_WIDTH * 2 + 1] = color;
}

void images::bitmapImage(uint8_t x, uint8_t y, const uint8_t* bmp, char width, char height, uint16_t color)
{
    uint8_t i, j, byteWidth = (width + 7) / 8;
    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            if (*(bmp + j * byteWidth + i / 8) & (128 >> (i & 7))) {
                drawPoint(x + i, y + j, color);
            }
        }
    }
}

void images::bitmapChar(uint8_t x, uint8_t y, char acsii, char size, char mode, uint16_t hwColor)
{
    uint8_t i, j, y0 = y, x0 = x;
    char temp;
    uint8_t ch = acsii - ' '; // Start array at ASCII ' '
    for (i = 0; i < size; i++) {

        /*** Size 6, vertical-run-through ***/
        if (size == 6)
        {
            if (mode)temp = font5x7[ch][i]; // Normal mode
            else temp = ~font5x7[ch][i]; // Inverted mode

            for (j = 0; j < 8; j++)
            {
                if (temp & 0x80) // Checks whether bit is set or not
                    drawPoint(x, y, hwColor);
                else
                    drawPoint(x, y, 0);

                temp <<= 1; // Shifts to next bit
                y++;
                if ((y - y0) == 8) // Checks whether end of vertical line is reached
                {
                    y = y0;
                    x++;
                }
            }
        }

        /*** Size 3, horisontal-run-through ***/
        if (size == 3)
        {
            if (mode)temp = font3x5[ch][i]; // Normal mode
            else temp = ~font3x5[ch][i]; // Inverted mode

            for (j = 0; j < 8; j++)
            {
                if (temp & 0x80) // Checks whether bit is set or not
                    drawPoint(x, y, hwColor);
                else
                    drawPoint(x, y, 0);

                temp <<= 1; // Shifts to next bit
                x++;
                if ((x - x0) == 4) // Checks whether end of horisontal line is reached
                {
                    x = x0;
                    y++;
                }
            }
        }
    }
}

void images::bitmapString(uint8_t x, uint8_t y, const char* pString, uint8_t size, uint8_t mode, uint16_t hwColor)
{
    if (size == 6)
    {
        while (*pString != '\0') {
            bitmapChar(x, y, *pString, size, mode, hwColor);
            x += size;  // Move 6 bit to the right
            pString++; // Move pointer to next character
        }
    }

    if (size == 3)
    {
        while (*pString != '\0')
        {
            bitmapChar(x, y, *pString, size, mode, hwColor);
            x += (size + 1); // Move 4 bit to the right
            pString++; // Move pointer to next character
        }
    }
}

void images::bitmapStart()
{
    bitmapImgBackground(DARK_BROWN);
    bitmapImgLogo(0, 0);
}

void images::bitmapPlantdata()
{
    char light[14];
    snprintf(light, sizeof(light), "LIGHT: %d", logPtr_->getLatest(LIGHT));
    char weight[14];
    snprintf(weight, sizeof(weight), "WEIGHT:%d g", logPtr_->getLatest(WEIGHT));
    char humidity[14];
    snprintf(humidity, sizeof(humidity), "MOIST: %d %%", logPtr_->getLatest(MOIST));
    char water[14];
    snprintf(water, sizeof(water), "WATER: %d %%", logPtr_->getLatest(WATERLVL));

    switch (planteIDPtr_->getPlanteType())
    {
    case TYPE_FLOWER:
        bitmapImgPlant(76, 0, FLOWER);
        break;

    case TYPE_LEAF:
        bitmapImgPlant(76, 0, LEAF);
        break;

    case TYPE_CACTUS:
        bitmapImgPlant(76, 0, CACTUS);
        break;

    default:
        break;
    }

    char name[6];
    strcpy(&name[0], (planteIDPtr_->getPlanteName()).c_str());
    bitmapString(78, 44, name, 3, 1, SILVER);

    if (logPtr_->isEmpty())
    {
        position_ = 4;
    }
    else
    {
        if (position_ == 4)
            position_ = 0;
    }

    switch (position_)
    {
    case 0:
        bitmapString(0, 9, &light[0], 6, 0, SILVER);
        bitmapString(0, 18, &weight[0], 6, 1, SILVER);
        bitmapString(0, 27, &humidity[0], 6, 1, SILVER);
        bitmapString(0, 36, &water[0], 6, 1, SILVER);
        bitmapString(0, 54, "NEW PLANT", 3, 1, SILVER);
        break;

    case 1:
        bitmapString(0, 9, &light[0], 6, 1, SILVER);
        bitmapString(0, 18, &weight[0], 6, 0, SILVER);
        bitmapString(0, 27, &humidity[0], 6, 1, SILVER);
        bitmapString(0, 36, &water[0], 6, 1, SILVER);
        bitmapString(0, 54, "NEW PLANT", 3, 1, SILVER);
        break;

    case 2:
        bitmapString(0, 9, &light[0], 6, 1, SILVER);
        bitmapString(0, 18, &weight[0], 6, 1, SILVER);
        bitmapString(0, 27, &humidity[0], 6, 0, SILVER);
        bitmapString(0, 36, &water[0], 6, 1, SILVER);
        bitmapString(0, 54, "NEW PLANT", 3, 1, SILVER);
        break;

    case 3:
        bitmapString(0, 9, &light[0], 6, 1, SILVER);
        bitmapString(0, 18, &weight[0], 6, 1, SILVER);
        bitmapString(0, 27, &humidity[0], 6, 1, SILVER);
        bitmapString(0, 36, &water[0], 6, 1, SILVER);
        bitmapString(0, 54, "NEW PLANT", 3, 0, SILVER);
        break;

    case 4:
        bitmapString(0, 9, "NO DATA!", 6, 1, SILVER);
        bitmapString(0, 54, "NEW PLANT", 3, 0, SILVER);
        break;

    default:
        break;
    }
}

void images::bitmapPlant()
{
    char name[10];
    strcpy(&name[0], (planteIDPtr_->getPlanteName()).c_str());

    bitmapString(0, 0, "YOUR PLANT:", 6, 1, LIGHT_GREEN);
    bitmapString(0, 16, "Name:", 6, 1, SILVER);
    bitmapString(34, 18, name, 3, 1, SILVER);
    bitmapString(0, 28, "Type:", 6, 1, SILVER);
    switch (planteIDPtr_->getPlanteType())
    {
    case TYPE_FLOWER:
        bitmapString(34, 30, "Flower", 3, 1, SILVER);
        bitmapImgPlant(76, 0, FLOWER);
        break;

    case TYPE_LEAF:
        bitmapString(34, 30, "Leaf", 3, 1, SILVER);
        bitmapImgPlant(76, 0, LEAF);
        break;

    case TYPE_CACTUS:
        bitmapString(34, 30, "Cactus", 3, 1, SILVER);
        bitmapImgPlant(76, 0, CACTUS);
        break;

    default:
        break;
    }

    if (position_)
    {
        bitmapString(44, 52, "OK", 6, 1, SILVER);
        bitmapString(60, 52, "Cancel", 6, 0, SILVER);
    }
    else
    {
        bitmapString(44, 52, "OK", 6, 0, SILVER);
        bitmapString(60, 52, "Cancel", 6, 1, SILVER);
    }

}

void images::bitmapSetup()
{
    bitmapString(0, 0, "SETUP NEW PLANT:", 6, 1, LIGHT_GREEN);
    if (position_) {
        bitmapString(20, 20, "OK", 6, 1, SILVER);
        bitmapString(20, 30, "Cancel", 6, 0, SILVER);
    }
    else {
        bitmapString(20, 20, "OK", 6, 0, SILVER);
        bitmapString(20, 30, "Cancel", 6, 1, SILVER);
    }
}

void images::bitmapType()
{
    bitmapString(0, 0, "CHOOSE TYPE:", 6, 1, LIGHT_GREEN);
    bitmapImgPlant(0, 14, FLOWER);
    bitmapImgPlant(30, 14, LEAF);
    bitmapImgPlant(60, 14, CACTUS);

    switch (position_)
    {
    case 0:
        bitmapString(0, 58, "Flower", 3, 0, SILVER);
        bitmapString(30, 58, "Leaf", 3, 1, SILVER);
        bitmapString(60, 58, "Cactus", 3, 1, SILVER);
        break;

    case 1:
        bitmapString(0, 58, "Flower", 3, 1, SILVER);
        bitmapString(30, 58, "Leaf", 3, 0, SILVER);
        bitmapString(60, 58, "Cactus", 3, 1, SILVER);
        break;

    case 2:
        bitmapString(0, 58, "Flower", 3, 1, SILVER);
        bitmapString(30, 58, "Leaf", 3, 1, SILVER);
        bitmapString(60, 58, "Cactus", 3, 0, SILVER);
        break;
    }
}

void images::bitmapName()
{
    bitmapString(0, 0, "CHOOSE NAME:", 6, 1, LIGHT_GREEN);

    bitmapString(0, 12, "-ROSA", 6, 1, SILVER);
    bitmapString(0, 24, "-ULLA", 6, 1, SILVER);
    bitmapString(0, 36, "-IBEN", 6, 1, SILVER);
    bitmapString(0, 48, "-LILY", 6, 1, SILVER);

    bitmapString(32, 12, "-BENT", 6, 1, SILVER);
    bitmapString(32, 24, "-ADAM", 6, 1, SILVER);
    bitmapString(32, 36, "-LARS", 6, 1, SILVER);
    bitmapString(32, 48, "-ASKE", 6, 1, SILVER);

    switch (position_)
    {
    case 0:
        bitmapString(0, 12, "-ROSA", 6, 0, SILVER);
        break;

    case 1:
        bitmapString(0, 24, "-ULLA", 6, 0, SILVER);
        break;

    case 2:
        bitmapString(0, 36, "-IBEN", 6, 0, SILVER);
        break;

    case 3:
        bitmapString(0, 48, "-LILY", 6, 0, SILVER);
        break;

    case 4:
        bitmapString(40, 12, "-BENT", 6, 0, SILVER);
        break;

    case 5:
        bitmapString(40, 24, "-ADAM", 6, 0, SILVER);
        break;

    case 6:
        bitmapString(40, 36, "-LARS", 6, 0, SILVER);
        break;

    case 7:
        bitmapString(40, 48, "-ASKE", 6, 0, SILVER);
        break;

    default:
        break;
    }
}

void images::bitmapLogHum()
{
    auto week = logPtr_->getWeek(MOIST);
    bitmapString(0, 0, "HUMIDITY LOG:", 6, 1, LIGHT_GREEN);

    char buf[20];
    snprintf(buf, sizeof(buf), "TODAY:      %d %%", week[0]);
    bitmapString(0, 12, buf, 3, 1, WHITE);

    snprintf(buf, sizeof(buf), "1 DAY AGO:  %d %%", week[1]);
    bitmapString(0, 19, buf, 3, 1, WHITE);

    snprintf(buf, sizeof(buf), "2 DAYS AGO: %d %%", week[2]);
    bitmapString(0, 26, buf, 3, 1, WHITE);

    snprintf(buf, sizeof(buf), "3 DAYS AGO: %d %%", week[3]);
    bitmapString(0, 33, buf, 3, 1, WHITE);

    snprintf(buf, sizeof(buf), "4 DAYS AGO: %d %%", week[4]);
    bitmapString(0, 40, buf, 3, 1, WHITE);

    snprintf(buf, sizeof(buf), "5 DAYS AGO: %d %%", week[5]);
    bitmapString(0, 47, buf, 3, 1, WHITE);

    snprintf(buf, sizeof(buf), "6 DAYS AGO: %d %%", week[6]);
    bitmapString(0, 54, buf, 3, 1, WHITE);

    bitmapImage(88, 59, symbol_return_inv, 8, 5, SILVER);
}

void images::bitmapLogLight()
{
    auto week = logPtr_->getWeek(LIGHT);
    bitmapString(0, 0, "LIGHT LOG:", 6, 1, LIGHT_GREEN);

    char buf[20];
    snprintf(buf, sizeof(buf), "TODAY:      %d", week[0]);
    bitmapString(0, 12, buf, 3, 1, WHITE);

    snprintf(buf, sizeof(buf), "1 DAY AGO:  %d", week[1]);
    bitmapString(0, 19, buf, 3, 1, WHITE);

    snprintf(buf, sizeof(buf), "2 DAYS AGO: %d", week[2]);
    bitmapString(0, 26, buf, 3, 1, WHITE);

    snprintf(buf, sizeof(buf), "3 DAYS AGO: %d", week[3]);
    bitmapString(0, 33, buf, 3, 1, WHITE);

    snprintf(buf, sizeof(buf), "4 DAYS AGO: %d", week[4]);
    bitmapString(0, 40, buf, 3, 1, WHITE);

    snprintf(buf, sizeof(buf), "5 DAYS AGO: %d", week[5]);
    bitmapString(0, 47, buf, 3, 1, WHITE);

    snprintf(buf, sizeof(buf), "6 DAYS AGO: %d", week[6]);
    bitmapString(0, 54, buf, 3, 1, WHITE);

    bitmapImage(88, 59, symbol_return_inv, 8, 5, SILVER);
}

void images::bitmapLogWeight()
{
    auto week = logPtr_->getWeek(WEIGHT);
    bitmapString(0, 0, "WEIGHT LOG:", 6, 1, LIGHT_GREEN);

    char buf[20];
    snprintf(buf, sizeof(buf), "TODAY:      %d G", week[0]);
    bitmapString(0, 12, buf, 3, 1, WHITE);

    snprintf(buf, sizeof(buf), "1 DAY AGO:  %d G", week[1]);
    bitmapString(0, 19, buf, 3, 1, WHITE);

    snprintf(buf, sizeof(buf), "2 DAYS AGO: %d G", week[2]);
    bitmapString(0, 26, buf, 3, 1, WHITE);

    snprintf(buf, sizeof(buf), "3 DAYS AGO: %d G", week[3]);
    bitmapString(0, 33, buf, 3, 1, WHITE);

    snprintf(buf, sizeof(buf), "4 DAYS AGO: %d G", week[4]);
    bitmapString(0, 40, buf, 3, 1, WHITE);

    snprintf(buf, sizeof(buf), "5 DAYS AGO: %d G", week[5]);
    bitmapString(0, 47, buf, 3, 1, WHITE);

    snprintf(buf, sizeof(buf), "6 DAYS AGO: %d G", week[6]);
    bitmapString(0, 54, buf, 3, 1, WHITE);

    bitmapImage(88, 59, symbol_return_inv, 8, 5, SILVER);
}

/**** bitmaps to be part of other bitmaps ****/

void images::bitmapImgBackground(uint16_t color)
{
    uint16_t i, j;
    for (i = 0; i < OLED_HEIGHT; i++) {
        for (j = 0; j < OLED_WIDTH; j++) {
            drawPoint(j, i, color);
        }
    }
}

void images::bitmapImgPlant(uint8_t x, uint8_t y, uint8_t image)
{
    /* Bitmap Pot*/
    bitmapImage(x, y, plantPot_rim, 24, 42, RED);
    bitmapImage(x, y, plantPot_shade, 24, 42, ROSE);
    bitmapImage(x, y, plantPot_fill, 24, 42, RED);
    bitmapImage(x, y, plantPot_edge, 24, 42, DARK_RED);

    switch (image) {
    case LEAF:
        bitmapImage(x, y, plantLeaf_edge, 24, 42, GREEN);
        bitmapImage(x, y, plantLeaf_fill, 24, 42, LIME);
        bitmapImage(x, y, plantLeaf_inside, 24, 42, DARK_GREEN);
        break;

    case CACTUS:
        bitmapImage(x, y, plantCactus_dark, 24, 42, DARK_GREEN);
        bitmapImage(x, y, plantCactus_light, 24, 42, GREEN);
        bitmapImage(x, y, plantCactus_dots, 24, 42, YELLOW);
        break;

    case FLOWER:
        bitmapImage(x, y, plantFlower_centerDark, 24, 42, YELLOW);
        bitmapImage(x, y, plantFlower_centerLight, 24, 42, GOLDEN);
        bitmapImage(x, y, plantFlower_leafDark, 24, 42, VIOLET);
        bitmapImage(x, y, plantFlower_leafLight, 24, 42, PURPLE);
        bitmapImage(x, y, plantFlower_stemDark, 24, 42, GREEN);
        bitmapImage(x, y, plantFlower_stemLight, 24, 42, LIME);
        break;

    default:
        break;
    }
}

void images::bitmapImgLogo(uint8_t x, uint8_t y)
{
    bitmapImage(0, 12, logo_ipt, 96, 43, WHITE);
    bitmapImage(0, 12, logo_o_dark, 96, 43, WHITE);
    bitmapImage(0, 12, logo_o_light, 96, 43, GREEN);
    bitmapImage(0, 12, logo_o_medium, 96, 43, DARK_GREEN);
}