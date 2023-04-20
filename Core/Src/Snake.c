#include "Map.h"
#include "Blob.h"
#include "Snake.h"
#include <stdlib.h>
#include <stdbool.h>


    // create a new snake with given id and position (x, y) and direction
    struct Snake* Snake(struct Map* map, uint8_t player_id, uint8_t x, uint8_t y, Direction dir, uint8_t length) {
        struct Snake* snake = malloc(sizeof(struct Snake));
        struct Blob* head = Blob(map, player_id, dir, BODY, NULL, NULL, x, y);
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
            struct Blob* blob = Blob(map, player_id, dir, BODY, snake->tail, NULL, x, y);
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
	void Move(struct Map* map, struct Snake* snake) {
        struct Blob* head = snake->head;
        struct Blob* tail = snake->tail;
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
            Kill(map, snake);
            return;
        }
        struct Blob* blob = map->map[x][y];
        if (blob != NULL) {
            if (blob->type == STONE || blob->type == BODY) {
                Kill(map, snake);
                return;
            }
            if(blob->type == FOOD) {
                free(blob);
                eat = true;
            }
        }
        struct Blob* new_head = Blob(map, head->player_id, head->dir, BODY, NULL, head, x, y);
        head->prev = new_head;
        snake->head = new_head;
        if (eat == false) {
            map->map[tail->x][tail->y] = NULL;
            snake->tail = snake->tail->prev;
            snake->tail->next = NULL;
            free(tail);
        }
    }

    // when a snake hit the wall or itself, call this function, and remove the snake from the game
	void Kill(struct Map* map, struct Snake* snake) {
        struct Blob* blob = snake->head;
        while (blob != NULL) {
            struct Blob* next = blob->next;
            map->map[blob->x][blob->y] = NULL;
            free(blob);
            blob = next;
        }
        free(snake);
    }

    // change the direction of the snake
    void SetDirection(struct Snake* snake, Direction dir) {
        snake->head->dir = dir;
    }

    // get the snake's head
    struct Blob* GetHead(struct Snake* snake) {
        return snake->head;
    }


    // get the snake's id
    uint8_t GetId(struct Snake* snake) {
        return snake->head->player_id;
    }

    // get the snake's length
    uint8_t GetLength(struct Snake* snake) {
        struct Blob* blob = snake->head->next;
        uint8_t length = 1;
        while (blob != NULL) {
            length++;
            blob = blob->next;
        }
        return length;
    }
