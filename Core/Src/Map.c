#include "Map.h"
#include "Blob.h"
#include <stdlib.h>
#include <string.h>



struct Map* Map(uint8_t height, uint8_t width) {
    struct Map* m = malloc(sizeof(struct Map));
	struct Blob*** map = (struct Blob***) malloc(width*sizeof(struct Blob**));
    memset(m->map_differ, 0, MAP_WIDTH*MAP_HEIGHT);
	for (int i = 0; i < width; ++i) {
		map[i] = (struct Blob**) malloc(height*sizeof(struct Blob*));
	}
    FillMap(m, EMPTY);

	m->map_data = map;
	m->height = height;
	m->width = width;
	return m;
}


// create a food blob and assign coordinate with it
void Spawn_Food_Randomly(struct Map* map) {
    uint8_t x = rand() % map->width;
    uint8_t y = rand() % map->height;
    while (map->map_data[x][y] != NULL) {
        x = rand() % map->width;
        y = rand() % map->height;
    }
    Set_Food(map, x, y);
}

void Spawn_Stone_Randomly(struct Map* map) {
    uint8_t x = rand() % map->width;
    uint8_t y = rand() % map->height;
    while (map->map_data[x][y] != NULL) {
        x = rand() % map->width;
        y = rand() % map->height;
    }
    Set_Stone(map, x, y);
}

void Set_Food(struct Map* map, uint8_t x, uint8_t y) {
    map->map_data[x][y] = Blob(0, UP, FOOD, NULL, NULL, x, y);
    map->map_differ[x + y*map->width] = true;
}

void Set_Stone(struct Map* map, uint8_t x, uint8_t y) {
    map->map_data[x][y] = Blob(0, UP, STONE, NULL, NULL, x, y);
    map->map_differ[x + y*map->width] = true;
}

void Set_Empty(struct Map* map, uint8_t x, uint8_t y) {
    map->map_data[x][y] = NULL;
    map->map_differ[x + y*map->width] = true;
}

void Set_Body(struct Map* map, uint8_t x, uint8_t y, struct Blob* blob) {
    map->map_data[x][y] = blob;
    map->map_differ[x + y*map->width] = true;
}

bool Is_Food(struct Map* map, uint8_t x, uint8_t y) {
    if (map->map_data[x][y] == NULL) {
        return false;
    }
    return map->map_data[x][y]->type == FOOD;
}

bool Is_Stone(struct Map* map, uint8_t x, uint8_t y) {
    if (map->map_data[x][y] == NULL) {
        return false;
    }
    return map->map_data[x][y]->type == STONE;
}

bool Is_Body(struct Map* map, uint8_t x, uint8_t y) {
    if (map->map_data[x][y] == NULL) {
        return false;
    }
    return map->map_data[x][y]->type == BODY;
}

bool Is_Empty(struct Map* map, uint8_t x, uint8_t y) {
    return map->map_data[x][y] == NULL;
}


// remove all non-snake blobs
void ClearMap(struct Map* map) {
    for (int x = 0; x < map->width; ++x) {
        for (int y = 0; y < map->height; ++y) {
            ClearCell(map, x, y);
            map->map_differ[x + y*map->width] = true;
        }
    }
}

void Map_Delete(struct Map* map) {
    ClearMap(map);
    for (int i = 0; i < map->width; ++i) {
        free(map->map_data[i]);
    }
    free(map->map_data);
    free(map);
}

void ClearCell(struct Map* map, uint8_t x, uint8_t y) {
    if (Is_Empty(map, x, y) == false && Is_Body(map, x, y) == false) {
        free(map->map_data[x][y]);
        map->map_data[x][y] = NULL;
        map->map_differ[x + y*map->width] = true;
    }
}

// fill empty slot with blob of type
void FillMap(struct Map* map, Type type) {
    for (int x = 0; x < map->width; ++x) {
        for (int y = 0; y < map->height; ++y) {
            if (Is_Empty(map, x, y) == true) {
                map->map_data[x][y] = Blob(0, UP, type, NULL, NULL, x, y);
                map->map_differ[x + y*map->width] = true;
            }
        }
    }
}