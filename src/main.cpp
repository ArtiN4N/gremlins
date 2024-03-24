#include <../include/raylib.h>
#include <../include/game.h>
#include <../include/menu.h>

#include <stdio.h>
#include <iostream>

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(SCREEN_W, SCREEN_H, "template");

    Game game;

    BeginDrawing();
            ClearBackground(BLACK);
            DrawText("wasd move, z attack, x dash, a heal\n loading", 0, SCREEN_H / 2, 50.f, WHITE);
            EndDrawing();

    game.init();

    while (!WindowShouldClose()) {
        if (game.inMainMenu) {
            SetWindowTitle("GM2: Menu");
            MainMenu(game);
            UpdateMusicStream(game.menuMusic);
        } else {
            SetWindowTitle("GM2: A Gremlin's Revenge");
            float dt = GetFrameTime();

            game.input(dt);
            game.update(dt);
            UpdateMusicStream(game.menuMusic);

            BeginDrawing();
            game.draw();
            EndDrawing();
        }

        if (game.flagRestart) {
            printf("you died!\n");
            game.unload();
            game = {};
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("wasd move, z attack, x dash, a heal\n loading", 0, SCREEN_H / 2, 50.f, WHITE);
            EndDrawing();
            game.init();
        }
    }

    game.unload();

    CloseWindow();
    return 0;
}