#pragma once

#include <raylib.h>
#include <defs.h>
#include <entity.h>
#include <camera.h>
#include <player.h>

#include <vector>

struct Game {
    Entity player;
    Viewport cam;
    Texture2D background;
    bool inMainMenu = true;

    std::vector<Entity> enemyList;
    std::vector<Entity> projectileList;

    void init() {
        player.init(200, 100, 25, 350);
        playerInitAttacks(&player);
        
        cam.init(&player);
    }

    void input(float dt) {
        playerInputHandle(&player, &projectileList, dt);
    }

    void update(float dt) {
        for (Entity e : projectileList) {
            e.update(dt);
        }

        for (Entity e : enemyList) {
            e.update(dt);
        }

        player.update(dt);

        cam.update();
    }

    void draw() {
        ClearBackground(BLACK);
        BeginMode2D(cam.camera);

        DrawCircle(10, 10, 20, BLUE);

        for (Entity e : projectileList) {
            e.draw();
        }

        for (Entity e : enemyList) {
            e.draw();
        }

        player.draw();

        EndMode2D();

        DrawText(TextFormat("elapsed: %.2f\n active: %d\n ready: %d\n player vel: { %.2f, %.2f }", player.attack.elapsed, player.attack.active, player.attack.ready, player.velocity.x, player.velocity.y), 10, 40, 10, WHITE);
        
        DrawFPS(10, 10);
    }
};