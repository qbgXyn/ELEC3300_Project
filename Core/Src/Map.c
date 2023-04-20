#include "Map.h"
#include "Blob.h"
#include <stdlib.h>



struct Map* Map(uint8_t height, uint8_t width) {
	struct Blob*** map = (struct Blob***) malloc(width*sizeof(struct Blob**));
	for (int i = 0; i < width; ++i) {
		map[i] = (struct Blob**) malloc(height*sizeof(struct Blob*));
	}

	struct Map* m = malloc(sizeof(struct Map));
	m->map = map;
	m->height = height;
	m->width = width;
	return m;
}


// create a food blob and assign coordinate with it
void Spawn_Food_Randomly(struct Map* map) {
    uint8_t x = rand() % map->width;
    uint8_t y = rand() % map->height;
    while (map->map[x][y] != NULL) {
        x = rand() % map->width;
        y = rand() % map->height;
    }
    map->map[x][y] = Blob(map, 0, UP, FOOD, NULL, NULL, x, y);
}

void Spawn_Stone_Randomly(struct Map* map) {
    uint8_t x = rand() % map->width;
    uint8_t y = rand() % map->height;
    while (map->map[x][y] != NULL) {
        x = rand() % map->width;
        y = rand() % map->height;
    }
    map->map[x][y] = Blob(map, 0, UP, STONE, NULL, NULL, x, y);
}

void Spawn_Food(struct Map* map, uint8_t x, uint8_t y) {
    map->map[x][y] = Blob(map, 0, UP, FOOD, NULL, NULL, x, y);
}

void Spawn_Stone(struct Map* map, uint8_t x, uint8_t y) {
    map->map[x][y] = Blob(map, 0, UP, STONE, NULL, NULL, x, y);
}

bool Is_Food(struct Map* map, uint8_t x, uint8_t y) {
    if (map->map[x][y] == NULL) {
        return false;
    }
    return map->map[x][y]->type == FOOD;
}

bool Is_Stone(struct Map* map, uint8_t x, uint8_t y) {
    if (map->map[x][y] == NULL) {
        return false;
    }
    return map->map[x][y]->type == STONE;
}

bool Is_Body(struct Map* map, uint8_t x, uint8_t y) {
    if (map->map[x][y] == NULL) {
        return false;
    }
    return map->map[x][y]->type == BODY;
}

bool Is_Empty(struct Map* map, uint8_t x, uint8_t y) {
    return map->map[x][y] == NULL;
}




void Consume_Food(struct Map* map, uint8_t x, uint8_t y) {
    free(map->map[x][y]);
    map->map[x][y] = NULL;
}

// remove all non-snake blobs
void ClearMap(struct Map* map) {
    for (int i = 0; i < map->width; ++i) {
        for (int j = 0; j < map->height; ++j) {
            if (Is_Empty(map, i, j) == false && Is_Body(map, i, j) == false) {
                free(map->map[i][j]);
                map->map[i][j] = NULL;
            }
        }
    }
}

// fill empty slot with blob of type
void FillMap(struct Map* map, Type type) {
    for (int i = 0; i < map->width; ++i) {
        for (int j = 0; j < map->height; ++j) {
            if (Is_Empty(map, i, j) == true) {
                map->map[i][j] = Blob(map, 0, UP, type, NULL, NULL, i, j);
            }
        }
    }
}