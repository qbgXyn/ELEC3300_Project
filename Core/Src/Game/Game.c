#include "Game/Game.h"
#include <stdio.h>
#include "Game/Map.h"
#include "Game/Game_Data.h"
#include "Game/Player.h"
#include "internal_map.h"
#include <string.h>
#include "GUI/bg.h"
#include "GUI/menu.h"
#include "lcd.h"

// init map is NULL first, set map name TEXT_CLASSIC
struct Game* Game(int player_count, int local_player_id) {
    struct Game* game = (struct Game*)malloc(sizeof(struct Game));
    game->map = NULL;
    strcpy(game->map_name, TEXT_CLASSIC);
    game->food_spawn_interval = DEFAULT_FOOD_SPAWN_INTERVAL;
    game->player_self = Player();
    game->player_self.is_alive = true;
    game->player_other = Player();
    game->is_host = false;
    game->is_running = false;
    game->game_mode = SINGLE_PLAYER;
    return game;
}

void Game_Update(struct Game* game) {
    if (game->is_running) {
        Player_Update(game->map, &game->player_self);
        if (game->game_mode == MULTI_PLAYER) {
            Player_Update(game->map, &game->player_other);
        }
    }
}

void Game_Render(struct Game* game) {
    if (game->map == NULL) {
        return;
    }
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            if (game->map->map_differ[x][y]) {
                game->map->map_differ[x][y] = false;
                // call render function
                if (Is_Empty(game->map, x, y)) {
                    // call something to recover background
                    LCD_DrawRectangle(x * BLOCK_SIZE, SCORE_AREA_HEIGHT + y * BLOCK_SIZE, (x * BLOCK_SIZE) + BLOCK_SIZE, (SCORE_AREA_HEIGHT + y * BLOCK_SIZE) + BLOCK_SIZE, EMPTY_COLOR);
                } else {
                    LCD_Fill(x * BLOCK_SIZE, SCORE_AREA_HEIGHT + y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, Blob_GetColor(game->map->map_data[x][y]));
                }
            }
        }
    }
}  


void Game_Start(struct Game* game) {
    Game_SetMap(game);
    
    // Clear LCD
    // LCD_Clear(0, 0, 240, 320, 0);

    // Draw the background according to the type of map chosen by the player
    BG_DrawBackground(BG_GetBackGround(game->map->map_bg));
    MENU_DrawScoreBoard(game);

    // generate all players and add them to the map
    Player_SpawnRandom(game, game->map, &game->player_self);
    if (game->game_mode == SINGLE_PLAYER) {
        Game_SetHost(game, true);
        game->player_self.id = PLAYER_1_ID;
    }else {
        Player_SpawnRandom(game, game->map, &game->player_other);
    }
    
    game->is_running = true;
}

//clear all neurtal stuff such as food and stone  by calling clearmap
//then kill all snakes
//then free all players
//then free game
// probably will not be used
// void Game_Destroy(struct Game* game) {
//     ClearMap(game->map);
//     Player_Delete(game->map, &game->player_self);
//     Player_Delete(game->map, &game->player_other);
//     // free(game->player_self);
//     // free(game->player_other);
//     Map_Delete(game->map);
//     free(game);
    
// }

