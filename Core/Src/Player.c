#include "Player.h"


struct Player* Player(){
    struct Player *player = malloc(sizeof(struct Player));
    player->score = 0;
    player->snake = NULL;
    player->is_alive = true;
    player->buttonPressed[0] = false;
    player->buttonPressed[1] = false;
    player->buttonPressed[2] = false;
    player->buttonPressed[3] = false;
    player->is_ready = false;
    return player;
}

void Signal_Input(struct Player* player, Direction dir) {
    player->buttonPressed[dir] = true;
}

bool Is_Alive(struct Player* player) {
    return player->is_alive;
}

void Player_Update(struct Map* map, struct Player* player) {
    for(int i = 0; i < 4; i++) {
        if(player->buttonPressed[i]) {
            Snake_SetDirection(player->snake, i);
        }
    }
    if (Is_Alive(player)) {
        Snake_Update(map, player->snake);
    }
}

void Player_Delete(struct Map* map, struct Player* player) {
    if (player == NULL) return;
    Snake_Delete(map, player->snake);
    free(player);
}