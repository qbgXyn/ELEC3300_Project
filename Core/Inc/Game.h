#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <Player.h>

#ifndef GAME_H
#define GAME_H

#define TICK 20
#define TIME_PER_TICK 1.0/TICK
#define MAX_PLAYER_COUNT 8

typedef enum {SINGLE_PLAYER, MULTI_PLAYER} GameMode;

typedef enum {BLACK, RED, BLUE, CYAN, GREEN, MAGENTA, YELLOW, PINK, GRAY} Player_Color;

struct Map;


struct Game {
	struct Map* map; 
    char* map_name;
	int map_height; // with y 0 as top left and height - 1 as bottom right
	int map_width; // with x 0 as top left and width - 1 as bottom right
    int food_spawn_interval;
    struct Player** player_list;
    int player_count;
    int local_player_id;
    bool is_running;
    GameMode game_mode;
    bool is_host;

};


struct Game* Game(int player_count, int local_player_id);

void Game_Update(struct Game* game);

void Game_Render(struct Game* game);

void Game_Handle_Input(struct Game* game);

void Game_Start(struct Game* game);

void Game_Destroy(struct Game* game);

bool LoadMap(struct Game* game, char* map_name);


#endif