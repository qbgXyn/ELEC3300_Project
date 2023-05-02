#include "Game/Map.h"
#include "Game/Blob.h"
#include <stdlib.h>
#include <string.h>




struct Map* Map() {
    
    struct Map* m = malloc(sizeof(struct Map));
    memset(m->map_differ, true, sizeof(m->map_differ));
    memset(m->map_data, 0, sizeof(m->map_data));
    m->map_bg = BG_CLASSIC;
	return m;
}


// create a food blob and assign coordinate with it
void Spawn_Food_Randomly(struct Map* map) {
    srand(HAL_GetTick());
    int x = rand() % MAP_WIDTH;
    int y = rand() % MAP_HEIGHT;
    while (Is_Empty(map, x, y) == false) {
        x = rand() % MAP_WIDTH;
        y = rand() % MAP_HEIGHT;
    }
    Set_Food(map, x, y);
}

void Spawn_Stone_Randomly(struct Map* map) {
    srand(HAL_GetTick());
    int x = rand() % MAP_WIDTH;
    int y = rand() % MAP_HEIGHT;
    while (Is_Empty(map, x, y) == false) {
        x = rand() % MAP_WIDTH;
        y = rand() % MAP_HEIGHT;
    }
    Set_Stone(map, x, y);
}

void Set_Food(struct Map* map, int x, int y) {
    map->map_data[x][y] = Blob(NEURTAL_PLAYER_ID, UP, FOOD, NULL, NULL, x, y);
    map->map_differ[x][y] = true;
}

void Set_Stone(struct Map* map, int x, int y) {
    map->map_data[x][y] = Blob(NEURTAL_PLAYER_ID, UP, STONE, NULL, NULL, x, y);
    map->map_differ[x][y] = true;
}

void Set_Empty(struct Map* map, int x, int y) {
    map->map_data[x][y] = NULL;
    map->map_differ[x][y] = true;
}

void Set_Body(struct Map* map, int x, int y, struct Blob* blob) {
    map->map_data[x][y] = blob;
    map->map_differ[x][y] = true;
}

bool Is_Food(struct Map* map, int x, int y) {
    if (map->map_data[x][y] == NULL) {
        return false;
    }
    return map->map_data[x][y]->type == FOOD;
}

bool Is_Stone(struct Map* map, int x, int y) {
    if (map->map_data[x][y] == NULL) {
        return false;
    }
    return map->map_data[x][y]->type == STONE;
}

bool Is_Body(struct Map* map, int x, int y) {
    if (map->map_data[x][y] == NULL) {
        return false;
    }
    return map->map_data[x][y]->type == BODY;
}

bool Is_Empty(struct Map* map, int x, int y) {
    return map->map_data[x][y] == NULL || map->map_data[x][y]->type == EMPTY;
}


void Set_Differ(struct Map* map, int x, int y) {
    map->map_differ[x][y] = true;
}


// remove all blobs
void ClearMap(struct Map* map) {
    for (int x = 0; x < MAP_WIDTH; ++x) {
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            ClearCell(map, x, y);
            map->map_differ[x][y] = true;
        }
    }
}

// remember to clear all snakes before deleting map
void Map_Delete(struct Map* map) {
    ClearMap(map);
    for (int i = 0; i < MAP_WIDTH; ++i) {
        free(map->map_data[i]);
    }
    free(map->map_data);
    free(map);
}

void ClearCell(struct Map* map, int x, int y) {
    if (Is_Empty(map, x, y) == false) {
        free(map->map_data[x][y]);
        map->map_data[x][y] = NULL;
        map->map_differ[x][y] = true;
    }
}

// fill empty slot with blob of type
void FillMap(struct Map* map, Type type) {
    for (int x = 0; x < MAP_WIDTH; ++x) {
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            if (Is_Empty(map, x, y) == true) {
                map->map_data[x][y] = Blob(0, UP, type, NULL, NULL, x, y);
                map->map_differ[x][y] = true;
            }
        }
    }
}