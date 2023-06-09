/*****************************************************************************
*
* File                : plant_images.h
* Hardware Environment: Raspberry Pi (Zero)
* Build Environment   : g++
* Version             : V1.0
* Author              : A. Lihn
*
******************************************************************************/

#ifndef _PLANT_IMAGES_H_
#define _PLANT_IMAGES_H_

/************* Plant leafs *************/
/************* 24*42 pixels ************/
static const uint8_t plantLeaf_edge[3 * 42] =
{ 0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,

    0x1F,0x00,0x00,
    0x20,0xC0,0x00,
    0x40,0x27,0x80,
    0x40,0x28,0x40,
    0x40,0x10,0x20,
    0x40,0x38,0x40,
    0x20,0x57,0x80,
    0x1F,0x90,0x00,
    0x00,0x13,0x80,
    0x00,0x1C,0x40,
    0x01,0x93,0x80,
    0x02,0x50,0x00,
    0x42,0x30,0x00,
    0xB9,0x30,0x60,
    0x84,0xD3,0x90,
    0x82,0x14,0x10,
    0x46,0x18,0x20,
    0x3A,0x14,0xC0,
    0x02,0x13,0x00,
    0x02,0x10,0x00,

    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
};

static const uint8_t plantLeaf_fill[3 * 42] =
{ 0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,

    0x00,0x00,0x00,
    0x1F,0x00,0x00,
    0x3F,0xC0,0x00,
    0x3B,0xC7,0x80,
    0x3C,0x00,0xC0,
    0x3F,0xC7,0x80,
    0x1F,0x80,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x80,
    0x00,0x00,0x00,
    0x01,0x80,0x00,
    0x01,0x40,0x00,
    0x40,0x80,0x00,
    0x78,0x00,0x60,
    0x60,0x03,0xA0,
    0x38,0x00,0x40,
    0x00,0x03,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,

    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
};

static const uint8_t plantLeaf_inside[3 * 42] =
{ 0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,

    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x04,0x00,0x00,
    0x03,0xEF,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x03,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x80,0x00,
    0x00,0x40,0x00,
    0x00,0x00,0x00,
    0x1C,0x00,0x40,
    0x00,0x07,0x80,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,

    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
};

/************* Plant cactus ************/
/************* 24*42 pixels ************/
static const uint8_t plantCactus_dark[3 * 42] =
{ 0x00,0xE0,0x00,
    0x01,0x50,0x00,
    0x02,0x48,0x00,
    0x02,0x48,0x00,
    0x02,0x08,0x00,
    0x42,0x48,0x00,
    0xA2,0x48,0x00,
    0xA2,0x48,0x00,
    0xA2,0x48,0x00,
    0xA2,0x48,0x00,
    0xA2,0x48,0x00,
    0xA2,0x48,0x00,
    0xA2,0x08,0x00,
    0xB6,0x48,0x00,
    0x8B,0x48,0x00,
    0xA0,0x48,0x00,
    0x7A,0x48,0x60,
    0x06,0x48,0x90,
    0x02,0x08,0x90,
    0x02,0x48,0x90,
    0x02,0x48,0x90,
    0x02,0x48,0x90,
    0x02,0x4B,0x10,
    0x02,0x4A,0x10,
    0x02,0x48,0x30,
    0x02,0x4B,0xE0,
    0x02,0x4C,0x00,
    0x02,0x48,0x00,
    0x02,0x48,0x00,
    0x02,0x58,0x00,

    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
};

static const uint8_t plantCactus_light[3 * 42] =
{ 0x00,0x00,0x00,
    0x00,0xA0,0x00,
    0x01,0xA0,0x00,
    0x01,0xB0,0x00,
    0x01,0xB0,0x00,
    0x01,0xB0,0x00,
    0x41,0xB0,0x00,
    0x41,0xA0,0x00,
    0x41,0xB0,0x00,
    0x01,0xB0,0x00,
    0x41,0xB0,0x00,
    0x41,0xB0,0x00,
    0x41,0xB0,0x00,
    0x41,0xB0,0x00,
    0x54,0xB0,0x00,
    0x5C,0xA0,0x00,
    0x05,0xB0,0x00,
    0x01,0xB0,0x40,
    0x01,0xB0,0x60,
    0x01,0xB0,0x60,
    0x01,0xB0,0x60,
    0x01,0xB0,0x60,
    0x01,0x90,0xE0,
    0x01,0xB5,0x20,
    0x01,0x33,0xC0,
    0x01,0xB4,0x00,
    0x01,0xB0,0x00,
    0x01,0xB0,0x00,
    0x01,0xA0,0x00,
    0x01,0xA0,0x00,

    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
};

