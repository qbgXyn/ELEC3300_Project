#include <stdlib.h>
#include <stdint.h>

#ifndef SNAKE_H
#define SNAKE_H

struct Map;

struct Snake {
	struct Blob* head; // the head of the snake
	struct Blob* tail; // the tail of the snake
};

struct Snake* Snake(struct Map* map, uint8_t player_id, uint8_t x, uint8_t y, Direction dir, uint8_t length);


void Move(struct Map* map, struct Snake* snake);
void Grow(struct Map* map, struct Snake* snake);
void Kill(struct Map* map, struct Snake* snake);

void SetDirection(struct Snake* snake, Direction dir);


struct Blob* GetHead(struct Snake* snake);
uint8_t GetId(struct Snake* snake);
uint8_t GetLength(struct Snake* snake);


#endif