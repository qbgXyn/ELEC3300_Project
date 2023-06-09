#ifndef GAME_GUI_H
#define GAME_GUI_H

#include <stdint.h>

#define BTN_K1 0
#define BTN_K2 1

#define TEXT_GAME_WIN 0
#define TEXT_GAME_LOSE 1
#define TEXT_GAME_OVER 2

#include <stdbool.h>

void ShowExitConfirmation();
void ShowEndGameMessage(int end_game_status);

char* GetEndGameMessage(int end_game_status);
void ClearPromptBox();

#endif