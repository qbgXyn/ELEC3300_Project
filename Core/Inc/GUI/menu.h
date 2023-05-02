#ifndef MENU_H
#define MENU_H

#define MENU_ITEM_COUNT 3
#define SUBMENU_ITEM_COUNT 3
#define MENU_ITEM_DISTANCE 30
#define MENU_ITEM_START_Y 60
#define MENU_ITEM_X 40

#define INDEX_SINGLE_PLAYER 0
#define INDEX_MULTI_PLAYER 1
#define INDEX_CHOOSE_MAP 2

#include "Game/Game.h"


typedef enum {
    MAIN_MENU,
    MAP_MENU,
    ROOM_MENU,
	IN_GAME,
    END_GAME
} MenuState;


// ELEC3300 - Project
void MENU_SelectNextItem();
void MENU_AddItem(char* title);
void MENU_DrawSubmenu(uint8_t submenuIndex);
void MENU_DrawMainMenu(void);
void MENU_SwitchMenu(MenuState newMenuState);
void MENU_DrawScoreBoard(struct Game* game);
void MENU_SetState(MenuState state);


#endif