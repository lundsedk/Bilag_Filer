#include "ssd1331.h"

int main()
{
    char imageBuf_[OLED_WIDTH * OLED_HEIGHT * 2];

    for (int i = 0; i < sizeof(imageBuf_); i++)
    {
        imageBuf_[i] = 0xFF;
    }

    ssd1331 ssd1331_;
    ssd1331_.init();

    ssd1331_.sendCommand(DISPLAY_ON_NORMAL);
    ssd1331_.displayImage(&imageBuf_[0], sizeof(imageBuf_));

    sleep(1);

    for (int i = 0; i < sizeof(imageBuf_); i++)
    {
        imageBuf_[i] = 0x04;
    }

    ssd1331_.displayImage(&imageBuf_[0], sizeof(imageBuf_));

    return 0;
}