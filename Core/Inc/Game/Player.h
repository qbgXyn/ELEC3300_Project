#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "Game/Snake.h"

struct Map;


struct Game;


struct Player {
	int score;
    struct Snake *snake;
    bool is_alive;
    bool buttonPressed[4];
    bool is_ready;
    int id;
} ;


struct Player Player();


void Player_SetDirection(struct Player* player, Direction dir);

void Signal_Receive(struct Player* player, Direction dir);

bool Is_Alive(struct Player* player);
void Player_Delete(struct Map* map, struct Player* player);
void Player_Update(struct Map* map, struct Player* player);

int Player_Getid(struct Game* game);

bool Player_Spawn(struct Game* game, struct Player* player, int x, int y, Direction dir);
void Player_SpawnRandom(struct Game* game, struct Map* map, struct Player* player);

#endif