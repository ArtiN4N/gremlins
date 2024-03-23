#include <../include/raylib.h>
#include <../include/defs.h>
#include <../include/entity.h>

#include <stdio.h>
#include <cmath>




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

        DrawText(TextFormat("elapsed: %.2f\n active: %d\n ready: %d\n player vel: { %.2f, %.2f }", player.attack.elapsed, player.attack.active, player.attack.ready, player.velocity.x, player.velocity.y), 10, 40, 10, WHITE);
        
        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}