#pragma once

#include "raylib.h"

#include <cstdlib>

#include "FULLmap1.h"
#include "FULLmap2.h"
#include "FULLmap3.h"
#include "FULLmap4.h"

enum CollisionType { WALL = 0, DOOR, NONE };

unsigned int mapSizes[10][2] = {
    {128, 1216},
    {64, 64},
    {48, 64},
    {64, 43},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0}
};

Vector2 mapSpawns[10] = {
    {128, 1920},
    {1920, 128},
    {600, 600},
    {300, 300},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0}
};

struct Map {
    int width;
    int height;

    int tileSize;

    int mapNum = 1;

    CollisionType* mapCollisionData;

    Texture2D mapTextures[4];
    Texture2D* currentMapTex;

    void setup() {
        Image map1Data = LoadImage("assets/maps/FULLmap1.png");
        Texture2D map1Image = LoadTextureFromImage(map1Data);
        UnloadImage(map1Data);

        Image map2Data = LoadImage("assets/maps/FULLmap2.png");
        Texture2D map2Image = LoadTextureFromImage(map2Data);
        UnloadImage(map2Data);

        Image map3Data = LoadImage("assets/maps/FULLmap3.png");
        Texture2D map3Image = LoadTextureFromImage(map3Data);
        UnloadImage(map3Data);

        Image map4Data = LoadImage("assets/maps/FULLmap4.png");
        Texture2D map4Image = LoadTextureFromImage(map4Data);
        UnloadImage(map4Data);

        
        mapTextures[0] = map1Image;
        mapTextures[1] = map2Image;
        mapTextures[2] = map3Image;
        mapTextures[3] = map4Image;
        
        currentMapTex = NULL;
    }   

    void initMap(int map) {
        mapNum = map;


        currentMapTex = &(mapTextures[mapNum - 1]);


        width = mapSizes[map - 1][0];
        height = mapSizes[map - 1][1];

        mapCollisionData = (CollisionType*) malloc(sizeof(CollisionType) * mapSizes[map - 1][0] * mapSizes[map - 1][1]);

        unsigned int* image_data;
        switch (map) {
            case 1:
                image_data = fullmap1_data;
                tileSize = 64;
                break;
            case 2:
                image_data = fullmap2_data;
                tileSize = 64;
                break;
            case 3:
                image_data = fullmap3_data;
                tileSize = 64;
                break;
            case 4:
                image_data = fullmap4_data;
                tileSize = 64;
                break;
            default:
                image_data = fullmap4_data;
                tileSize = 64;
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
    }

    float getMapZoom() {
        switch (mapNum) {
            case 2:
                return .5f;
            default:
                return 1.f;
        }
    }

    Vector2 getSpawnPos() {
        return mapSpawns[mapNum - 1];
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
            default:
                return 1;
        }
    }

    void switchMap(int map) {
        unloadMap();
        initMap(map);
    }

    void teardown() {
        for (int i = 0; i < 4; i++) {
            UnloadTexture(mapTextures[i]);
        }
    }
};