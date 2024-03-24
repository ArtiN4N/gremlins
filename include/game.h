#pragma once

#include <raylib.h>
#include <defs.h>
#include <entity.h>
#include <camera.h>
#include <player.h>

#include "col.hpp"
#include "FULLmap4.h"

#include <vector>

struct Game {
    Entity player;
    Entity enemy;

    PlayerSprites playerSprites;

    Map map;

    Viewport cam;
    Texture2D menuImage;
    Texture2D mapImage;
    bool inMainMenu;

    std::vector<Entity> enemyList;
    std::vector<Entity> projectileList;

    void init() {
        map.initMap(1);

        player.type = PLAYER;
        enemy.type = ENEMY;

        playerSprites.init();
        
        Vector2 spawn = map.getSpawnPos();
        player.init(spawn.x, spawn.y, 25, 350);
        playerInit(&player, &playerSprites);

        Vector2 playerPos = player.position;
        int numEnemies = 1;
        for (int i = 0; i < numEnemies; i++) {
        Entity enemy;
        enemy.type = ENEMY;
        enemy.init(playerPos.x, playerPos.y, 25, 200);
        enemyList.push_back(enemy);
    }
        
        cam.init(&player);
        cam.camera.zoom = map.getMapZoom();

        Image menuData = LoadImage("assets/maps/map1.png");
        menuImage = LoadTextureFromImage(menuData);
        UnloadImage(menuData);

        Image mapData = LoadImage("assets/maps/FULLmap2.png");
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

            bool alive = projectileList[index].update(&player, map, dt);
            
            if (!alive) {
                projectileList.erase(projectileList.begin() + index);
                iter--;
            }
        }

        for (Entity& enemy : enemyList) {
        enemy.update(&player, map, dt);
    }

        for (auto iter = enemyList.begin(); iter != enemyList.end(); iter++) {
            int index = std::distance(enemyList.begin(), iter);
            if (!index >= 0 || !index < enemyList.size()) break;

            
            bool alive = enemyList[index].update(&player, map, dt);

            if (!alive) {
                enemyList.erase(enemyList.begin() + index);
                iter--;
            }

        }

        player.update(&player, map, dt);

        cam.update();
    }

    void draw() {
        ClearBackground(BLACK);
        BeginMode2D(cam.camera);

        Rectangle sourceRec = { 0.0f, 0.0f, (float) mapImage.width, (float) mapImage.height };

        Rectangle destRec = { 0, 0, (float) mapImage.width, (float) mapImage.height };

        // draw backgroudd img scaled to the screen size
        DrawTexturePro(mapImage, sourceRec, destRec, (Vector2){ 0, 0 }, 0.0f, WHITE);

        for (int iY = 0; iY < map.height; iY++) {
            for (int iX = 0; iX < map.width; iX++) {
                if (map.mapCollisionData[iY * map.width + iX] != NONE) {
                    Color color = RED;
                    if (map.mapCollisionData[iY * map.width + iX]) color = BLUE;
                    DrawRectangle(iX * map.tileSize, iY * map.tileSize, map.tileSize, map.tileSize, color);
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
        map.unloadMap();
    }
};