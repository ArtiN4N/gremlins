#pragma once

int SCREEN_W = 1600;
int SCREEN_H = 800;

enum Direction { NORTH = 0, EAST, SOUTH, WEST };

struct AttackBox {
    Vector2 offset;
    Vector2 size;
    Vector2 realSize;

    bool active;
    bool ready;

    float elapsed;
    float maxActive;
    float maxCooldown;

    void init(float width, float height, float mActive, float mCool) {
        size = {width, height};
        realSize = size;

        active = false;
        ready = true;

        elapsed = 0.f;
        maxActive = mActive;
        maxCooldown = mCool;
    }

    void update(Direction parentDir, float parentRad, float dt) {
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
    }

    void debugDraw(Vector2 parentPos) {
        if (!active) return;

        Vector2 drawPos = { parentPos.x + offset.x, parentPos.y + offset.y };
        DrawRectangleV(drawPos, realSize, {0, 0, 255, 120});
    }
};