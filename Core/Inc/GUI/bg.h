#ifndef BG_H
#define BG_H

#define BG_IMAGE_WIDTH 240
#define BG_IMAGE_HEIGHT 320
#define BG_COUNTER 3

typedef enum {  BG_FOREST, BG_DESERT, BG_CITY, // can be loaded from SD card with type only, no need to load data
                BG_CLASSIC, BG_MAIN, BG_UNKNOWN, BG_RANDOM,  // internal usage only
                BG_CUSTOM = 1000} BackGroundType; // can be loaded from SD card with type and data

extern unsigned short bgImageData[BG_IMAGE_WIDTH * BG_IMAGE_HEIGHT]; // To store bg Image data

uint16_t GUI_GetBackgroundPixel(const unsigned short* bg, uint16_t x, uint16_t y);

void BG_DrawBackground(const unsigned short bg[]);
void BG_RestoreBackground(const unsigned short* bg, uint16_t x, uint16_t y, uint16_t width, uint16_t height);

void GUI_LoadBackgroundFromSDCard(const char *filename);
const unsigned short* GetRandomBackground();
const unsigned short* BG_GetBackGround(BackGroundType bg);

#endif