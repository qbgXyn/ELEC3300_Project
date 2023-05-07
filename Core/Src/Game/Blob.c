#include "Game/Blob.h"
#include "lcd.h"
#include "stdbool.h"
#include "Game/Game_Data.h"


int get_Id(struct Blob* blob) {
    return blob->player_id;
}


struct Blob* Blob(uint8_t player_id, Direction dir, Type type, struct Blob* prev, struct Blob* next, int x, int y) {
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
unsigned short Blob_GetColor(struct Blob* blob) {
	bool isHead = blob->prev == NULL;
	switch (blob->type)
	{
	case EMPTY:
		return EMPTY_COLOR;
	case FOOD:
		return FOOD_COLOR;
	case STONE:
		return STONE_COLOR;
	case BODY:
		if (isHead) {
			if (blob->player_id == PLAYER_1_ID) {
				return PLAYER_1_HEAD_COLOR;
			}
			else {
				return PLAYER_2_HEAD_COLOR;
			}
		}else {
			if (blob->player_id == PLAYER_1_ID) {
				return PLAYER_1_BODY_COLOR;
			}
			else {
				return PLAYER_2_BODY_COLOR;
			}
		}
	default:
		break;
	}
	return 0;
}
