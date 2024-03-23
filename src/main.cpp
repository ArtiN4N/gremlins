#include <../include/raylib.h>
#include <../include/defs.h>
#include <stdio.h>

int SCREEN_W = 1600;
int SCREEN_H = 800;


struct Entity {
    Vector2 position;
    float radius;
    float speed;

    void init(float x, float y, float rad, float spd) {
        position = {x, y};
        radius = rad;

        speed = spd;
    }

    void draw() {
        DrawCircleV(position, radius, RED);
    }
};

struct AttackBox {
    Entity* parent;
    Vector2 offset;

    Vector2 size;

    void init(Entity* follow, float offX, float offY, float width, float height) {
        parent = follow;
        offset = {offX, offY};
        size = {width, height};
    }

    void debugDraw() {
        Vector2 drawPos = { parent->position.x + offset.x, parent->position.y + offset.y };
        DrawRectangleV(drawPos, size, {0, 0, 255, 120});
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
    player.init(200, 100, 100, 350);

    Viewport cam;
    cam.init(&player);

    AttackBox example;
    example.init(&player, -15, -(30+100), 30, 30);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // INPUT
        if (IsKeyDown(KEY_W)) player.position.y -= player.speed * dt;
        if (IsKeyDown(KEY_A)) player.position.x -= player.speed * dt;
        if (IsKeyDown(KEY_S)) player.position.y += player.speed * dt;
        if (IsKeyDown(KEY_D)) player.position.x += player.speed * dt;

        // UPDATE
        cam.update();

        // DRAW
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(cam.camera);

        player.draw();
        example.debugDraw();

        DrawCircle(10, 10, 20, BLUE);

        EndMode2D();
        
        DrawFPS(20, 20);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}