// load map from file
// also update MAP_WIDTH, MAP_HEIGHT, game->food_spawn_interval
// file format:
// line 1: food_spawn_interval
// line 2: map background (0:forest, 1:desert, 2:city, 1000:custom)
// line 3: map data (width*height) (0: empty, 1: food, 2: stone) (row by row) (no space) (newline)
// example:
// 1000
// 2
// 000
// 111
// 222
// 000
// return true if success, false if fail
bool LoadFileMap(struct Game* game, char* map_name) {
    FILE* file = fopen(map_name, "r");
    if (file == NULL) {
        return false;
    }
    fscanf(file, "%d", &game->food_spawn_interval);
    int bg;
    fscanf(file, "%d", &bg);
    if ((bg > BG_COUNTER && bg != BG_CUSTOM) || bg < 0) {
        fclose(file);
        return false;
    }
    if (game->map != NULL) {
        Map_Delete(game->map);
    }
    game->map = Map(MAP_WIDTH, MAP_HEIGHT);
    game->map->map_bg = bg;
    for(int x = 0; x < MAP_WIDTH; x++) {
        for(int y = 0; y < MAP_HEIGHT; y++) {
            int data;
            fscanf(file, "%d", &data);
            LoadDataToMap(game, x, y, data);
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
    if (strcmp(map_name, TEXT_CLASSIC) == 0) {
        if (game->map != NULL) {
        Map_Delete(game->map);
        }
        game->map = Map(MAP_WIDTH, MAP_HEIGHT);
        game->map->map_bg = BG_CLASSIC;
        for(int x = 0; x < MAP_WIDTH; x++) {
            for(int y = 0; y < MAP_HEIGHT; y++) {
                LoadDataToMap(game, x, y, INTERNAL_MAP_CLASSIC[x][y]);
            }
        }
        return true;
    }
    // temp ugly code
    // should combine map_name, map_bg together 
    if(strcmp(map_name, TEXT_FOREST) == 0) {
        if (game->map != NULL) {
        Map_Delete(game->map);
        }
        game->map = Map(MAP_WIDTH, MAP_HEIGHT);
        game->map->map_bg = BG_FOREST;
        for(int x = 0; x < MAP_WIDTH; x++) {
            for(int y = 0; y < MAP_HEIGHT; y++) {
                LoadDataToMap(game, x, y, INTERNAL_MAP_FOREST[x][y]);
            }
        }
        return true;
    }
    if(strcmp(map_name, TEXT_DESERT) == 0) {
        if (game->map != NULL) {
        Map_Delete(game->map);
        }
        game->map = Map(MAP_WIDTH, MAP_HEIGHT);
        game->map->map_bg = BG_DESERT;
        for(int x = 0; x < MAP_WIDTH; x++) {
            for(int y = 0; y < MAP_HEIGHT; y++) {
                LoadDataToMap(game, x, y, INTERNAL_MAP_DESERT[x][y]);
            }
        }
        return true;
    }
    return false;
}

// stone_rate: for every cell, it has 1/stone_rate chance to be a stone
void LoadRandomMap(struct Game* game, int stone_rate) {
    srand(HAL_GetTick()); // Initialize the random number seed with the current system clock
    if (game->map != NULL) {
        Map_Delete(game->map);
    }
    game->map = Map(MAP_WIDTH, MAP_HEIGHT);
    for(int x = 0; x < MAP_WIDTH; x++) {
        for(int y = 0; y < MAP_HEIGHT; y++) {
            int data = rand() % stone_rate == 0 ? STONE : EMPTY;
            LoadDataToMap(game, x, y, data);
        }
    }
    // set background
    game->map->map_bg = BG_RANDOM;
}

// set up the map based on name
void Game_SetMap(struct Game* game)
{
    if (strcmp(game->map_name, TEXT_RANDOM_MAP_EASY) == 0) {
        LoadRandomMap(game, STONE_RATE_EASY);
    }else if (strcmp(game->map_name, TEXT_RANDOM_MAP_MEDIUM) == 0) {
        LoadRandomMap(game, STONE_RATE_MEDIUM);
    }else if (strcmp(game->map_name, TEXT_RANDOM_MAP_HARD) == 0) {
        LoadRandomMap(game, STONE_RATE_HARD);
    }else if (strcmp(game->map_name, TEXT_CLASSIC) == 0) {
        LoadInternalMap(game, TEXT_CLASSIC);
    }else if (strcmp(game->map_name, TEXT_FOREST) == 0) {
        LoadInternalMap(game, TEXT_FOREST);
    }else if (strcmp(game->map_name, TEXT_DESERT) == 0) {
        LoadInternalMap(game, TEXT_DESERT);
    }else {
        LoadFileMap(game, strcat(game->map_name, ".txt"));
    }
}

bool Game_IsRandomMap(struct Game* game) {
    return strcmp(game->map_name, TEXT_RANDOM_MAP_EASY) == 0 ||
        strcmp(game->map_name, TEXT_RANDOM_MAP_MEDIUM) == 0 ||
        strcmp(game->map_name, TEXT_RANDOM_MAP_HARD) == 0;
}

void LoadDataToMap(struct Game* game, int x, int y, int data) {
    if (data == FOOD) {
        Set_Food(game->map, x, y);
    }
    else if (data == STONE) {
        Set_Stone(game->map, x, y);
    }
    else {
        Set_Empty(game->map, x, y);
    }
}


bool Game_IsHost(struct Game* game) {
    return game->is_host;
}


void Game_SetHost(struct Game* game, bool is_host) {
    game->is_host = is_host;
}


int Game_GetPlayerCount(struct Game* game) {
    return game->player_other.is_alive ? 2 : 1;
}