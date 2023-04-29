#ifndef BLOB_H
#define BLOB_H

#include <stdlib.h>
#include <stdint.h>

typedef enum {UP, DOWN, LEFT, RIGHT} Direction;
typedef enum {EMPTY, BODY, FOOD, STONE} Type;
struct Blob {
	Direction dir;
	Type type;
	struct Blob* prev;
	struct Blob* next;
	uint8_t player_id; // 0 for neutral, 1 for player 1, 2 for player 2
	uint8_t x;
	uint8_t y;
};


// create blob and assign coordinate with it
struct Blob* Blob(uint8_t player_id, Direction dir, Type type, struct Blob* prev, struct Blob* next, uint8_t x, uint8_t y);

int get_Id(struct Blob* blob);




#endif