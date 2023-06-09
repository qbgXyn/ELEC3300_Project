#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "Game/Blob.h"
#include "Game/Game_Data.h"
#include "GUI/bg.h"


/*
the size of the lcd screen is 240(width)*320(height)

the top left corner is (0,0)
the bottom right corner is (239,319)

we reserve 80 pixels for the score board
which means, the game area is 240(width)*240(height)

we divide the game area into 40*40 cells
which means, each cell is 6*6 pixels

when accessing the map, we use the coordinate of the cell
which means, the top left cell is (0,0)
the bottom right cell is (39,39)

the indexing of the map is map[width(x)][height(y)]
which means, the top left cell is map[0][0]
the bottom right cell is map[39][39]

the format of storing map, is stored in a 2d array of pointers to Blob
when loading map, it starts by filling the first(top) row, from left to right
then the second row, to the bottom
*/


struct Map {
	struct Blob* map_data[MAP_WIDTH][MAP_HEIGHT]; // map[width(x)][height(y)]
	bool map_differ[MAP_WIDTH][MAP_HEIGHT];
	BackGroundType map_bg;
	int food_spawn_interval; // in ms
};

struct Map* Map();



void Spawn_Food_Randomly(struct Map* map);

void Spawn_Stone_Randomly(struct Map* map);

void Set_Food(struct Map* map, int x, int y);
void Set_Stone(struct Map* map, int x, int y);
void Set_Empty(struct Map* map, int x, int y);
void Set_Body(struct Map* map, int x, int y, struct Blob* blob);

bool Is_Food(struct Map* map, int x, int y);
bool Is_Stone(struct Map* map, int x, int y);
bool Is_Body(struct Map* map, int x, int y);
bool Is_Empty(struct Map* map, int x, int y);
void Set_Differ(struct Map* map, int x, int y);

void Consume_Food(struct Map* map, int x, int y);

void ClearMap(struct Map* map);
void ClearCell(struct Map* map, int x, int y);
void Map_Delete(struct Map* map);

void FillMap(struct Map* map, Type type);


#endif