#include "Game/Blob.h"


int get_Id(struct Blob* blob) {
    return blob->player_id;
}


struct Blob* Blob(uint8_t player_id, Direction dir, Type type, struct Blob* prev, struct Blob* next, uint8_t x, uint8_t y) {
	struct Blob* blob = malloc(sizeof(struct Blob));
	blob->dir = dir;
	blob->type = type;
	blob->prev = prev;
	blob->next = next;
	blob->x = x;
	blob->y = y;
	blob->player_id = player_id;

	return blob;
}