/*****************************************************************************
*
* File                : sdd1331_constants.h
* Hardware Environment: Raspberry Pi (Zero)
* Build Environment   : g++
* Version             : V1.0
* Author              : Anette Olesen Lihn
*
******************************************************************************/

#ifndef _SSD1331_CONSTANTS_H_
#define _SSD1331_CONSTANTS_H_

#define LOW     0
#define HIGH    1
#define GPIO_BUF_SIZE 10

/************** GPIO PINS *************/
#define RST     19
#define DC      13

/******** DISPLAY MEASUREMENTS ********/
#define OLED_WIDTH 96
#define OLED_HEIGHT 64

/************ DRIVER PATHS ***********/
#define FILE_PATH_DC "/dev/gpio_dc"     // D/C device
#define FILE_PATH_RST "/dev/gpio_rst"   // RESET device
#define FILE_PATH_SPI0 "/dev/spi_drv0"  // SPI device

/******** FUNDAMENTAL COMMANDS ********/
#define SET_COLUMN_ADDRESS              0x15
#define SET_ROW_ADDRESS                 0x75
#define SET_CONTRAST_A                  0x81
#define SET_CONTRAST_B                  0x82
#define SET_CONTRAST_C                  0x83
#define MASTER_CURRENT_CONTROL          0x87
#define SET_PRECHARGE_SPEED_A           0x8A
#define SET_PRECHARGE_SPEED_B           0x8B
#define SET_PRECHARGE_SPEED_C           0x8C
#define SET_REMAP_AND_COLOR_DEPTH       0xA0
#define SET_DISPLAY_START_LINE          0xA1
#define SET_DISPLAY_OFFSET              0xA2
#define MODE_NORMAL                     0xA4
#define MODE_ENTIRE_DISPLAY_ON          0xA5
#define MODE_ENTIRE_DISPLAY_OFF         0xA6
#define MODE_INVERSE_DISPLAY            0xA7
#define SET_MULTIPLEX_RATIO             0xA8
#define DIM_MODE_SETTING                0xAB
#define SET_MASTER_CONFIG               0xAD
#define DISPLAY_ON_DIM                  0xAC
#define DISPLAY_OFF                     0xAE
#define DISPLAY_ON_NORMAL               0xAF
#define POWER_SAVE_MODE                 0xB0
#define PHASE_PERIOD_ADJUSTMENT         0xB1
#define DISPLAY_CLOCK_DIV               0xB3
#define SET_GRAy_SCALE_TABLE            0xB8
#define ENABLE_LINEAR_GRAY_SCALE_TABLE  0xB9
#define SET_PRECHARGE_LEVEL             0xBB
#define SET_V_VOLTAGE                   0xBE
#define SET_COMMAND_LOCK                0xFD
#define DRAW_LINE                       0x21
#define DRAW_RECTANGLE                  0x22
#define COPY                            0x23
#define DIM_WINDOW                      0x24
#define CLEAR_WINDOW                    0x25
#define FILL_WINDOW                     0x26
#define DISABLE_FILL                    0x00
#define ENABLE_FILL                     0x01
#define CONTINUOUS_SCROLLING_SETUP      0x27
#define DEACTIVE_SCROLLING              0x2E
#define ACTIVE_SCROLLING                0x2F

#endif