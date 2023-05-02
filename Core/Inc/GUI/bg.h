#ifndef BG_H
#define BG_H
#define BG_IMAGE_WIDTH 320
#define BG_IMAGE_HEIGHT 240
#define BG_COUNTER 3

typedef enum {  BG_FOREST, BG_DESERT, BG_CITY, // can be loaded from SD card
                BG_CLASSIC, BG_MAIN, BG_UNKNOWN, BG_RANDOM,  // internal usage only
                BG_CUSTOM = 1000} BackGroundType; // can be loaded from SD card

uint16_t GUI_GetBackgroundPixel(uint16_t x, uint16_t y);

void BG_DrawBackground(const unsigned short bg[]);
static uint16_t bgImageData[BG_IMAGE_WIDTH * BG_IMAGE_HEIGHT]; // To store bg Image data
void GUI_LoadBackgroundFromSDCard(const char *filename);
void BG_DrawBackground(const unsigned short bg[]);
const unsigned short* GetRandomBackground();
const unsigned short* BG_GetBackGround(BackGroundType bg);

#endif