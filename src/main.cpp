#include <../include/raylib.h>
#include <../include/game.h>
#include <../include/menu.h>

#include <stdio.h>

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(SCREEN_W, SCREEN_H, "template");
    
    Game game;
    game.init();

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