#include "lcd.h"
#include "GUI/bg.h"

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
