#include <../include/raylib.h>
#include <../include/defs.h>
#include <stdio.h>

int SCREEN_W = 1600;
int SCREEN_H = 800;


struct Entity {
    Vector2 position;

    void draw() {
        DrawCircleV(position, 10, RED);
    }
};

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(SCREEN_W, SCREEN_H, "template");

    Entity player;
    player.position = {100, 100};

    while (!WindowShouldClose()) {
        //float dt = GetFrameTime();

        BeginDrawing();

        ClearBackground(BLACK);

        player.draw();
        
        DrawFPS(20, 20);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}