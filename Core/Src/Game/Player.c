#include "Game/Player.h"
#include "Game/Snake.h"
#include "Game/Game_Data.h"
#include "Game/Game.h"


struct Player Player(){
    struct Player player = {
        .score = 0,
        .snake = NULL,
        .is_alive = false,
        .buttonPressed[0] = false,
        .buttonPressed[1] = false,
        .buttonPressed[2] = false,
        .buttonPressed[3] = false,
        .is_ready = false,
        .id = PLAYER_UNKNOWN_ID
    };
    return player;
    // struct Player *player = malloc(sizeof(struct Player));
    // player->score = 0;
    // player->snake = NULL;
    // player->is_alive = true;
    // player->buttonPressed[0] = false;
    // player->buttonPressed[1] = false;
    // player->buttonPressed[2] = false;
    // player->buttonPressed[3] = false;
    // player->is_ready = false;
    // return player;
}

void Signal_Input(struct Player* player, Direction dir) {
    player->buttonPressed[dir] = true;
}

bool Is_Alive(struct Player* player) {
    return player->is_alive;
}

void Player_Update(struct Map* map, struct Player* player) {
    if (Is_Alive(player) == false) return;
    
    for(int i = 0; i < 4; i++) {
        if(player->buttonPressed[i]) {
            Snake_SetDirection(player->snake, i);
        }
    }
    Snake_Update(player, map, player->snake);
    if (player->snake == NULL) {
        player->is_alive = false;
    }
}

void Player_Delete(struct Map* map, struct Player* player) {
    if (player == NULL) return;
    Snake_Delete(player, map, player->snake);
    free(player);
}

int Player_GetScore(struct Player* player) {
    return player->score;
}

void Player_AddScore(struct Player* player, int score) {
    player->score += score;
}

void Player_SetReady(struct Player* player, bool is_ready) {
    player->is_ready = is_ready;
}

bool Player_IsReady(struct Player* player) {
    return player->is_ready;
}

bool Player_Spawn(struct Game* game, struct Player* player, int x, int y, Direction dir) {
    if (Snake_IsSpawnable(game->map, x, y, dir, SNAKE_START_LENGTH) == false) return false;
    player->snake = Snake(game->map, Player_Getid(game), x, y, dir, SNAKE_START_LENGTH);
    return true;
}



void Player_SpawnRandom(struct Game* game, struct Map* map, struct Player* player) {
    srand(HAL_GetTick());
    int x = rand() % MAP_WIDTH;
    int y = rand() % MAP_HEIGHT;
    Direction dir = rand() % 4;
    while (Snake_IsSpawnable(map, x, y, dir, SNAKE_START_LENGTH) == false) {
        x = rand() % MAP_WIDTH;
        y = rand() % MAP_HEIGHT;
    }
    player->snake = Snake(map, Player_Getid(game), x, y, dir, SNAKE_START_LENGTH);
}

int Player_Getid(struct Game* game) {
    if (Game_IsHost(game)) {
        return PLAYER_1_ID;
    }else {
        return PLAYER_2_ID;
    }
}
