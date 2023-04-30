#include "stdint.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcd.h"
#include "GUI/game_gui.h"



void GenerateGameMap(uint8_t selectedDifficulty, uint8_t map, uint8_t players)
{
    // // Clear LCD
    // // LCD_Clear(0, 0, 240, 320, 0);

    // // Draw the background according to the type of map chosen by the player
    // switch (map) {
    //     case 1: // Forest Map
    //         LCD_DrawForest();
    //         break;
    //     case 2: // City Map
    //         LCD_DrawDesert();
    //         break;
    //     case 3:
    //         LCD_Clear(0, 0, 240, 320, 0xFFFF);
    //         break;
    //     default:
    //         // Handle any other cases if necessary
    //         break;
    // }

    // // Show player score
    // char scoreBuffer[32];
    // snprintf(scoreBuffer, sizeof(scoreBuffer), "P1 Score: %d", player1Score);
    // LCD_DrawString(10, 2, scoreBuffer);

    // if (players == 2) {
    //     snprintf(scoreBuffer, sizeof(scoreBuffer), "P2 Score: %d", player2Score);
    //     LCD_DrawString(140, 2, scoreBuffer);
    // }

    // // Generate maps
    // srand(HAL_GetTick()); // Initialize the random number seed with the current system clock
    // for (uint8_t x = 0; x < GRID_SIZE_X; x++) {
    //     for (uint8_t y = 0; y < GRID_SIZE_Y; y++) {
    //     	// Initialize the random number seed with the current system clock
    //         if ((rand() % 100) < (difficulty * 3)) {
    //             gameMap[x][y] = 1;
    //             LCD_Fill(x * BLOCK_SIZE, SCORE_AREA_HEIGHT + y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, BLACK);
    //         } else {
    //             gameMap[x][y] = 0;
    //             // Draw a black square border
    //             LCD_DrawRectangle(x * BLOCK_SIZE, SCORE_AREA_HEIGHT + y * BLOCK_SIZE, (x * BLOCK_SIZE) + BLOCK_SIZE, (SCORE_AREA_HEIGHT + y * BLOCK_SIZE) + BLOCK_SIZE, BLACK);
    //         }
    //     }
    // }
}



// This function is mainly used to prompt the user for the K1 and K2 buttons in the game
// The first time you click K1 or K2 in the game, an info box will be displayed.
// and then
// K1 - Reload Map
// k2 - Main Menu
int8_t ShowExitConfirmation() {
		// Draw the game's prompt box
	    LCD_DrawRectangle(SCREEN_CENTER_X - (CONFIRM_BOX_WIDTH / 2), SCREEN_CENTER_Y - (CONFIRM_BOX_HEIGHT / 2),
	                      SCREEN_CENTER_X + (CONFIRM_BOX_WIDTH / 2), SCREEN_CENTER_Y + (CONFIRM_BOX_HEIGHT / 2), BLACK);
	    LCD_Fill(SCREEN_CENTER_X - (CONFIRM_BOX_WIDTH / 2) + 1, SCREEN_CENTER_Y - (CONFIRM_BOX_HEIGHT / 2) + 1,
	             CONFIRM_BOX_WIDTH - 2, CONFIRM_BOX_HEIGHT - 2, WHITE);

	    // Display prompt text
	    LCD_DrawString(SCREEN_CENTER_X - 60, SCREEN_CENTER_Y - 10, "K1: Reload Map");
	    LCD_DrawString(SCREEN_CENTER_X - 60, SCREEN_CENTER_Y + 10, "K2: Main Menu");

	    // Waiting for user input
	    uint8_t exitConfirmed = 0;
	    while (1) {
	        if (HAL_GPIO_ReadPin(K1_GPIO_Port, K1_Pin) == GPIO_PIN_SET) {
	            exitConfirmed = 1;
	            break;
	        }
	        if (HAL_GPIO_ReadPin(K2_GPIO_Port, K2_Pin) == GPIO_PIN_SET) {
	            exitConfirmed = 1;
	            break;
	        }
	    }

	    return exitConfirmed;
}