#pragma once

#include <raylib.h>
#include <defs.h>
#include "map.h"
#include <entity.h>
#include <camera.h>
#include <player.h>
#include <enemy.h>

#include "sprites.h"

#include "col.hpp"


#include <vector>

struct Game {
    Entity player;

    PlayerSprites playerSprites;
    HumanSprites humanSprites;
    GhostSprites ghostSprites;
    WizardSprites wizardSprites;
    GwizardSprites GWizardSprites;

    Map map;

    Viewport cam;
    Texture2D menuImage;
    
    bool inMainMenu;

    bool switchMapFlag;

    bool flagRestart;

    std::vector<Entity> enemyList;
    std::vector<Entity> projectileList;

    void init() {
        flagRestart = false;

        map.setup();
        
        std::vector<EnemyInfo> enemyInfo = {};
        map.initMap(4, &enemyInfo);

        switchMapFlag = false;

        playerSprites.init();
        humanSprites.init();
        ghostSprites.init();
        wizardSprites.init();
        GWizardSprites.init();

        std::cout << "loaded sprites" << std::endl;

        Vector2 spawn = map.getSpawnPos();
        
        player.init(spawn.x, spawn.y, PLAYER);
        playerSprites.initEntity(&player);

        std::cout << "inited player" << std::endl;

        addEntities(enemyInfo);

        std::cout << "added enemies" << std::endl;
        
        cam.init(&player);
        cam.camera.zoom = map.getMapZoom();

        Image menuData = LoadImage("assets/maps/map1.png");
        menuImage = LoadTextureFromImage(menuData);
        UnloadImage(menuData);

        inMainMenu = true;
    }

    void addEntities(std::vector<EnemyInfo> entityInfo) {
        std::cout << "looping through enemy infos..." << std::endl;
        for (EnemyInfo info : entityInfo) {
            std::cout << "craeting enemy";
            std::cout << " at xPos: " << info.spawn.x << std::endl;
            Entity enemy;
            enemy.init(info.spawn.x, info.spawn.y, info.type);

            switch (info.type) {
                case HUMAN:
                    humanSprites.initEntity(&enemy);
                    break;
                case GHOST:
                    ghostSprites.initEntity(&enemy);
                    break;
                case WIZARD:
                    wizardSprites.initEntity(&enemy);
                    break;
                case GRANDW:
                    GWizardSprites.initEntity(&enemy);
                    break;
                default:
                    break;
            }

            enemyList.push_back(enemy);
        }
    }

    void input(float dt) {
        playerInputHandle(&player, &enemyList, &projectileList, dt);

        if (IsKeyPressed(KEY_EQUAL)) cam.camera.zoom += .25f;
        if (IsKeyPressed(KEY_MINUS)) cam.camera.zoom -= .25f;

        if (cam.camera.zoom < .25f) cam.camera.zoom = .25f;
    }

    void update(float dt) {

        for (auto iter = projectileList.begin(); iter != projectileList.end(); iter++) {
            int index = std::distance(projectileList.begin(), iter);

            bool alive = projectileList[index].update(&map, &switchMapFlag, dt);
            
            if (!alive) {
                projectileList.erase(projectileList.begin() + index);
                iter--;
            }
        }

        for (auto iter = enemyList.begin(); iter != enemyList.end(); iter++) {
            int index = std::distance(projectileList.begin(), iter);

            enemyList[index].update(&map, &switchMapFlag, dt);
            basicAI(&enemyList[index], &player, dt);

            if (enemyList[index].flagDeath) {
                enemyList.erase(enemyList.begin() + index);
                iter--;
            }
        }

        player.update(&map, &switchMapFlag, dt);
        if (player.flagDeath) {
            flagRestart = true;
        }

        if (player.attack.active) {
            for (Entity enemy : enemyList) {
                if (enemy.radius + player.radius < Vector2Distance(enemy.position, player.position)) {
                    enemy.takeDamage(player.damage);
                }
            }
        }

        if (switchMapFlag) {
            

            std::vector<EnemyInfo> enemyInfo;
            map.switchMap(map.getNewMap(player.position), &enemyInfo);

            enemyList.clear();

            player.position = map.getSpawnPos();
            switchMapFlag = false;

            std::cout << "# of enemies: " << enemyInfo.size() << std::endl;
            addEntities(enemyInfo);
        }

        cam.update();
    }

    void draw() {
        ClearBackground(BLACK);
        BeginMode2D(cam.camera);


        //Texture2D mapTex = map.mapTextures[3];

        
        Texture2D mapTex = *(map.currentMapTex);

        Rectangle sourceRec = { 0.0f, 0.0f, (float) mapTex.width, (float) mapTex.height };

        Rectangle destRec = { 0, 0, (float) mapTex.width, (float) mapTex.height };

        // draw backgroudd img scaled to the screen size
        DrawTexturePro(mapTex, sourceRec, destRec, (Vector2){ 0, 0 }, 0.0f, WHITE);

        

        for (int iY = 0; iY < map.height; iY++) {
            for (int iX = 0; iX < map.width; iX++) {
                if (map.mapCollisionData[iY * map.width + iX] != NONE) {
                    Color color = RED;
                    if (map.mapCollisionData[iY * map.width + iX]) color = BLUE;
                    DrawRectangle(iX * map.tileSize, iY * map.tileSize, map.tileSize, map.tileSize, color);
                }   
            }
        }

        for (Entity e : enemyList) {
            switch (e.type) {
                case HUMAN:
                    humanSprites.draw(e);
                    break;
                case GHOST:
                    ghostSprites.draw(e);
                    break;
                case WIZARD:
                    wizardSprites.draw(e);
                    break;
                case GRANDW:
                    GWizardSprites.draw(e);
                    break;
                default:
                    break;
            }
        }

        playerSprites.draw(player);

        EndMode2D();

        DrawFPS(10, 10);
    }

    void unload() {
        UnloadTexture(menuImage);

        playerSprites.unload();
        humanSprites.unload();
        ghostSprites.unload();
        wizardSprites.unload();
        GWizardSprites.unload();

        map.unloadMap();
        enemyList.clear();
        map.teardown();
    }
};