#include "Game.h"
#include <stdio.h>
#include "Map.h"
#include "Game_Data.h"
#include "Player.h"
#include "internal_map.h"

// init map is NULL first, set map name "Random"
struct Game* Game(int player_count, int local_player_id) {
    struct Game* game = (struct Game*)malloc(sizeof(struct Game));
    game->map = NULL;
    game->map_name = "Random";
    game->map_height = MAP_HEIGHT;
    game->map_width = MAP_WIDTH;
    game->food_spawn_interval = DEFAULT_FOOD_SPAWN_INTERVAL;
    game->player_list = (struct Player**)malloc(sizeof(struct Player*) * MAX_PLAYER_COUNT);
    game->player_count = player_count;
    game->local_player_id = local_player_id;
    game->is_running = false;
    game->game_mode = SINGLE_PLAYER;
    return game;
}

void Game_Update(struct Game* game) {
    if (game->is_running) {
        for (int i = 0; i < game->player_count; i++) {
            if (Is_Alive(game->player_list[i])) {
                Game_Handle_Input(game);
                Snake_Update(game->map, game->player_list[i]->snake);
            }
        }
    }
}

void Game_Render(struct Game* game) {
    int x, y;
    for(int i = 0; i < MAP_WIDTH*MAP_HEIGHT; ++i) {
        if (game->map->map_differ[i]) {
            game->map->map_differ[i] = false;
            x = i % MAP_WIDTH;
            y = i / MAP_WIDTH;
            // call render function
        }
    }
}  

void Game_Handle_Input(struct Game* game) {
    if (game->is_running) {
        for (int i = 0; i < game->player_count; i++) {
            if (Is_Alive(game->player_list[i])) {
                if (game->player_list[i]->buttonPressed[UP]) {
                    Snake_SetDirection(game->player_list[i]->snake, UP);
                }
                else if (game->player_list[i]->buttonPressed[DOWN]) {
                    Snake_SetDirection(game->player_list[i]->snake, DOWN);
                }
                else if (game->player_list[i]->buttonPressed[LEFT]) {
                    Snake_SetDirection(game->player_list[i]->snake, LEFT);
                }
                else if (game->player_list[i]->buttonPressed[RIGHT]) {
                    Snake_SetDirection(game->player_list[i]->snake, RIGHT);
                }
            }
        }
    }
}

void Game_Start(struct Game* game) {
    game->is_running = true;
}

//clear all neurtal stuff such as food and stone  by calling clearmap
//then kill all snakes
//then free all players
//then free game
void Game_Destroy(struct Game* game) {
    for (int i = 0; i < MAX_PLAYER_COUNT; i++) {
        if (game->player_list[i] != NULL && Is_Alive(game->player_list[i])) {
            Snake_Delete(game->map, game->player_list[i]->snake);
            free(game->player_list[i]);
        }
    }
    Map_Delete(game->map);
    free(game->player_list);
    free(game);
    
}

// load map from file
// also update game->map_width, game->map_height, game->food_spawn_interval
// file format:
// line 1: food_spawn_interval
// line 2: map data (width*height) (0: empty, 1: food, 2: stone) (row by row) (no space) (no newline)
// example:
// 1000
// 000
// 111
// 222
// 000
// return true if success, false if fail
bool LoadMap(struct Game* game, char* map_name) {
    FILE* file = fopen(map_name, "r");
    if (file == NULL) {
        return false;
    }
    fscanf(file, "%d", &game->food_spawn_interval);
    game->map = Map(game->map_width, game->map_height);
    for (int i = 0; i < game->map_height; i++) {
        for (int j = 0; j < game->map_width; j++) {
            int type;
            fscanf(file, "%d", &type);
            if (type == FOOD) {
                Set_Food(game->map, j, i);
            }
            else if (type == STONE) {
                Set_Stone(game->map, j, i);
            }
            else {
                Set_Empty(game->map, j, i);
            }
        }
    }
    fclose(file);
    return true;
}

// load map from internal map in code in the format internal_map.h
// in internal_map.h, there is a 2D array of int
// in variable internal_map_<map_name>
// also update game->food_spawn_interval
// return true if success, false if fail
//
// data of internal map are stored in a 2D array of int
// 0: empty, 1: food, 2: stone
// example:
// int internal_map_example[MAP_HEIGHT][MAP_WIDTH] = {
//     {0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0},
//};
// return true if success, false if fail

bool LoadInternalMap(struct Game* game, char* map_name) {
    if (strcmp(map_name, "classic") == 0) {
        game->map = Map(game->map_width, game->map_height);
        for (int i = 0; i < game->map_height; i++) {
            for (int j = 0; j < game->map_width; j++) {
                if (classic[i][j] == STONE) {
                    Set_Stone(game->map, j, i);
                }
                else {
                    Set_Empty(game->map, j, i);
                }
            }
        }
    }

}