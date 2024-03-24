#pragma once

#include <raylib.h>
#include <defs.h>
#include <entity.h>
#include <camera.h>
#include <player.h>

#include "col.hpp"
#include "Map.hpp"

#include <vector>

struct Game {
    Entity player;
    Viewport cam;

    std::vector<Entity> enemyList;
    std::vector<Entity> projectileList;

    //std::vector<vix::game_object> obstacles;

    void init() {
        player.init(200, 100, 25, 350);
        playerInitAttacks(&player);
        
        cam.init(&player);

        vix::initMap(new_piskel_data, NEW_PISKEL_FRAME_WIDTH, NEW_PISKEL_FRAME_HEIGHT);
        //draw_image_and_push_to_vector(new_piskel_data, NEW_PISKEL_FRAME_WIDTH, NEW_PISKEL_FRAME_HEIGHT, obstacles);
    }

    void input(float dt) {
        playerInputHandle(&player, &projectileList, dt);
    }

    void update(float dt) {
        for (auto iter = projectileList.begin(); iter != projectileList.end(); iter++) {
            int index = std::distance(projectileList.begin(), iter);

            bool alive = projectileList[index].update(map_data, dt);
            
            if (!alive) {
                projectileList.erase(projectileList.begin() + index);
                iter--;
            }
        }

        for (auto iter = enemyList.begin(); iter != enemyList.end(); iter++) {
            int index = std::distance(projectileList.begin(), iter);

            bool alive = enemyList[index].update(map_data, dt);
            
            if (!alive) {
                enemyList.erase(enemyList.begin() + index);
                iter--;
            }
        }

        player.update(map_data, dt);

        cam.update();
    }

    void draw() {
        ClearBackground(BLACK);
        BeginMode2D(cam.camera);

        for (int iY = 0; iY < NEW_PISKEL_FRAME_HEIGHT; iY++) {
            for (int iX = 0; iX < NEW_PISKEL_FRAME_WIDTH; iX++) {
                if (!map_data[iY * NEW_PISKEL_FRAME_WIDTH + iX]) {
                    DrawRectangle(iX * TILE_SIZE, iY * TILE_SIZE, TILE_SIZE, TILE_SIZE, RED);
                }   
            }
        }

        for (Entity e : projectileList) {
            e.draw();
        }

        for (Entity e : enemyList) {
            e.draw();
        }

        player.draw();

        EndMode2D();

        //DrawText(TextFormat("elapsed: %.2f\n active: %d\n ready: %d\n player vel: { %.2f, %.2f }", player.attack.elapsed, player.attack.active, player.attack.ready, player.velocity.x, player.velocity.y), 10, 40, 10, WHITE);
        
        DrawFPS(10, 10);
    }
};