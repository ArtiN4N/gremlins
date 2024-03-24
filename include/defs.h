#pragma once

#include <iostream>

#define TILE_SIZE 64

int SCREEN_W = 1600;
int SCREEN_H = 800;

enum Direction { NORTH = 0, EAST, SOUTH, WEST };

enum EntityType { HUMAN = 0, WIZARD, GRANDW, GHOST, PLAYER, PROJECTILE };

struct EnemyInfo {
    EntityType type;
    Vector2 spawn;
};

struct AttackBox {
    Vector2 offset;
    Vector2 size;
    Vector2 realSize;

    bool projectile;

    bool active;
    bool ready;

    float elapsed;
    float maxActive;
    float maxCooldown;

    void init(float width, float height, float mActive, float mCool, bool proj) {
        size = {width, height};
        realSize = size;

        active = false;
        ready = true;

        projectile = proj;

        elapsed = 0.f;
        maxActive = mActive;
        maxCooldown = mCool;
    }

    bool update(Direction parentDir, float parentRad, float dt) {
        if (projectile) {
            
            switch (parentDir) {
                case NORTH:
                    realSize = size;
                    offset = { -realSize.x / 2.f, -realSize.y / 2.f };
                    break;
                case EAST:
                    realSize = {size.y, size.x};
                    offset = { -realSize.x / 2.f, -realSize.y / 2.f };
                    break;
                case SOUTH:
                    realSize = size;
                    offset = { -realSize.x / 2.f, -realSize.y / 2.f };
                    break;
                case WEST:
                    realSize = {size.y, size.x};
                    offset = { -realSize.x / 2.f, -realSize.y / 2.f };
                    break;
            }

            active = true;

            elapsed += dt;

            if (elapsed > maxActive) {
                return false;
            }
            return true;
        }

        switch (parentDir) {
            case NORTH:
                realSize = size;
                offset = { -realSize.x / 2.f, -(realSize.y + parentRad) };
                break;
            case EAST:
                realSize = {size.y, size.x};
                offset = { parentRad, -realSize.y / 2.f };
                break;
            case SOUTH:
                realSize = size;
                offset = { -realSize.x / 2.f, parentRad };
                break;
            case WEST:
                realSize = {size.y, size.x};
                offset = { -(realSize.x + parentRad), -realSize.y / 2.f };
                break;
        }

        if (active) {
            ready = false;
            elapsed += dt;
        }
        else if (!ready) elapsed += dt;
        
        if (!active && !ready && elapsed >= maxCooldown) {
            elapsed = 0.f;
            ready = true;
        }

        if (active && elapsed >= maxActive) {
            elapsed = 0.f;
            active = false;
        }

        return true;
    }

    void debugDraw(Vector2 parentPos) {
        if (!active) return;

        Vector2 drawPos = { parentPos.x + offset.x, parentPos.y + offset.y };
        DrawRectangleV(drawPos, realSize, {0, 0, 255, 120});
    }
};