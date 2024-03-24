#pragma once

#include "defs.h"
#include "raylib.h"
#include "entity.h"

struct EnemySprites {
    Texture2D idle[4];

    Texture2D walk[4];

    void init() {
        for (int i = 0; i < 4; i++) {
            Image img = LoadImage(TextFormat("assets/gramps/idle%d.png", i + 1));
            idle[i] = LoadTextureFromImage(img);
            UnloadImage(img);
        }

        for (int i = 0; i < 4; i++) {
            Image img = LoadImage(TextFormat("assets/gramps/walk%d.png", i + 1));
            walk[i] = LoadTextureFromImage(img);
            UnloadImage(img);
        }
    }

    void unload() {
        for (int i = 0; i < 4; i++) {
            UnloadTexture(idle[i]);
        }
        for (int i = 0; i < 4; i++) {
            UnloadTexture(walk[i]);
        }
    }
};

void enemyInit(Entity* enemy, EnemySprites* sprites) {
    enemy->tex = &(sprites->idle[3]);
    enemy->player = false;
}

void basicAI(Entity* parent, Entity* target, float dt) {
    // Move the enemy towards the player, but not beyond the enemy's speed
    //parent->moveVelocity = Vector2MoveTowards(parent->position, target->position, parent->speed * dt);

    Vector2 dir = Vector2Subtract(target->position, parent->position);
    dir = Vector2Normalize(dir);
    
    parent->moveVelocity.x = dir.x * parent->speed;
    parent->moveVelocity.y = dir.y * parent->speed;

    
}