#include "GUI/event_handler.h"
#include "GUI.h"
#include "GUI/game_gui.h"
#include "lcd.h"
#include "GUI/bg.h"
#include "GUI/Menu.h"
#include "Game/Game.h"
#include <string.h>

extern uint8_t menuItemCount;
extern uint8_t currentMenuItemIndex;
extern char menuItemNameList[8][32];

extern MenuState menuState;


extern struct Game* game;

extern bool exitMenuDisplayed;

void handle_map_selection() {
  strcpy(game->map_name, menuItemNameList[currentMenuItemIndex]);
}

void handle_K1_pressed_InGame() {
    if (exitMenuDisplayed == false) {
        exitMenuDisplayed = true;
        Game_Pause(game);
        ShowExitConfirmation();
    }else {
        ClearPromptBox();
        Game_Resume(game);
        exitMenuDisplayed = false;
    }
}

void handle_K2_pressed_InGame() {
    if (exitMenuDisplayed == false) {
        exitMenuDisplayed = true;
        Game_Pause(game);
        ShowExitConfirmation();
    }else {
        Game_End(game);
        MENU_SetState(MAIN_MENU);
        MENU_SwitchMenu(menuState);
        exitMenuDisplayed = false;
    }
}

void handle_K2_pressed_EndGame() {
    menuState = MAIN_MENU;
    MENU_SwitchMenu(menuState);
}

void handle_K2_pressed_MainMenu() {
    switch (currentMenuItemIndex) {
        case INDEX_SINGLE_PLAYER:
              menuState = IN_GAME;
              MENU_SwitchMenu(menuState);
              Game_Start(game);
              break;
        case INDEX_MULTI_PLAYER:
              menuState = ROOM_MENU;
              MENU_SwitchMenu(menuState);
              break;
        case INDEX_CHOOSE_MAP:
              menuState = MAP_MENU;
              MENU_SwitchMenu(menuState);
              break;
        default:
              break;
    }
}

void handle_Map_Menu_NextPage() {
    
}

void handle_K2_pressed_SubMenu() {
    switch (menuState) {
        case MAP_MENU:
              handle_map_selection();
              break;
        case ROOM_MENU:
              break;
        default:
              break;
    }
    menuState = MAIN_MENU;
    MENU_SwitchMenu(menuState);
}