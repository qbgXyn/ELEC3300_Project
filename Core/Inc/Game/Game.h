#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "Game/Player.h"
#include "Game/Game_Data.h"



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

void Game_Start(struct Game* game);

void Game_Destroy(struct Game* game);

void Game_Add_Player(struct Game* game, struct Player* player);

void Game_Remove_Player(struct Game* game, struct Player* player);


bool LoadMap(struct Game* game, char* map_name);
bool LoadRandomMap(struct Game* game, int stone_rate);
bool LoadInternalMap(struct Game* game, char* map_name);

//private
void LoadDataToMap(struct Game* game, int x, int y, int data);


#endif