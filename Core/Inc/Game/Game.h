#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "Game/Player.h"
#include "Game/Game_Data.h"



typedef enum {SINGLE_PLAYER, MULTI_PLAYER} GameMode;

#define STONE_RATE_EASY 40
#define STONE_RATE_MEDIUM 30
#define STONE_RATE_HARD 20


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


struct Game* Game(int player_count, int local_player_id);

void Game_Update(struct Game* game);

void Game_Render(struct Game* game);

void Game_Start(struct Game* game);

// void Game_Destroy(struct Game* game);

void Game_Add_Player(struct Game* game, struct Player* player);

void Game_Remove_Player(struct Game* game, struct Player* player);

bool Game_IsHost(struct Game* game);
void Game_SetHost(struct Game* game, bool is_host);


bool LoadFileMap(struct Game* game, char* map_name);
void LoadRandomMap(struct Game* game, int stone_rate);
bool LoadInternalMap(struct Game* game, char* map_name);
void Game_SetMap(struct Game* game);
bool Game_IsHost(struct Game* game);
int Game_GetPlayerCount(struct Game* game);

//private
void LoadDataToMap(struct Game* game, int x, int y, int data);
bool Game_IsRandomMap(struct Game* game);


#endif