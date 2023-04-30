#include "Game/Map.h"
#include "Game/Blob.h"
#include "Game/Snake.h"
#include <stdlib.h>
#include <stdbool.h>


// create a new snake with given id and position (x, y) and direction
struct Snake* Snake(struct Map* map, uint8_t player_id, uint8_t x, uint8_t y, Direction dir, uint8_t length) {
    struct Snake* snake = malloc(sizeof(struct Snake));
    struct Blob* head = Blob(player_id, dir, BODY, NULL, NULL, x, y);
    Set_Body(map, x, y, head);
    snake->head = head;
    snake->tail = head;
    for (int i = 1; i < length; i++) {
        switch (dir) {
            case UP:
                y--;
                break;
            case DOWN:
                y++;
                break;
            case LEFT:
                x++;
                break;
            case RIGHT:
                x--;
                break;
        }
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



// move snake head to new position by its direction
// if the snake is dead, kill it
// if the snake is not dead, check if the snake eats food
// move the snake by create a new head
// if the snake eats food, do not delete the tail(that way, the length grows by 1). if not, delete the tail
void Snake_Update(struct Map* map, struct Snake* snake) {
    struct Blob* head = snake->head;
    uint8_t x = head->x;
    uint8_t y = head->y;
    bool eat = false;
    switch (head->dir) {
        case UP:
            y++;
            break;
        case DOWN:
            y--;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
    }
    if (x < 0 || x >= map->width || y < 0 || y >= map->height) {
        Snake_Delete(map, snake);
        return;
    }
    if (Is_Empty(map, x, y) == false) {
        if (Is_Stone(map, x, y) || Is_Body(map, x, y)) {
            Snake_Delete(map, snake);
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

// when a snake hit the wall or itself, call this function, will remove the snake from the game
void Snake_Delete(struct Map* map, struct Snake* snake) {
    if (snake == NULL) return;
    struct Blob* blob = snake->head;
    while (blob != NULL) {
        struct Blob* next = blob->next;
        ClearCell(map, blob->x, blob->y);
        blob = next;
    }
    free(snake);
}

void Snake_Remove_Tail(struct Map* map, struct Snake* snake) {
    if (snake == NULL) return;
    struct Blob* tail = snake->tail;
    snake->tail = snake->tail->prev;
    ClearCell(map, tail->next->x, tail->next->y);
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