#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "Game/Player.h"
#include "Game/Game_Data.h"
#include "GUI/bg.h"
#include "ff.h"




typedef enum {SINGLE_PLAYER, MULTI_PLAYER} GameMode;

#define STONE_RATE_EASY 35
#define STONE_RATE_MEDIUM 20
#define STONE_RATE_HARD 10


struct Map;


struct Game {
	struct Map* map; 
    char map_name[NAME_LENGTH];
    int food_spawn_interval;
    struct Player player_self;
    struct Player player_other;
    bool is_running;
    GameMode game_mode;
    bool is_host;

};


struct Game* Game();

void Game_Update(struct Game* game);

void Game_Render(struct Game* game);

void Game_Start(struct Game* game);

void Game_End(struct Game* game);

// void Game_Destroy(struct Game* game);

void Game_Add_Player(struct Game* game, struct Player* player);

void Game_Remove_Player(struct Game* game, struct Player* player);

bool Game_IsHost(struct Game* game);
void Game_SetHost(struct Game* game, bool is_host);


FRESULT LoadFileMap(struct Game* game, char* map_name);
void LoadRandomMap(struct Game* game, int stone_rate);
bool LoadInternalMap(struct Game* game, char* map_name);
void Game_SetMap(struct Game* game);
bool Game_IsHost(struct Game* game);
int Game_GetPlayerCount(struct Game* game);
void Game_Pause(struct Game* game);

void Game_Resume(struct Game* game);

//private
void LoadDataToMap(struct Game* game, int x, int y, int data);
bool Game_IsRandomMap(struct Game* game);

BackGroundType Game_GetMapBgType(struct Game* game);


#endif
