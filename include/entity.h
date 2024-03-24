#pragma once

#include "defs.h"
#include "raylib.h"

#include <cmath>
#include <iostream>
#include <vector>

#include "col.hpp"
#include "Map.hpp"

struct Entity {
    Vector2 position;

    Vector2 moveVelocity;
    Vector2 actionVelocity;

    float dashTrace;

    float radius;
    float speed;

    Direction dir;

    AttackBox attack;

    void init(float x, float y, float rad, float spd) {
        position = {x, y};

        moveVelocity = { 0.f, 0.f };
        actionVelocity = { 0.f, 0.f };

        dashTrace = 0.f;

        radius = rad;

        speed = spd;

        dir = NORTH;
    }

    void initProj(Direction direction) {
        if (!attack.projectile) return;

        dir = direction;

        switch (dir) {
            case NORTH:
                moveVelocity.y = -speed;
                break;
            case SOUTH:
                moveVelocity.y = speed;
                break;
            case WEST:
                moveVelocity.x = -speed;
                break;
            case EAST:
                moveVelocity.x = speed;
                break;
        }
    }

    bool update(bool map_data[1024], float dt) {
        bool ret = attack.update(dir, radius, dt);

        Vector2 prevPos = { position.x, position.y };

        position.x += (actionVelocity.x + moveVelocity.x) * dt;
        position.y += (actionVelocity.y + moveVelocity.y) * dt;

        float f = .0005f;
        actionVelocity.x *= pow(f, dt);
        actionVelocity.y *= pow(f, dt);
        dashTrace *= pow(f, dt);

        if (actionVelocity.x > 0.f && actionVelocity.x < 50.f) actionVelocity.x = 0.f;
        if (actionVelocity.x < 0.f && actionVelocity.x > -50.f) actionVelocity.x = 0.f;

        if (actionVelocity.y > 0.f && actionVelocity.y < 50.f) actionVelocity.y = 0.f;
        if (actionVelocity.y < 0.f && actionVelocity.y > -50.f) actionVelocity.y = 0.f;

        if (dashTrace > 0.f && dashTrace < 50.f) dashTrace = 0.f;
        if (dashTrace < 0.f && dashTrace > -50.f) dashTrace = 0.f;
        
        for (int iY = 0; iY < NEW_PISKEL_FRAME_HEIGHT; iY++) {
            for (int iX = 0; iX < NEW_PISKEL_FRAME_WIDTH; iX++) {
                if (!map_data[iY * NEW_PISKEL_FRAME_WIDTH + iX]) continue;
                bool collide = vix::check_collision_circle_rec_this(position, radius, rec);

                Rectangle rec = {iX * TILE_SIZE, iY * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                

                if (collide && prevPos.x > (iX * TILE_SIZE) + TILE_SIZE && position.x < (iX * 32) + 32) {
                    position.x = prevPos.x;
                }

                if (collide && prevPos.x < (iX * TILE_SIZE) && position.x > (iX * TILE_SIZE)) {
                    position.x = prevPos.x;
                }
            }
        }
        /*
        //Draw bounding box objects
        size_t length = 1024;

        // prevposition - indecies
        // ig it depends on map tile size
        // lets say theyre 25 * 25
        Vector2 prevPosToMap = { (int) prevPos.x / TILE_SIZE, (int) prevPos.y / TILE_SIZE };
        Vector2 posToMap = { (int) position.x / TILE_SIZE, (int) position.y / TILE_SIZE };

        std::cout << prevPos.x << ":" << position.x << ":" << 2 * TILE_SIZE << std::endl;

        for (size_t i = 0; i < length; i++) {
            //convert i to 2d
            size_t iX = i % NEW_PISKEL_FRAME_WIDTH;
            size_t iY = i / NEW_PISKEL_FRAME_HEIGHT;

            if (prevPos.x > (iX * TILE_SIZE) + TILE_SIZE && position.x < (iX * 32) + 32 && position.y > (iY * 32) && position.y < (iX * 32) + 32) {
                actionVelocity.x = 0.f;
                position.x = prevPos.x;
            }

            if (prevPos.x < (iX * TILE_SIZE) && position.x > (iX * TILE_SIZE) && position.y > (iY * 32) && position.y < (iX * 32) + 32) {
                actionVelocity.x = 0.f;
                position.x = prevPos.x;
            }
            
            

            //new_piskel_data[0][i]; // color value
            
        }*/

        return ret;
    }

    void draw() {
        Vector2 posToMap = { (int) position.x / TILE_SIZE, (int) position.y / TILE_SIZE };
        std::cout << "tile = " << posToMap.x << ":" << posToMap.y << std::endl;

        //DrawRectangle();

        DrawCircleV(position, radius, RED);
        attack.debugDraw(position);
    }
};