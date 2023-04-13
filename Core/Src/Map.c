#include "Map.h"
#include "Blob.h"
#include <stdlib.h>


struct Map* Map(uint8_t height, uint8_t width, int food_spawn_interval) {
	struct Blob*** map = (struct Blob***) malloc(width*sizeof(struct Blob**));
	for (int i = 0; i < width; ++i) {
		map[i] = (struct Blob**) malloc(height*sizeof(struct Blob*));
	}

	struct Map* m = malloc(sizeof(struct Map));
	m->map = map;
	m->height = height;
	m->width = width;
	m->food_spawn_interval = food_spawn_interval;
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

void Spawn_Stone(struct Map* map, uint8_t x, uint8_t y) {
    map->map[x][y] = Blob(map, 0, UP, STONE, NULL, NULL, x, y);
}