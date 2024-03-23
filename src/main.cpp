#include <../include/raylib.h>
#include <../include/game.h>

#include <stdio.h>

#include "col.hpp"

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(SCREEN_W, SCREEN_H, "template");

    Game game;
    game.init();

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        game.input(dt);
        game.update(dt);

        BeginDrawing();
        game.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}