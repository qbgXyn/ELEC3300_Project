#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "Snake.h"
struct Map;


struct Player {
	int score;
    struct Snake *snake;
    bool is_alive;
    bool buttonPressed[4];
    bool is_ready;
} ;


struct Player* Player();


void Signal_Input(struct Player* player, Direction dir);

void Signal_Receive(struct Player* player, Direction dir);

bool Is_Alive(struct Player* player);


#endif