#pragma once

#include <stdio.h>
#include <raylib.h>
#include <../include/game.h>

void MainMenu(Game& game) {
    BeginDrawing();
    ClearBackground(BLACK);

    Rectangle sourceRec = { 0.0f, 0.0f, (float)game.menuImage.width, (float)game.menuImage.height };

    Rectangle destRec = { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() };

    // draw backgroudd img scaled to the screen size
    DrawTexturePro(game.menuImage, sourceRec, destRec, (Vector2){ 0, 0 }, 0.0f, WHITE);

    DrawText("Gremlin Massacre 2: A Gremlin's Revenge", GetScreenWidth() / 2 - MeasureText("Gremlin Massacre 2: A Gremlin's Revenge", 40) / 2, GetScreenHeight() / 4 - 40, 40, WHITE);

    // Draw the play button
    DrawRectangle(GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 - 50, 200, 50, BLUE);
    DrawText("Play", GetScreenWidth() / 2 - MeasureText("Play", 30) / 2, GetScreenHeight() / 2 - 40, 30, WHITE);
    Rectangle play_button = { float(GetScreenWidth() / 2 - 100), float(GetScreenHeight() / 2 - 50), 200, 50 };

    // Draw the settings button
    DrawRectangle(GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 10, 200, 50, BLUE);
    DrawText("Settings", GetScreenWidth() / 2 - MeasureText("Settings", 30) / 2, GetScreenHeight() / 2 + 20, 30, WHITE);
    Rectangle settings_button = { float(GetScreenWidth() / 2 - 100), float(GetScreenHeight() / 2 + 10), 200, 50 };

    // Credits:
    DrawText("Created by: ", GetScreenWidth() / 2 - MeasureText("Created by: ", 20) / 2, GetScreenHeight() / 2 + 200, 20, WHITE);
    DrawText("Arshia T.", GetScreenWidth() / 2 - MeasureText("Arshia T.", 20) / 2, GetScreenHeight() / 2 + 220, 20, WHITE);
    DrawText("Cohen T.H.", GetScreenWidth() / 2 - MeasureText("Cohen T.H.", 20) / 2, GetScreenHeight() / 2 + 240, 20, WHITE);
    DrawText("Daffodil H.", GetScreenWidth() / 2 - MeasureText("Daffodil H.", 20) / 2, GetScreenHeight() / 2 + 260, 20, WHITE);
    DrawText("Julian M.", GetScreenWidth() / 2 - MeasureText("Julian M.", 20) / 2, GetScreenHeight() / 2 + 280, 20, WHITE);
    DrawText("Saarang A.", GetScreenWidth() / 2 - MeasureText("Saarang A.", 20) / 2, GetScreenHeight() / 2 + 300, 20, WHITE);

    Vector2 mousePos = GetMousePosition();

    if (CheckCollisionPointRec(mousePos, play_button) || CheckCollisionPointRec(mousePos, settings_button)){
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        }
    else
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    if (CheckCollisionPointRec(GetMousePosition(), play_button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        game.inMainMenu = false;
    }

    EndDrawing();
}