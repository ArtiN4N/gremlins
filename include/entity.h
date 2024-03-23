#pragma once

#include "defs.h"
#include "raylib.h"

#include <cmath>

struct Entity {
    Vector2 position;
    Vector2 velocity;

    float dashTrace;

    float radius;
    float speed;

    Direction dir;

    AttackBox attack;

    void init(float x, float y, float rad, float spd) {
        position = {x, y};
        velocity = { 0.f, 0.f };

        dashTrace = 0.f;

        radius = rad;

        speed = spd;

        dir = NORTH;

        attack.init(70, 50, .3f, .05f);
    }

    void update(float dt) {
        
        if (IsKeyDown(KEY_LEFT)) {
            position.x -= speed * dt;
            dir = WEST;
        }
        if (IsKeyDown(KEY_RIGHT)) {
            position.x += speed * dt;
            dir = EAST;
        }
        if (IsKeyDown(KEY_UP)) {
            position.y -= speed * dt;
            dir = NORTH;
        }
        if (IsKeyDown(KEY_DOWN)) {
            position.y += speed * dt;
            dir = SOUTH;
        }

        if (IsKeyPressed(KEY_Z) && attack.ready) attack.active = true;

        if (IsKeyPressed(KEY_X) && dashTrace == 0.f && !attack.active) {
            switch (dir) {
                case NORTH:
                    velocity.y += -3000;
                    break;
                case EAST:
                    velocity.x += 3000;
                    break;
                case SOUTH:
                    velocity.y += 3000;
                    break;
                case WEST:
                    velocity.x += -3000;
                    break;
            }

            dashTrace = 3000;
        }

        attack.update(dir, radius, dt);

        position.x += velocity.x * dt;
        position.y += velocity.y * dt;

        float f = .0005f;
        velocity.x *= pow(f, dt);
        velocity.y *= pow(f, dt);
        dashTrace *= pow(f, dt);

        if (velocity.x > 0.f && velocity.x < 50.f) velocity.x = 0.f;
        if (velocity.x < 0.f && velocity.x > -50.f) velocity.x = 0.f;

        if (velocity.y > 0.f && velocity.y < 50.f) velocity.y = 0.f;
        if (velocity.y < 0.f && velocity.y > -50.f) velocity.y = 0.f;

        if (dashTrace > 0.f && dashTrace < 50.f) dashTrace = 0.f;
        if (dashTrace < 0.f && dashTrace > -50.f) dashTrace = 0.f;
    }

    void draw() {
        DrawCircleV(position, radius, RED);
        attack.debugDraw(position);
    }
};