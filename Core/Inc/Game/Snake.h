#ifndef SNAKE_H
#define SNAKE_H

#include <stdlib.h>
#include <stdint.h>
#include "Game/Blob.h"


#define SNAKE_START_LENGTH 3
#define SNAKE_HEAD_EMPTY_OVERHEAD 2 // the number of empty spaces at  the front of head of the snake, to give some space for the head to turn

struct Map;
struct Player;

struct Snake {
	struct Blob* head; // the head of the snake
	struct Blob* tail; // the tail of the snake
};

struct Snake* Snake(struct Map* map, uint8_t player_id, int x, int y, Direction dir, uint8_t length);


bool Snake_Update(struct Player* player, struct Map* map, struct Snake* snake);
void Snake_Grow(struct Map* map, struct Snake* snake);
void Snake_Delete(struct Player* player, struct Map* map, struct Snake* snake);

void Snake_SetDirection(struct Snake* snake, Direction dir);

void Snake_Remove_Tail(struct Map* map, struct Snake* snake);

bool Snake_IsSpawnable(struct Map* map, int x, int y, Direction dir, uint8_t length);


struct Blob* Snake_GetHead(struct Snake* snake);
uint8_t Snake_GetId(struct Snake* snake);
uint8_t Snake_GetLength(struct Snake* snake);
void Snake_GetPreviousBodyPosition(struct Blob* blob, int* x, int* y);
void Snake_GetNextBodyPosition(struct Blob* blob, int* x, int* y);

//private
Direction Opposite_Direction(Direction dir);


#endif