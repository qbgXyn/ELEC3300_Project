#include <stdlib.h>
#include <stdint.h>

#ifndef MAP_H
#define MAP_H

struct Blob;
struct Map {
	struct Blob*** map;
	uint8_t height; // with y 0 as top left and height - 1 as bottom right
	uint8_t width; // with x 0 as top left and width - 1 as bottom right
	int food_spawn_interval; // in ms
};

struct Map* Map(uint8_t height, uint8_t width, int food_spawn_interval);



void Spawn_Food_Randomly(struct Map* map);

void Spawn_Stone_Randomly(struct Map* map);

void Spawn_Stone(struct Map* map, uint8_t x, uint8_t y);


#endif