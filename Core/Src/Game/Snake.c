#include "Game/Map.h"
#include "Game/Blob.h"
#include "Game/Snake.h"
#include <stdlib.h>
#include <stdbool.h>
#include "Game/Player.h"


// create a new snake with given id and position (x, y) and direction
struct Snake* Snake(struct Map* map, uint8_t player_id, int x, int y, Direction dir, uint8_t length) {
    struct Snake* snake = malloc(sizeof(struct Snake));
    struct Blob* head = Blob(player_id, dir, BODY, NULL, NULL, x, y);
    Set_Body(map, x, y, head);
    snake->head = head;
    snake->tail = head;
    for (int i = 1; i < length; i++) {
        Snake_GetPreviousBodyPosition(snake->tail, &x, &y);
        struct Blob* blob = Blob(player_id, dir, BODY, snake->tail, NULL, x, y);
        Set_Body(map, x, y, blob);
        snake->tail->next = blob;
        snake->tail = blob;
        if (i == 1) {
            head->next = blob;
        }
    }
    return snake;
}


//given a coordinate and direction, and length, return if the snake can spawn at that position
bool Snake_IsSpawnable(struct Map* map, int x, int y, Direction dir, uint8_t length) {
    length += SNAKE_HEAD_EMPTY_OVERHEAD;
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) return false;
    switch (dir) {
        case UP:
            y -= SNAKE_HEAD_EMPTY_OVERHEAD; //shift the head up to make space for the head
            if (y - length < 0) return false;
            if (y + length >= MAP_HEIGHT) return false;
            for (int i = 0; i < length; i++) {
                if (Is_Empty(map, x, y + i) == false) return false;
            }
            break;
        case DOWN:
            y += SNAKE_HEAD_EMPTY_OVERHEAD; //shift the head down to make space for the head
            if (y + length >= MAP_HEIGHT) return false;
            if (y - length < 0) return false;
            for (int i = 0; i < length; i++) {
                if (Is_Empty(map, x, y - i) == false) return false;
            }
            break;
        case LEFT:
            x -= SNAKE_HEAD_EMPTY_OVERHEAD; //shift the head left to make space for the head
            if (x - length < 0) return false;
            if (x + length >= MAP_WIDTH) return false;
            for (int i = 0; i < length; i++) {
                if (Is_Empty(map, x - i, y) == false) return false;
            }
            break;
        case RIGHT:
            x += SNAKE_HEAD_EMPTY_OVERHEAD; //shift the head right to make space for the head
            if (x + length >= MAP_WIDTH) return false;
            if (x - length < 0) return false;
            for (int i = 0; i < length; i++) {
                if (Is_Empty(map, x + i, y) == false) return false;
            }
            break;
    }
    return true;
}



// move snake head to new position by its direction
// if the snake is dead, kill it
// if the snake is not dead, check if the snake eats food
// move the snake by create a new head
// if the snake eats food, do not delete the tail(that way, the length grows by 1). if not, delete the tail
void Snake_Update(struct Player* player, struct Map* map, struct Snake* snake) {
    struct Blob* head = snake->head;
    int x = head->x;
    int y = head->y;
    bool eat = false;
    Set_Differ(map, x, y); // set the head to different color
    Snake_GetNextBodyPosition(head, &x, &y);
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
        Snake_Delete(player, map, snake);
        return;
    }
    if (Is_Empty(map, x, y) == false) {
        if (Is_Stone(map, x, y) || Is_Body(map, x, y)) {
            Snake_Delete(player, map, snake);
            return;
        }
        if(Is_Food(map, x, y)) {
            ClearCell(map, x, y);
            eat = true;
        }
    }
    struct Blob* new_head = Blob(head->player_id, head->dir, BODY, NULL, head, x, y);
    Set_Body(map, x, y, new_head);
    head->prev = new_head;
    snake->head = new_head;
    if (eat == false) {
        Snake_Remove_Tail(map, snake);
    }
}

// get the previous position of the snake head
// for example, if the snake is going up, the previous position is (x, y+1)
void Snake_GetPreviousBodyPosition(struct Blob* blob, int* x, int* y) {
    if (blob == NULL) return;
    switch (blob->dir) {
        case UP:
            *y = blob->y + 1;
            *x = blob->x;
            break;
        case DOWN:
            *y = blob->y - 1;
            *x = blob->x;
            break;
        case LEFT:
            *y = blob->y;
            *x = blob->x + 1;
            break;
        case RIGHT:
            *y = blob->y;
            *x = blob->x - 1;
            break;
    }
}

// get the next position of the snake head
// for example, if the snake is going up, the next position is (x, y-1)
void Snake_GetNextBodyPosition(struct Blob* blob, int* x, int* y) {
    if (blob == NULL) return;
    switch (blob->dir) {
        case UP:
            *y = blob->y - 1;
            *x = blob->x;
            break;
        case DOWN:
            *y = blob->y + 1;
            *x = blob->x;
            break;
        case LEFT:
            *y = blob->y;
            *x = blob->x - 1;
            break;
        case RIGHT:
            *y = blob->y;
            *x = blob->x + 1;
            break;
    }
}

// when a snake hit the wall or itself, call this function, will remove the snake from the game
void Snake_Delete(struct Player* player, struct Map* map, struct Snake* snake) {
    if (snake == NULL) return;
    struct Blob* blob = snake->head;
    while (blob != NULL) {
        struct Blob* next = blob->next;
        ClearCell(map, blob->x, blob->y);
        blob = next;
    }
    free(snake);
    player->snake = NULL;
}

void Snake_Remove_Tail(struct Map* map, struct Snake* snake) {
    if (snake == NULL) return;
    struct Blob* tail = snake->tail;
    snake->tail = snake->tail->prev;
    ClearCell(map, tail->x, tail->y);
    snake->tail->next = NULL;
}

// change the direction of the snake
void Snake_SetDirection(struct Snake* snake, Direction dir) {
    if (dir != snake->head->dir && dir != Opposite_Direction(snake->head->dir)) {
        snake->head->dir = dir;
    }
}

// get the snake's head
struct Blob* Snake_GetHead(struct Snake* snake) {
    return snake->head;
}


bool Snake_IsDead(struct Snake* snake, struct Blob* blob) {
    if (blob == NULL) return false;
    if (snake == NULL) return false;
    if (blob->player_id != snake->head->player_id) return false;
    return snake->head == blob;
}


// get the snake's id
uint8_t Snake_GetId(struct Snake* snake) {
    return snake->head->player_id;
}

// get the snake's length
uint8_t Snake_GetLength(struct Snake* snake) {
    struct Blob* blob = snake->head->next;
    uint8_t length = 1;
    while (blob != NULL) {
        length++;
        blob = blob->next;
    }
    return length;
}


Direction Opposite_Direction(Direction dir) {
    switch (dir) {
        case UP:
            return DOWN;
        case DOWN:
            return UP;
        case LEFT:
            return RIGHT;
        case RIGHT:
            return LEFT;
    }
    return UP;
}
