#include "Player.h"


struct Player* Player(){
    return malloc(sizeof(struct Player));
}

void Signal_Input(struct Player* player, Direction dir) {
    player->buttonPressed[dir] = true;
}

bool Is_Alive(struct Player* player) {
    return player->is_alive;
}