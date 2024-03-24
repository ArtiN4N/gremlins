#pragma once

#include "defs.h"
#include "raylib.h"
#include "entity.h"

void humanAI(Entity* parent, Entity* target, float dt) {
    // Move the human away from the player

    if (parent->alertRadius + target->radius < Vector2Distance(target->position, parent->position)) return;

    Vector2 dir = Vector2Subtract(target->position, parent->position);
    dir = Vector2Normalize(dir);
    
    parent->moveVelocity.x = dir.x * -parent->speed;
    parent->moveVelocity.y = dir.y * -parent->speed;
}

void ghostAI(Entity* parent, Entity* target, float dt) {
    // Move the ghost towards the player
   if (parent->alertRadius + target->radius < Vector2Distance(target->position, parent->position)) return;

    Vector2 dir = Vector2Subtract(target->position, parent->position);
    dir = Vector2Normalize(dir);
    
    parent->moveVelocity.x = dir.x * parent->speed;
    parent->moveVelocity.y = dir.y * parent->speed;
}

void wizardAI(Entity* parent, Entity* target, std::vector<Entity>* projectileList, float dt) {
    if (parent->alertRadius + target->radius < Vector2Distance(target->position, parent->position)) return;

    Vector2 dir = Vector2Normalize(Vector2Subtract(target->position, parent->position));
    parent->shootCooldown -= dt;
    if (parent->shootCooldown <= 0) {
        Entity arrow;
        arrow.init(parent->position.x, parent->position.y, PROJECTILE);
        arrow.initProj(dir);

        projectileList->push_back(arrow);
        parent->shootCooldown = .8f;
    }
    
}