#include <../include/raylib.h>
#include <../include/defs.h>
#include <stdio.h>

int SCREEN_W = 1600;
int SCREEN_H = 800;


struct Entity {
    Vector2 position;
    float radius;

    void init(float x, float y, float rad) {
        position = {x, y};
        radius = rad;
    }

    void draw() {
        DrawCircleV(position, radius, RED);
    }
};

struct Viewport {
    Camera2D camera;
    Entity* follow;

    void init(Entity* following) {
        camera = {0};
        
        camera.offset = { SCREEN_W / 2.f, SCREEN_H / 2.f };
        camera.rotation = 0.f;
        camera.zoom = 1.f;

        follow = following;
    }

    void update() {
        camera.target = follow->position;
    }
};

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(SCREEN_W, SCREEN_H, "template");

    Entity player;
    player.init(200, 100, 100);

    Viewport cam;
    cam.init(&player);

    while (!WindowShouldClose()) {
        //float dt = GetFrameTime();

        cam.update();

        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode2D(cam.camera);

        player.draw();

        EndMode2D();
        
        DrawFPS(20, 20);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}