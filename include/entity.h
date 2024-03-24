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

    float hp;
    float maxHP;

    float damage;

    int gold;
    int heals;

    float dashTrace;

    float radius;
    float speed;

    bool flagDeath;

    Direction dir;

    AttackBox attack;

    Texture2D* tex;

    EntityType type;

    void init(float x, float y, EntityType ty) {
        position = {x, y};
        moveVelocity = { 0.f, 0.f };
        actionVelocity = { 0.f, 0.f };

        type = ty;
        heals = 0;

        flagDeath = false;

        dir = NORTH;

        tex = NULL;

        switch (type) {
            case PLAYER:
                gold = 0;
                radius = 25.f;
                speed = 350;
                hp = 100.f;
                maxHP = hp;
                damage = 25.f;
                attack.init(70, 50, .3f, .05f, false);
                break;
            case HUMAN:
                gold = 100;
                radius = 35.f;
                speed = 250;
                hp = 50.f;
                maxHP = hp;
                damage = 0.f;
                break;
            case GHOST:
                gold = 10;
                radius = 20.f;
                speed = 550;
                hp = 20.f;
                maxHP = hp;
                damage = 15.f;
                break;
            case WIZARD:
                gold = 5000;
                radius = 40.f;
                speed = 450;
                hp = 100.f;
                maxHP = hp;
                damage = 25.f;
                break;
            case GRANDW:
                gold = 100000;
                radius = 80.f;
                speed = 600;
                hp = 1000.f;
                maxHP = hp;
                damage = 25.f;
                break;
            case PROJECTILE:
                radius = 5.f;
                speed = 1000;
                hp = 1.f;
                maxHP = hp;
                damage = 10.f;
                attack.init(10, 100, 1.f, .0f, true);
        }
    }

    void takeDamage(float dmg) {
        hp -= dmg;
        checkDeath();
    }

    void checkDeath() {
        if (hp > 0) return;

        flagDeath = true;
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

    bool update(Map* map, bool* switchMapFlag, float dt) {
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

            if (iX < 0 || iY < 0 || iX >= map->width || iY >= map->height) continue;

            if (map->mapCollisionData[iY * map->width + iX] == NONE) continue;
            
            Rectangle rec = {(float) (iX * map->tileSize), (float) (iY * map->tileSize), (float) map->tileSize, (float) map->tileSize};

            bool collide = vix::check_collision_circle_rec_this(position, radius, rec);

            if (!collide) continue;

            if (map->mapCollisionData[iY * map->width + iX] == DOOR && type == PLAYER) {
                *switchMapFlag = true;
                std::cout << "raise map switch flag" << std::endl;
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
};