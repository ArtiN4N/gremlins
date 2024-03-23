#include <../include/raylib.h>
#include <../include/defs.h>
#include <stdio.h>

int SCREEN_W = 1600;
int SCREEN_H = 800;

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(SCREEN_W, SCREEN_H, "template");

    while (!WindowShouldClose()) {
        //float dt = GetFrameTime();

        BeginDrawing();

        ClearBackground(BLACK);
        
        DrawFPS(20, 20);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}