static const uint8_t plantCactus_dots[3 * 42] =
{ 0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x10,0x00,
    0x00,0x00,0x00,
    0x00,0x40,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x10,0x00,
    0x00,0x00,0x00,
    0x40,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x40,0x00,
    0x00,0x00,0x00,
    0x20,0x00,0x00,
    0x03,0x10,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x20,
    0x00,0x40,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x20,0x00,
    0x00,0x00,0xC0,
    0x00,0x84,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x10,0x00,
    0x00,0x00,0x00,

    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
};

/************* Plant flower ************/
/************* 24*42 pixels ************/
static const uint8_t plantFlower_stemLight[3 * 42] =
{ 0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,

    0x00,0xA0,0x00,
    0x00,0xA0,0x00,
    0x00,0xAC,0x00,
    0x06,0xB4,0x00,
    0x05,0xA4,0x00,
    0x04,0xAC,0x00,
    0x06,0xB8,0x00,
    0x03,0xA0,0x00,
    0x00,0xA0,0x00,
    0x00,0xA0,0x00,

    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
};

static const uint8_t plantFlower_stemDark[3 * 42] =
{ 0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,

    0x00,0x40,0x00,
    0x00,0x40,0x00,
    0x00,0x40,0x00,
    0x00,0x48,0x00,
    0x02,0x58,0x00,
    0x03,0x50,0x00,
    0x01,0x40,0x00,
    0x00,0x40,0x00,
    0x00,0x40,0x00,
    0x00,0x40,0x00,

    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
};

static const uint8_t plantFlower_leafLight[3 * 42] =
{ 0x00,0x00,0x00,

    0x00,0x00,0x00,
    0x01,0xF0,0x00,
    0x03,0xF8,0x00,
    0x01,0xF0,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x38,0x03,0x80,
    0x3C,0x01,0xC0,
    0x38,0x01,0xC0,
    0x38,0x01,0xC0,
    0x38,0x01,0xC0,
    0x10,0x01,0x00,
    0x00,0x00,0x00,
    0x01,0x10,0x00,
    0x01,0xF8,0x00,
    0x01,0xF8,0x00,
    0x00,0xF8,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,

    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
};

static const uint8_t plantFlower_leafDark[3 * 42] =
{ 0x00,0x00,0x00,

    0x01,0xF0,0x00,
    0x02,0x08,0x00,
    0x04,0x04,0x00,
    0x06,0x0C,0x00,
    0x07,0xFC,0x00,
    0x3B,0xFB,0x80,
    0x45,0x14,0x40,
    0xC2,0x0E,0x20,
    0xC4,0x06,0x20,
    0xC4,0x06,0x20,
    0xC4,0x06,0x20,
    0xEE,0x0E,0xE0,
    0x7D,0x17,0xC0,
    0x3A,0xEB,0x80,
    0x06,0x04,0x00,
    0x06,0x04,0x00,
    0x07,0x04,0x00,
    0x03,0xF8,0x00,
    0x01,0xF0,0x00,

    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
};

static const uint8_t plantFlower_centerDark[3 * 42] =
{ 0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,

    0x00,0xC0,0x00,
    0x01,0x80,0x00,
    0x03,0x80,0x00,
    0x03,0x80,0x00,
    0x03,0x80,0x00,
    0x01,0xB0,0x00,
    0x00,0xE0,0x00,

    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
};

static const uint8_t plantFlower_centerLight[3 * 42] =
{ 0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,

    0x00,0x20,0x00,
    0x00,0x70,0x00,
    0x00,0xF8,0x00,
    0x00,0xF8,0x00,
    0x00,0xF8,0x00,
    0x00,0x40,0x00,
    0x00,0x00,0x00,

    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
};

#endif