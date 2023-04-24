#include <stdlib.h>
#include <stdint.h>
#include "Blob.h"

#ifndef SNAKE_H
#define SNAKE_H

struct Map;

struct Snake {
	struct Blob* head; // the head of the snake
	struct Blob* tail; // the tail of the snake
};

struct Snake* Snake(struct Map* map, uint8_t player_id, uint8_t x, uint8_t y, Direction dir, uint8_t length);


void Snake_Update(struct Map* map, struct Snake* snake);
void Snake_Grow(struct Map* map, struct Snake* snake);
void Snake_Kill(struct Map* map, struct Snake* snake);

void Snake_SetDirection(struct Snake* snake, Direction dir);


struct Blob* Snake_GetHead(struct Snake* snake);
uint8_t Snake_GetId(struct Snake* snake);
uint8_t Snake_GetLength(struct Snake* snake);


#endif