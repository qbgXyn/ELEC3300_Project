#include "lcd.h"
#include "GUI/bg.h"
#include "internal_bg.h"
#include <stdlib.h>

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
        default:
            bg_data = NULL;
            break;
    }
    return bg_data;
}
