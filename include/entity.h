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
    }

    void update(float dt) {
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