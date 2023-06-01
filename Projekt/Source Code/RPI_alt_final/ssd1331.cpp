/*****************************************************************************
*
* File                : ssd1331.cpp
* Hardware Environment: Raspberry Pi (Zero)
* Build Environment   : g++
* Version             : V1.0
* Author              : A. Lihn
*
******************************************************************************/

#include "ssd1331.h"

ssd1331::ssd1331() {}

ssd1331::~ssd1331() {}

void ssd1331::init() {

    gpio_write(RST, HIGH);
    usleep(100);
    gpio_write(RST, LOW);
    usleep(100);  
    gpio_write(RST, HIGH);

    sendCommand(DISPLAY_OFF);               // Display Off
    sendCommand(SET_REMAP_AND_COLOR_DEPTH); // Horisontal address increment, maps left to right, normal order RGB, 65K color format
    sendCommand(0x72);
    sendCommand(SET_DISPLAY_START_LINE);    // Set display Start Line to 0
    sendCommand(0x0);
    sendCommand(SET_DISPLAY_OFFSET);        // Set display offset to 0
    sendCommand(0x0);
    sendCommand(MODE_NORMAL);               // Set display mode to normal
    sendCommand(SET_MULTIPLEX_RATIO);       // Set multiplex ratio
    sendCommand(0x3F);
    sendCommand(SET_MASTER_CONFIG);         // Set master configuration
    sendCommand(0x8E);
    sendCommand(POWER_SAVE_MODE);           // Enable Power Save Mode
    sendCommand(0x1A);
    sendCommand(PHASE_PERIOD_ADJUSTMENT);   // Phase 1 and 2 period adjustment = defualt
    sendCommand(0x74);
    sendCommand(DISPLAY_CLOCK_DIV);         // Display clock divider = 0, oscillator frequency = max
    sendCommand(0xF0);
    sendCommand(SET_PRECHARGE_SPEED_A);     // Set Second Pre-change Speed For Color A to same value as contrast
    sendCommand(0xFF);
    sendCommand(SET_PRECHARGE_SPEED_B);     // Set Second Pre-change Speed For Color B to same value as contrast
    sendCommand(0xFF);
    sendCommand(SET_PRECHARGE_SPEED_C);     // Set Second Pre-change Speed For Color C to same value as contrast
    sendCommand(0xFF);
    sendCommand(SET_PRECHARGE_LEVEL);       // Set Pre-Change Level to default
    sendCommand(0x3A);
    sendCommand(SET_V_VOLTAGE);             // Set vcomH to default
    sendCommand(0x3E);
    sendCommand(MASTER_CURRENT_CONTROL);    // Value 0x01 -> 0x0E, dim -> bright
    sendCommand(0x06);
    sendCommand(SET_CONTRAST_A);            // Contrast for color A set to max value
    sendCommand(0xFF);
    sendCommand(SET_CONTRAST_B);            // Contrast for color B set to max value
    sendCommand(0xFF);
    sendCommand(SET_CONTRAST_C);            // Contrast for color C set to max value
    sendCommand(0xFF);
}

void ssd1331::displayImage(char* buffer, int size) {
    sendCommand(SET_COLUMN_ADDRESS);
    sendCommand(0);                 // Column start coordinate
    sendCommand(OLED_WIDTH - 1);    // Column end coordinate
    sendCommand(SET_ROW_ADDRESS);
    sendCommand(0);                 // Row start coordinate
    sendCommand(OLED_HEIGHT - 1);   // Row end coordinate

    gpio_write(DC, HIGH);               // D/C set HIGH for data transfer
    spi_transfer_data(buffer, size);    
    gpio_write(DC, LOW);                // D/C set low to minimize risk of pixel flaws
}

void ssd1331::sendCommand(char cmd) {
    gpio_write(DC, LOW);    // D/C set LOW for command transfer
    spi_transfer_cmd(cmd);  
}

int ssd1331::gpio_write(int pin, int value)
{
    size_t fd;
    int err;
    char buf[GPIO_BUF_SIZE];

    if (pin == RST)
    {
        if ((fd = open(FILE_PATH_RST, O_WRONLY)) < 0) {
            err = errno;
            printf("ERROR: GPIO device can not open\n");
            return errno;
        }

        sprintf(buf, "%d", value);
        err = write(fd, &buf, strlen(buf));
        close(fd);
    }

    if (pin == DC)
    {
        if ((fd = open(FILE_PATH_DC, O_WRONLY)) < 0) {
            err = errno;
            printf("ERROR: GPIO device can not open\n");
            return errno;
        }

        sprintf(buf, "%d", value);
        err = write(fd, &buf, strlen(buf));
        close(fd);
    }

    return err;
}

int ssd1331::spi_transfer_cmd(char cmd)
{
    int fd, num_wr;
    int status = 0;

    fd = open(FILE_PATH_SPI0, O_WRONLY);
    if (fd == -1)
    {
        printf("Failed to open with err: %s", strerror(errno));
        return -1;
    }

    num_wr = write(fd, &cmd, sizeof(cmd));
    if (num_wr == -1)
    {
        printf("Failed to write with err: %s", strerror(errno));
        return num_wr;
    }
    else if (num_wr < sizeof(cmd))
    {
        printf("Did not write the whole string, only %i bytes", num_wr);
    }

    status = close(fd);
    if (status == -1)
    {
        printf("Failed to close with err: %s", strerror(errno));
        return status;
    }

    return 0;
}

int ssd1331::spi_transfer_data(char* buffer, int size)
{
    int status = 0;
    int fd, num_wr, value;

    fd = open(FILE_PATH_SPI0, O_WRONLY);
    if (fd == -1)
    {
        printf("Failed to open with err: %s", strerror(errno));
        return -1;
    }

    num_wr = write(fd, buffer, size);
    if (num_wr == -1)
    {
        printf("Failed to write with err: %s", strerror(errno));
        return num_wr;
    }

    status = close(fd);
    if (status == -1)
    {
        printf("Failed to close with err: %s", strerror(errno));
        return status;
    }

    return 0;

}