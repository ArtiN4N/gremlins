#pragma once

#include "raylib.h"

#include <cstdlib>

#include "FULLmap2.h"
#include "FULLmap4.h"

enum CollisionType { WALL = 0, DOOR, NONE };

unsigned int mapSizes[10][2] = {
    {0, 0},
    {64, 64},
    {0, 0},
    {64, 43},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0}
};

Vector2 mapSpawns[10] = {
    {0, 0},
    {1920, 128},
    {0, 0},
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

    void initMap(int map) {
        mapNum = map;

        width = mapSizes[map - 1][0];
        height = mapSizes[map - 1][1];

        std::cout << "alloc'ing map" << std::endl;
        mapCollisionData = (CollisionType*) malloc(sizeof(CollisionType) * mapSizes[map - 1][0] * mapSizes[map - 1][1]);
        std::cout << "alloc'ed map" << std::endl;

        std::cout << "loading image data" << std::endl;
        unsigned int* image_data;
        switch (map) {
            case 2:
                image_data = fullmap2_data;
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
        std::cout << "got image data" << std::endl;

        for (unsigned int y = 0; y < mapSizes[map - 1][1]; y++) {
            for (unsigned int x = 0; x < mapSizes[map - 1][0]; x++) {
                std::cout << "writing collision at x = " << x << " and y = " << y << " res = " << y * width + x << " cuz width = " << width << std::endl;
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

    int getNewMap(Vector2 position) {
        switch (mapNum) {
            case 2:
                if (position.y < 128) return 3;
                else return 1;
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
};