#pragma once

#include "raylib.h"

#include <cstdlib>

#include "defs.h"

#include <vector>

#include "FULLmap1.h"
#include "FULLmap2.h"
#include "FULLmap3.h"
#include "FULLmap4.h"
#include "FULLmap5.h"

enum CollisionType { WALL = 0, DOOR, NONE };

unsigned int mapSizes[10][2] = {
    {64, 64},
    {64, 64},
    {48, 64},
    {64, 43},
    {64, 39},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0}
};

Vector2 mapSpawns[10][2] = {
    {{128, 1300}, {4000, 1300}},
    {{1920, 128}, {1500, 4000}},
    {{2900, 1000}, {1530, 4000}},
    {{300, 300}, {3650, 2000}},
    {{128, 1664}, {128, 1664}},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0}
};

std::vector<EnemyInfo> mapEnemies[10] = {}; 
std::vector<Vector2> mapItems[10] = {}; 

struct Map {
    int width;
    int height;

    int tileSize;

    int mapNum;
    int oldMapNum;

    CollisionType* mapCollisionData;

    Texture2D mapTextures[5];
    Texture2D* currentMapTex;

    void setup() {
        mapNum = 0;
        oldMapNum = 0;

        for (int i = 0; i < 5; i++) {
            Image mapData = LoadImage(TextFormat("assets/maps/FULLmap%d.png", i+1));
            Texture2D mapImage = LoadTextureFromImage(mapData);
            UnloadImage(mapData);

            mapTextures[i] = mapImage;
        }
        
        currentMapTex = NULL;

        map1Setup(&(mapEnemies[0]));
        map2Setup(&(mapEnemies[1]));
        map3Setup(&(mapEnemies[2]));
        map4Setup(&(mapEnemies[3]));
        map5Setup(&(mapEnemies[4]));
        //map6Setup();
        //map7Setup();
        //map8Setup();
        //map9Setup();
        //map10Setup();
    }   

    void initMap(int map, std::vector<EnemyInfo>* enemyInfo) {
        oldMapNum = mapNum;

        mapNum = map;

        currentMapTex = &(mapTextures[mapNum - 1]);

        width = mapSizes[map - 1][0];
        height = mapSizes[map - 1][1];

        mapCollisionData = (CollisionType*) malloc(sizeof(CollisionType) * mapSizes[map - 1][0] * mapSizes[map - 1][1]);

        unsigned int* image_data;
        tileSize = 64;
        switch (mapNum) {
            case 1:
                image_data = fullmap1_data;
                break;
            case 2:
                image_data = fullmap2_data;
                break;
            case 3:
                image_data = fullmap3_data;
                break;
            case 4:
                image_data = fullmap4_data;
                break;
            case 5:
                image_data = fullmap5_data;
                break;
            default:
                image_data = fullmap4_data;
                break;
        }

        for (unsigned int y = 0; y < mapSizes[map - 1][1]; y++) {
            for (unsigned int x = 0; x < mapSizes[map - 1][0]; x++) {
                //Get pixel color
                uint32_t pixel = image_data[y * width + x];

                if (pixel == 0xff285f4d) mapCollisionData[y * width + x] = WALL;
                else if (pixel == 0xff0000ff) mapCollisionData[y * width + x] = DOOR;
                else mapCollisionData[y * width + x] = NONE;
            }
        }


        *enemyInfo = mapEnemies[mapNum - 1];
        std::cout << "new enemies size = " << enemyInfo->size() << std::endl;
    }

    float getMapZoom() {
        switch (mapNum) {
            case 1:
                return .5f;
            case 2:
                return .5f;
            case 3:
                return 1.f;
            case 4: 
                return 1.f;
            case 5:
                return .75f;
            default:
                return 1.f;
        }
    }

    Vector2 getSpawnPos() {
        int version = 0;
        switch (mapNum) {
            case 1:
                if (oldMapNum != 2) version = 1;
                break;
            case 2:
                if (oldMapNum != 3) version = 1;
                break;
            case 3:
                if (oldMapNum != 4) version = 1;
                break;
            case 4:
                if (oldMapNum != 0) version = 1;
                break;
            case 5:
                break;
            default:
                break;
        }
        return mapSpawns[mapNum - 1][version];
    }

    void unloadMap() {
        free(mapCollisionData);
    }

    Texture2D* getMapImage() {
        return &(mapTextures[mapNum - 1]);
    }

    int getNewMap(Vector2 position) {
        switch (mapNum) {
            case 1:
                if (position.x < 128) return 2;
                else return 5;
            case 2:
                if (position.y < 128) return 3;
                else return 1;
            case 3:
                if (position.y < 640 * 3) return 4;
                else return 2;
            case 4:
                return 3;
            case 5:
                return 1;
            default:
                return 1;
        }
    }

    void switchMap(int map, std::vector<EnemyInfo>* enemyInfo) {
        std::cout << "unloading old map data" << std::endl;
        unloadMap();
        std::cout << "loading new map data" << std::endl;
        initMap(map, enemyInfo);
    }

    void teardown() {
        for (int i = 0; i < 4; i++) {
            UnloadTexture(mapTextures[i]);
        }
    }
};