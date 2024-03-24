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
    PlayerSprites playerSprites;

    Viewport cam;
    Texture2D menuImage;
    Texture2D mapImage;
    bool inMainMenu;

    std::vector<Entity> enemyList;
    std::vector<Entity> projectileList;

    void init() {
        playerSprites.init();

        player.init(200, 100, 25, 350);
        playerInit(&player, &playerSprites);
        
        cam.init(&player);

        vix::initMap(new_piskel_data, NEW_PISKEL_FRAME_WIDTH, NEW_PISKEL_FRAME_HEIGHT);

        Image menuData = LoadImage("assets/maps/map1.png");
        menuImage = LoadTextureFromImage(menuData);
        UnloadImage(menuData);

        Image mapData = LoadImage("assets/maps/FULLmap3.png");
        mapImage = LoadTextureFromImage(mapData);
        UnloadImage(mapData);

        inMainMenu = true;
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

        Rectangle sourceRec = { 0.0f, 0.0f, (float) mapImage.width, (float) mapImage.height };

        Rectangle destRec = { 0, 0, (float) mapImage.width, (float) mapImage.height };

        // draw backgroudd img scaled to the screen size
        DrawTexturePro(mapImage, sourceRec, destRec, (Vector2){ 0, 0 }, 0.0f, WHITE);

        

        for (int iY = 0; iY < NEW_PISKEL_FRAME_HEIGHT; iY++) {
            for (int iX = 0; iX < NEW_PISKEL_FRAME_WIDTH; iX++) {
                if (map_data[iY * NEW_PISKEL_FRAME_WIDTH + iX]) {
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

        DrawFPS(10, 10);
    }

    void unload() {
        UnloadTexture(menuImage);
        UnloadTexture(mapImage);
        playerSprites.unload();
    }
};