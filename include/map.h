#pragma once

#include "raylib.h"

#include <cstdlib>

#include "FULLmap4.h"

unsigned int mapSizes[10][2] = {
    {0, 0},
    {0, 0},
    {0, 0},
    {64, 43},
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

    bool* mapCollisionData;

    void initMap(int map) {
        width = mapSizes[map - 1][0];
        height = mapSizes[map - 1][1];

        std::cout << "alloc'ing map" << std::endl;
        mapCollisionData = (bool*) malloc(sizeof(bool) * mapSizes[map - 1][0] * mapSizes[map - 1][1]);
        std::cout << "alloc'ed map" << std::endl;

        std::cout << "loading image data" << std::endl;
        unsigned int* image_data;
        switch (map) {
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
                mapCollisionData[y * width + x] = (pixel != 0x00000000);
            }
        }
    }

    void unloadMap() {
        free(mapCollisionData);
    }

    void switchMap(int map) {
        unloadMap();
        initMap(map);
    }
};