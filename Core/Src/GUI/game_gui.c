#include "stdint.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcd.h"
#include "GUI/game_gui.h"
#include "Game/Map.h"
#include "Game/Game.h"

extern struct Game* game;

void DrawPromptBox() {
    // Draw the game's prompt box x45, y130, x195, y190 
    LCD_DrawRectangle(SCREEN_CENTER_X - (CONFIRM_BOX_WIDTH / 2), SCREEN_CENTER_Y - (CONFIRM_BOX_HEIGHT / 2),
                        SCREEN_CENTER_X + (CONFIRM_BOX_WIDTH / 2), SCREEN_CENTER_Y + (CONFIRM_BOX_HEIGHT / 2), BLACK);
    LCD_Fill(SCREEN_CENTER_X - (CONFIRM_BOX_WIDTH / 2) + 1, SCREEN_CENTER_Y - (CONFIRM_BOX_HEIGHT / 2) + 1,
                CONFIRM_BOX_WIDTH - 2, CONFIRM_BOX_HEIGHT - 2, WHITE);
}

// clear by finding boundary
// then re-render the background image to the screen
// and also re-render the menu
// and also re-render the game
void ClearPromptBox() {
    int x = (SCREEN_CENTER_X - (CONFIRM_BOX_WIDTH / 2)) / BLOCK_SIZE;
    int y = (SCREEN_CENTER_Y - (CONFIRM_BOX_HEIGHT / 2) - SCORE_AREA_HEIGHT) / BLOCK_SIZE;
    int width = CONFIRM_BOX_WIDTH / BLOCK_SIZE + 1;
    int height = CONFIRM_BOX_HEIGHT / BLOCK_SIZE + 1;
    for (int j = y; j < y + height; j++) {
        for(int i = x; i < x + width; i++) {
            Set_Differ(game->map, i, j);
        }
    }
}




// This function is mainly used to prompt the user for the K1 and K2 buttons in the game
// The first time you click K1 or K2 in the game, an info box will be displayed.
// and then
// K1 - Reload Map
// k2 - Main Menu
void ShowExitConfirmation() {
		// Draw the game's prompt box
	    DrawPromptBox();

	    // Display prompt text
	    LCD_DrawString(SCREEN_CENTER_X - 60, SCREEN_CENTER_Y - 10, "K1: Resume");
	    LCD_DrawString(SCREEN_CENTER_X - 60, SCREEN_CENTER_Y + 10, "K2: Main Menu");
}

char* GetEndGameMessage(int end_game_status) {
    switch (end_game_status) {
        case TEXT_GAME_WIN:
            return "You Win!";
        case TEXT_GAME_LOSE:
            return "You Lose!";
        case TEXT_GAME_OVER:
            return "Game over!";
        default:
            return "Unknown";
    }
}

void ShowEndGameMessage(int end_game_status) {
		// Draw the game's prompt box
	    DrawPromptBox();

	    // Display prompt text
	    LCD_DrawString(SCREEN_CENTER_X - 60, SCREEN_CENTER_Y - 10, GetEndGameMessage(end_game_status));
	    LCD_DrawString(SCREEN_CENTER_X - 60, SCREEN_CENTER_Y + 10, "[K2] Main Menu");
}