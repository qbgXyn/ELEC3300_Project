#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "Blob.h"
#include "Game_Data.h"


struct Map {
	struct Blob*** map_data; // map[width(x)][height(y)]
	bool map_differ[MAP_WIDTH*MAP_HEIGHT];
	uint8_t height; // with y 0 as top left and height - 1 as bottom right
	uint8_t width; // with x 0 as top left and width - 1 as bottom right
	int food_spawn_interval; // in ms
};

struct Map* Map(uint8_t height, uint8_t width);



void Spawn_Food_Randomly(struct Map* map);

void Spawn_Stone_Randomly(struct Map* map);

void Set_Food(struct Map* map, uint8_t x, uint8_t y);
void Set_Stone(struct Map* map, uint8_t x, uint8_t y);

bool Is_Food(struct Map* map, uint8_t x, uint8_t y);
bool Is_Stone(struct Map* map, uint8_t x, uint8_t y);
bool Is_Body(struct Map* map, uint8_t x, uint8_t y);
bool Is_Empty(struct Map* map, uint8_t x, uint8_t y);

void Consume_Food(struct Map* map, uint8_t x, uint8_t y);

void ClearMap(struct Map* map);
void ClearCell(struct Map* map, uint8_t x, uint8_t y);
void Map_Delete(struct Map* map);

void FillMap(struct Map* map, Type type);


#endif