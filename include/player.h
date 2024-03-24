#pragma once

#include "defs.h"
#include "raylib.h"
#include "entity.h"

#include <vector>


void playerInitAttacks(Entity* player) {
    player->attack.init(70, 50, .3f, .05f, false);
}

void playerInputHandle(Entity* player, std::vector<Entity>* projectileList, float dt) {

    if (IsKeyPressed(KEY_LEFT)) {
        player->moveVelocity.x -= player->speed;
        player->dir = WEST;
    } else if (IsKeyReleased(KEY_LEFT)) {
        player->moveVelocity.x += player->speed;
    }

    if (IsKeyPressed(KEY_RIGHT)) {
        player->moveVelocity.x += player->speed;
        player->dir = EAST;
    } else if (IsKeyReleased(KEY_RIGHT)) {
        player->moveVelocity.x -= player->speed;
    }


    if (IsKeyPressed(KEY_UP)) {
        player->moveVelocity.y -= player->speed;
        player->dir = NORTH;
    } else if (IsKeyReleased(KEY_UP)) {
        player->moveVelocity.y += player->speed;
    }

    if (IsKeyPressed(KEY_DOWN)) {
        player->moveVelocity.y += player->speed;
        player->dir = EAST;
    } else if (IsKeyReleased(KEY_DOWN)) {
        player->moveVelocity.y -= player->speed;
    }



    if (IsKeyPressed(KEY_Z) && player->attack.ready) player->attack.active = true;

    if (IsKeyPressed(KEY_X) && player->dashTrace == 0.f && !player->attack.active) {
        switch (player->dir) {
            case NORTH:
                player->actionVelocity.y += -3000;
                break;
            case EAST:
                player->actionVelocity.x += 3000;
                break;
            case SOUTH:
                player->actionVelocity.y += 3000;
                break;
            case WEST:
                player->actionVelocity.x += -3000;
                break;
        }

        player->dashTrace = 3000;
    }

    if (IsKeyPressed(KEY_C)) {
        Entity arrow;
        arrow.init(player->position.x, player->position.y, 5, 1000);
        arrow.attack.init(10, 100, 1.f, .0f, true);
        arrow.initProj(player->dir);

        projectileList->push_back(arrow);
    }
}