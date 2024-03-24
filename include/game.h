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

#include "item_driver.h"

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

    //item system
    std::vector<uint32_t> inventory;

    void init() {
        flagRestart = false;

        map.setup();
        
        std::vector<EnemyInfo> enemyInfo = {};
        map.initMap(3, &enemyInfo);

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

        //item system
        vix::items_list.push_back(vix::item_driver{ {spawn.x-100, spawn.y-100}, 30 , vix::item_type::COIN});
        vix::items_list.push_back(vix::item_driver{ {spawn.x-200, spawn.y-200}, 20, vix::item_type::COIN });
        vix::items_list.push_back(vix::item_driver{ {spawn.x-300, spawn.y-300}, 25, vix::item_type::COIN });
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
        std::cout << "done enemies" << std::endl;
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
        std::cout << "done enemies" << std::endl;
    }

    void input(float dt) {
        playerInputHandle(&player, &projectileList, dt);

        if (IsKeyPressed(KEY_EQUAL)) cam.camera.zoom += .25f;
        if (IsKeyPressed(KEY_MINUS)) cam.camera.zoom -= .25f;

        if (cam.camera.zoom < .25f) cam.camera.zoom = .25f;
    }

    void update(float dt) {

        std::cout << "updating proj" << std::endl;

        for (auto iter = projectileList.begin(); iter != projectileList.end(); iter++) {
            int index = std::distance(projectileList.begin(), iter);

            bool alive = projectileList[index].update(&map, &switchMapFlag, dt);
            
            if (!alive) {
                projectileList.erase(projectileList.begin() + index);
                iter--;
            }
        }

        for (auto iter = enemyList.begin(); iter != enemyList.end(); iter++) {
            int index = std::distance(enemyList.begin(), iter);

            enemyList[index].update(&map, &switchMapFlag, dt);
            basicAI(&enemyList[index], &player, dt);

            if (enemyList[index].flagDeath) {
                enemyList.erase(enemyList.begin() + index);
                iter--;
            }
        }

        std::cout << "updating player" << std::endl;

        player.update(&map, &switchMapFlag, dt);
        if (player.flagDeath) {
            flagRestart = true;
        }

        if (player.attack.active) {
            for (Entity& enemy : enemyList) {
                
                if (enemy.radius + player.radius > Vector2Distance(enemy.position, player.position)) {
                    player.attack.active = false;
                    enemy.takeDamage(player.damage);
                    if (enemy.flagDeath) {
                        player.gold += enemy.gold;
                    }
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
            e.draw();
        }


        //item system
        size_t items_list_length = vix::items_list.size();

        for (size_t i = 0; i<items_list_length; i++) {
            vix::items_list[i].draw();
            if (vix::items_list[i].check_collision(player.position, player.radius)) {
                 inventory.push_back(vix::items_list[i].item_type);
                 vix::items_list.erase(vix::items_list.begin()+i);
                 items_list_length--;

                 std::cout<<"Hit"<<std::endl;
            }
        }

        player.draw();

        EndMode2D();

        DrawFPS(10, 10);

        DrawText(TextFormat("GOLD = $%d", player.gold), 10, 40, 40, YELLOW);
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