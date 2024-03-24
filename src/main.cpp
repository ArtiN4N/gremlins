#include <../include/raylib.h>
#include <../include/game.h>
#include <../include/menu.h>

#include <stdio.h>
#include <iostream>

int main() {
    std::cout << "main" << std::endl;
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(SCREEN_W, SCREEN_H, "template");

    Game game;
    std::cout << "starting init" << std::endl;
    game.init();
    std::cout << "done init" << std::endl;

    while (!WindowShouldClose()) {
        if (game.inMainMenu) {
            SetWindowTitle("GM2: Menu");
            MainMenu(game);
        } else {
            SetWindowTitle("GM2: A Gremlin's Revenge");
            float dt = GetFrameTime();

            game.input(dt);
            game.update(dt);

            BeginDrawing();
            game.draw();
            EndDrawing();
        }
    }

    game.unload();

    CloseWindow();
    return 0;
}