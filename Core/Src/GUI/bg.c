#include "lcd.h"
#include "GUI/bg.h"
//#include "ff.h"

#include "main.h"
// #include "ff.h" // Import the FatFS library for reading files from the SD card

void BG_DrawBackground(const unsigned short bg[])
{
    uint16_t x, y;
    uint16_t width = LCD_DispWindow_COLUMN; // Width
    uint16_t height = LCD_DispWindow_PAGE; // Height

    LCD_OpenWindow(0, 0, width, height);
    LCD_Write_Cmd(CMD_SetPixel);

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            LCD_Write_Data(bg[y * width + x]);
        }
    }
}

uint16_t GUI_GetBackgroundPixel(uint16_t x, uint16_t y) {
    // Assume that the background image data is stored in an array named bgImageData
    // Please note that if your background image data is stored differently, modify this function accordingly
    return bgImageData[y * BG_IMAGE_WIDTH + x];
}

void GUI_LoadBackgroundFromSDCard(const char *filename) {
    //FIL file;
    //FRESULT result = f_open(&file, filename, FA_READ);
    //if (result != FR_OK) {
    //    return;
    //}

    uint8_t bmpHeader[54];
    //UINT bytesRead;
    //f_read(&file, bmpHeader, sizeof(bmpHeader), &bytesRead);

    uint32_t width = bmpHeader[18] | (bmpHeader[19] << 8) | (bmpHeader[20] << 16) | (bmpHeader[21] << 24);
    uint32_t height = bmpHeader[22] | (bmpHeader[23] << 8) | (bmpHeader[24] << 16) | (bmpHeader[25] << 24);

    if (width != BG_IMAGE_WIDTH || height != BG_IMAGE_HEIGHT) {
        //f_close(&file);
        return;
    }

    uint32_t dataOffset = bmpHeader[10] | (bmpHeader[11] << 8) | (bmpHeader[12] << 16) | (bmpHeader[13] << 24);
    //f_lseek(&file, dataOffset);

    for (int y = BG_IMAGE_HEIGHT - 1; y >= 0; y--) {
        for (int x = 0; x < BG_IMAGE_WIDTH; x++) {
            uint8_t pixelData[2];
            //f_read(&file, pixelData, sizeof(pixelData), &bytesRead);
            bgImageData[y * BG_IMAGE_WIDTH + x] = (pixelData[1] << 8) | pixelData[0];
        }
    }

    //f_close(&file);
}
