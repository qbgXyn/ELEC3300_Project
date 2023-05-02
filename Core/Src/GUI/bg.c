#include "lcd.h"
#include "GUI/bg.h"
//#include "ff.h"

#include "main.h"
// #include "ff.h" // Import the FatFS library for reading files from the SD card
#include "internal_bg.h"
#include <stdlib.h>

unsigned short bgImageData[BG_IMAGE_WIDTH * BG_IMAGE_HEIGHT];

void BG_DrawBackground(const unsigned short bg[])
{
    uint16_t x, y;
    uint16_t width = LCD_DispWindow_COLUMN; // Width
    uint16_t height = LCD_DispWindow_PAGE; // Height
    if (bg == NULL) {
        LCD_Clear (0, 0, 240, 320, BACKGROUND);
        return;
    }

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

inline uint16_t GUI_GetBackgroundPixel(const unsigned short* bg, uint16_t x, uint16_t y) {
    // Assume that the background image data is stored in an array named bgImageData
    // Please note that if your background image data is stored differently, modify this function accordingly
    return bg[y * BG_IMAGE_WIDTH + x];
}

// restore background image
// x : x coordinate of the top left corner of the area to be restored
// y : y coordinate of the top left corner of the area to be restored
// width : width of the area to be restored
// height : height of the area to be restored
void BG_RestoreBackground(const unsigned short* bg, uint16_t start_x, uint16_t start_y, uint16_t width, uint16_t height) {
    uint16_t x, y;
    if (bg == NULL) {
        LCD_Clear (start_x, start_y, width, height, BACKGROUND);
        return;
    }
    LCD_OpenWindow(start_x, start_y, width, height);
    LCD_Write_Cmd(CMD_SetPixel);

    for (y = start_y; y < start_y + height; y++)
    {
        for (x = start_x; x < start_x + width; x++)
        {
            LCD_Write_Data(bg[y * LCD_DispWindow_COLUMN + x]);
        }
    }
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
// const unsigned short* GetRandomBackground() {
//     const unsigned short* bg;
//     int random = rand() % BG_COUNTER;
//     switch (random) {
//         case BG_FOREST:
//             bg = BG_FOREST_DATA;
//             break;
//         case BG_DESERT:
//             bg = BG_DESERT_DATA;
//             break;
//         case BG_CITY:
//             bg = BG_CITY_DATA;
//             break;
//         default:
//             break;
//     }
//     return bg;
// }

const unsigned short* BG_GetBackGround(BackGroundType bg) {
    const unsigned short* bg_data;
    if (bg == BG_RANDOM) {
        bg = rand() % BG_COUNTER;
    }
    switch (bg) {
        case BG_FOREST:
            bg_data = BG_FOREST_DATA;
            break;
        case BG_DESERT:
            bg_data = BG_DESERT_DATA;
            break;
        case BG_CITY:
            bg_data = BG_CITY_DATA;
            break;
        case BG_MAIN:
            bg_data = BG_MAIN_MENU_DATA;
            break;
        case BG_CLASSIC:
            bg_data = NULL;
            break;
        default:
            bg_data = BG_MAIN_MENU_DATA;
            break;
    }
    return bg_data;
}
