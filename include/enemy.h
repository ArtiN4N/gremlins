#pragma once

#include "defs.h"
#include "raylib.h"
#include "entity.h"

void basicAI(Entity* parent, Entity* target, float dt) {
    // Move the enemy towards the player, but not beyond the enemy's speed
    //parent->moveVelocity = Vector2MoveTowards(parent->position, target->position, parent->speed * dt);

    Vector2 dir = Vector2Subtract(target->position, parent->position);
    dir = Vector2Normalize(dir);
    
    parent->moveVelocity.x = dir.x * parent->speed;
    parent->moveVelocity.y = dir.y * parent->speed;

    
}