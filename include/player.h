#pragma once

#include "defs.h"
#include "raylib.h"
#include "entity.h"

void playerInputHandle(Entity* player, float dt) {
    if (IsKeyDown(KEY_LEFT)) {
        player->position.x -= player->speed * dt;
        player->dir = WEST;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        player->position.x += player->speed * dt;
        player->dir = EAST;
    }
    if (IsKeyDown(KEY_UP)) {
        player->position.y -= player->speed * dt;
        player->dir = NORTH;
    }
    if (IsKeyDown(KEY_DOWN)) {
        player->position.y += player->speed * dt;
        player->dir = SOUTH;
    }

    if (IsKeyPressed(KEY_Z) && player->attack.ready) player->attack.active = true;

    if (IsKeyPressed(KEY_X) && player->dashTrace == 0.f && !player->attack.active) {
        switch (player->dir) {
            case NORTH:
                player->velocity.y += -3000;
                break;
            case EAST:
                player->velocity.x += 3000;
                break;
            case SOUTH:
                player->velocity.y += 3000;
                break;
            case WEST:
                player->velocity.x += -3000;
                break;
        }

        player->dashTrace = 3000;
    }
}