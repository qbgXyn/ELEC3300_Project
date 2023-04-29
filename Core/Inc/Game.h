#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <Player.h>
#include "Game_Data.h"

#define TICK 2
#define TIME_PER_TICK 1.0/TICK
#define MAX_PLAYER_COUNT 8
#define Player_0_COLOR 0x001F
#define Player_1_COLOR 0xFFE0
#define STONE_COLOR 0xF7DE
#define FOOD_COLOR 0xF800
#define EMPTY_COLOR 0x0000

typedef enum {SINGLE_PLAYER, MULTI_PLAYER} GameMode;


struct Map;


struct Game {
	struct Map* map; 
    char* map_name;
	int map_height; // with y 0 as top left and height - 1 as bottom right
	int map_width; // with x 0 as top left and width - 1 as bottom right
    int food_spawn_interval;
    struct Player** player_list;
    int player_count;
    bool is_running;
    GameMode game_mode;
    int local_player_id;

};


struct Game* Game(int player_count, int local_player_id);

void Game_Update(struct Game* game);

void Game_Render(struct Game* game);

void Game_Handle_Input(struct Game* game);

void Game_Start(struct Game* game);

void Game_Destroy(struct Game* game);

bool LoadMap(struct Game* game, char* map_name);

void Game_Add_Player(struct Game* game, struct Player* player);

void Game_Remove_Player(struct Game* game, struct Player* player);


#endif