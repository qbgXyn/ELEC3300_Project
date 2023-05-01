#ifndef BG_H
#define BG_H

#define BG_COUNTER 3
typedef enum {  BG_FOREST, BG_DESERT, BG_CITY, // can be loaded from SD card
                BG_CLASSIC, BG_MAIN, BG_UNKNOWN, BG_RANDOM,  // internal usage only
                BG_CUSTOM = 1000} BackGroundType; // can be loaded from SD card

void BG_DrawBackground(const unsigned short bg[]);
const unsigned short* GetRandomBackground();

const unsigned short* BG_GetBackGround(BackGroundType bg);


#endif