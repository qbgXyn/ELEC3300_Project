#ifndef BG_H
#define BG_H
#define BG_IMAGE_WIDTH 320
#define BG_IMAGE_HEIGHT 240

enum {BG_MAIN, BG_FOREST, BG_DESERT, BG_CITY};
void BG_DrawBackground(const unsigned short bg[]);
static uint16_t bgImageData[BG_IMAGE_WIDTH * BG_IMAGE_HEIGHT]; // To store bg Image data
uint16_t GUI_GetBackgroundPixel(uint16_t x, uint16_t y);
void GUI_LoadBackgroundFromSDCard(const char *filename);

#endif