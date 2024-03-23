#include <../include/raylib.h>
#include <../include/defs.h>
#include <stdio.h>

int SCREEN_W = 1600;
int SCREEN_H = 800;

enum Direction { NORTH = 0, EAST, SOUTH, WEST };

struct AttackBox {
    Vector2 offset;
    Vector2 size;
    Vector2 realSize;

    void init(float width, float height) {
        size = {width, height};
        realSize = size;
    }

    void update(Direction parentDir, float parentRad) {
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
    }

    void debugDraw(Vector2 parentPos) {
        Vector2 drawPos = { parentPos.x + offset.x, parentPos.y + offset.y };

        DrawRectangleV(drawPos, realSize, {0, 0, 255, 120});
    }
};

struct Entity {
    Vector2 position;
    float radius;
    float speed;

    Direction dir;

    AttackBox attack;

    void init(float x, float y, float rad, float spd) {
        position = {x, y};
        radius = rad;

        speed = spd;

        dir = NORTH;

        attack.init(200, 50);
    }

    void update(float dt) {
        
        if (IsKeyDown(KEY_A)) {
            position.x -= speed * dt;
            dir = WEST;
        }
        if (IsKeyDown(KEY_D)) {
            position.x += speed * dt;
            dir = EAST;
        }
        if (IsKeyDown(KEY_W)) {
            position.y -= speed * dt;
            dir = NORTH;
        }
        if (IsKeyDown(KEY_S)) {
            position.y += speed * dt;
            dir = SOUTH;
        }

        attack.update(dir, radius);
    }

    void draw() {
        DrawCircleV(position, radius, RED);
        attack.debugDraw(position);
    }
};

struct Viewport {
    Camera2D camera;
    Entity* parent;

    void init(Entity* following) {
        camera = {0};
        
        camera.offset = { SCREEN_W / 2.f, SCREEN_H / 2.f };
        camera.rotation = 0.f;
        camera.zoom = 1.f;

        parent = following;
    }

    void update() {
        camera.target = parent->position;
    }
};

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(SCREEN_W, SCREEN_H, "template");

    Entity player;
    player.init(200, 100, 25, 350);

    Viewport cam;
    cam.init(&player);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // UPDATE
        player.update(dt);
        cam.update();

        // DRAW
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(cam.camera);

        DrawCircle(10, 10, 20, BLUE);

        player.draw();

        EndMode2D();
        
        DrawFPS(20, 20);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}