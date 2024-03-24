#pragma once

#include "defs.h"
#include "raylib.h"
#include "raymath.h"

#include <cmath>
#include <iostream>
#include <vector>

#include "col.hpp"
#include "map.h"

struct Entity {
    Vector2 position;

    Vector2 moveVelocity;
    Vector2 actionVelocity;

    float dashTrace;

    float radius;
    float speed;

    Direction dir;

    AttackBox attack;

    Texture2D* tex;

    bool player;

    void init(float x, float y, float rad, float spd) {
        position = {x, y};

        moveVelocity = { 0.f, 0.f };
        actionVelocity = { 0.f, 0.f };

        dashTrace = 0.f;

        radius = rad;

        speed = spd;

        dir = NORTH;

        player = false;
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

    bool tileCollisionEast(Vector2* prevPos, int iX, int iY, bool* foundX, bool collide) {
        if (collide && prevPos->x < (iX * TILE_SIZE) && position.x > (iX * TILE_SIZE) && !*foundX) {
            position.x = prevPos->x;
            //prevPos->y = position.y;
            actionVelocity.x *= -.5f;
            *foundX = true;

            return true;
        }
        return false;
    }

    bool tileCollisionWest(Vector2* prevPos, int iX, int iY, bool* foundX, bool collide) {
        if (collide && prevPos->x > (iX * TILE_SIZE) + TILE_SIZE && position.x < (iX * TILE_SIZE) + TILE_SIZE && !*foundX) {
            position.x = prevPos->x;
            //prevPos->y = position.y;
            actionVelocity.x *= -.5f;
            *foundX = true;
            return true;
        }
        return false;
    }

    bool tileCollisionX(Vector2* prevPos, int iX, int iY, bool* foundX, bool collide) {
        if ((actionVelocity.x + moveVelocity.x) > 0.f) return tileCollisionEast(prevPos, iX, iY, foundX, collide);
        else return tileCollisionWest(prevPos, iX, iY, foundX, collide);
    }

    bool tileCollisionSouth(Vector2* prevPos, int iX, int iY, bool* foundY, bool collide) {
        if (collide && prevPos->y < (iY * TILE_SIZE) && position.y > (iY * TILE_SIZE) && !*foundY) {
            position.y = prevPos->y;
            //prevPos->x = position.x;
            actionVelocity.y *= -.5f;
            *foundY = true;
            return true;
        }
        return false;
    }

    bool tileCollisionNorth(Vector2* prevPos, int iX, int iY, bool* foundY, bool collide) {
        if (collide && prevPos->y > (iY * TILE_SIZE) + TILE_SIZE && position.y < (iY * TILE_SIZE) + TILE_SIZE && !*foundY) {
            position.y = prevPos->y;
            //prevPos->x = position.x;
            actionVelocity.y *= -.5f;
            *foundY = true;
            return true;
        }
        return false;
    }

    bool tileCollisionY(Vector2* prevPos, int iX, int iY, bool* foundY, bool collide) {
        if ((actionVelocity.y + moveVelocity.y) < 0.f) return tileCollisionNorth(prevPos, iX, iY, foundY, collide);
        else return tileCollisionSouth(prevPos, iX, iY, foundY, collide);
    }

    bool update(Map* map, float dt) {
        bool ret = attack.update(dir, radius, dt);

        Vector2 prevPos = { position.x, position.y };

        position.x += (actionVelocity.x + moveVelocity.x) * dt;
        position.y += (actionVelocity.y + moveVelocity.y) * dt;

        // Debug logging
        // std::cout << "Player previous position: (" << prevPos.x << ", " << prevPos.y << ")\n";
        // std::cout << "PLayer updated postion: (" << position.x << ", " << position.y << ")\n";

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

        // MAP COLLISION
        Vector2 tileGridTL = {(float) ((int) (position.x - radius) / map->tileSize), (float) ((int) (position.y - radius) / map->tileSize)};
        Vector2 tileGridTR = {(float) ((int) (position.x + radius) / map->tileSize), (float) ((int) (position.y - radius) / map->tileSize)};
        Vector2 tileGridBL = {(float) ((int) (position.x - radius) / map->tileSize), (float) ((int) (position.y + radius) / map->tileSize)};
        Vector2 tileGridBR = {(float) ((int) (position.x + radius) / map->tileSize), (float) ((int) (position.y + radius) / map->tileSize)};

        Vector2 tilesToCheck[] = { tileGridTL, tileGridTR, tileGridBL, tileGridBR };

        bool foundX = false;
        bool foundY = false;

        for (int i = 0; i < 4; i++) {
            
            int iX = (int) tilesToCheck[i].x;
            int iY = (int) tilesToCheck[i].y;

            if (iX < 0 || iY < 0 || iX >= map.width || iY >= map.height) continue;
            if (map->mapCollisionData[iY * map->width + iX] == NONE) continue;
            
            Rectangle rec = {(float) (iX * map->tileSize), (float) (iY * map->tileSize), (float) map->tileSize, (float) map->tileSize};

            bool collide = vix::check_collision_circle_rec_this(position, radius, rec);

            if (!collide) continue;

            if (map->mapCollisionData[iY * map->width + iX] == DOOR && player) {
                std::cout << "loading new map" << std::endl;
                map->switchMap(map->getNewMap(position));
                position = map->getSpawnPos();
                break;
            }
            
            if (dir == EAST || dir == WEST) {
                if (tileCollisionX(&prevPos, iX, iY, &foundX, collide)) continue;
                if (tileCollisionY(&prevPos, iX, iY, &foundY, collide)) continue;
            } else {
                if (tileCollisionY(&prevPos, iX, iY, &foundY, collide)) continue;
                if (tileCollisionX(&prevPos, iX, iY, &foundX, collide)) continue;
            }
            
            
        }

        return ret;
    }


    void draw() {
        Texture2D drawing = *tex;
        Rectangle sourceRec = { 0.0f, 0.0f, (float) drawing.width, (float) drawing.height };

        Rectangle destRec = { position.x, position.y - 10, radius * 3, radius * 3 };
        DrawCircleV(position, radius, RED);
        // draw backgroudd img scaled to the screen size
        DrawTexturePro(drawing, sourceRec, destRec, { radius * 3/2, radius * 3/2 }, 0.f, WHITE);

        


        attack.debugDraw(position);
    }
};