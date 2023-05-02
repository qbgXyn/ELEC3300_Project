#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcd.h"
#include "GUI/menu.h"
#include "GUI/bg.h"
#include "internal_bg.h"
#include "internal_map.h"
#include "Game/game.h"
#include "Game/Map.h"


uint8_t menuItemCount = 0; // Number of menu items, dynamically updated when you call additem(), set to 0 when change menu
MenuState menuState = MAIN_MENU;
uint8_t currentMenuItemIndex = 0;

char menuItemNameList[8][32]; // List of menu item names, dynamically updated when you call additem(), set to 0 when change menu


extern int highScore;
extern struct Game* game;


void MENU_DrawArrow(uint8_t menuItemIndex);
void MENU_ClearArrow(uint8_t menuItemIndex);

void MENU_ClearArrow(uint8_t menuItemIndex) {
	// Clear the arrow symbol ">" in front of the last selected menu item
    uint16_t arrow_y = MENU_ITEM_START_Y + menuItemIndex * MENU_ITEM_DISTANCE;
    LCD_DrawString(20, arrow_y, " ");
    BG_RestoreBackground(BG_GetBackGround(Game_GetMapBgType(game)), 20, arrow_y, WIDTH_EN_CHAR, HEIGHT_EN_CHAR);
}

void MENU_DrawArrow(uint8_t menuItemIndex)
{	// Add the arrow symbol ">" in front of the current selected menu item
    uint16_t arrow_y = MENU_ITEM_START_Y + menuItemIndex * MENU_ITEM_DISTANCE;
    LCD_DrawString(20, arrow_y, ">");
}

void MENU_SelectNextItem() {
    // Clear the arrow symbol ">" in front of the last selected menu item
    MENU_ClearArrow(currentMenuItemIndex);
    // Update the currently selected menu item
    currentMenuItemIndex = (currentMenuItemIndex + 1) % menuItemCount;
    // Add the arrow symbol ">" in front of the newly selected menu item
    MENU_DrawArrow(currentMenuItemIndex);
}



void MENU_AddItem(char* title) {
    LCD_DrawString(MENU_ITEM_X, MENU_ITEM_START_Y + menuItemCount * MENU_ITEM_DISTANCE, title);
    strcpy(menuItemNameList[menuItemCount], title);
    ++menuItemCount;
}

void MENU_DrawSubMenu(uint8_t submenuIndex) {
    //LCD_Clear(0, 0, 240, 320, 0); // Clear LCD
    BG_DrawBackground(BG_MAIN_MENU_DATA);
    switch (submenuIndex) {
        case MAP_MENU: // Choose map
            MENU_AddItem(TEXT_RANDOM_MAP_EASY);
            MENU_AddItem(TEXT_RANDOM_MAP_MEDIUM);
            MENU_AddItem(TEXT_RANDOM_MAP_HARD);
            MENU_AddItem(TEXT_CLASSIC);
            MENU_AddItem(TEXT_FOREST);
            MENU_AddItem(TEXT_DESERT);
            break;
        case ROOM_MENU: // Choose players
            MENU_AddItem("Waiting for player 2...");
            break;
        default:
            break;
    }
}

void MENU_DrawMainMenu(void)
{
    //LCD_Clear(0, 0, 240, 320, 0); // Clear LCD
	// Draw title and option text
    BG_DrawBackground(BG_MAIN_MENU_DATA);
    LCD_DrawString(60, 10, "Snake Game");
    MENU_AddItem("Single-player");
    MENU_AddItem("Multi-player");
    MENU_AddItem("Choose map");

    // Shows the selected map and number of players
    char buffer[32];

    // Map
    strcpy(buffer, "Map: ");
    strcat(buffer, game->map_name);
    LCD_DrawString(40, 240, buffer);
    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, "Highest score: ");
    itoa(highScore, buffer + strlen(buffer), 10);
    LCD_DrawString(40, 270, buffer);
}


void MENU_SwitchMenu(MenuState newMenuState) {
    menuState = newMenuState;
    menuItemCount = 0;
    currentMenuItemIndex = 0;
    memset(menuItemNameList, 0, sizeof(menuItemNameList));
    switch(menuState) {
        case MAIN_MENU:
            MENU_DrawMainMenu();
            break;
        case MAP_MENU:
            MENU_DrawSubMenu(MAP_MENU);
            break;
        case ROOM_MENU:
            MENU_DrawSubMenu(ROOM_MENU);
            break;
        default:
            break;
    }
    MENU_DrawArrow(0);
}


void MENU_DrawScoreBoard(struct Game* game) {
    // Show player score
    char scoreBuffer[32];
    snprintf(scoreBuffer, sizeof(scoreBuffer), "P1 Score: 0");
    LCD_DrawString(10, 2, scoreBuffer);

    if (Game_GetPlayerCount(game) == 2) {
        snprintf(scoreBuffer, sizeof(scoreBuffer), "P2 Score: 0");
        LCD_DrawString(140, 2, scoreBuffer);
    }
}

void MENU_SetState(MenuState state) {
    menuState = state;
}