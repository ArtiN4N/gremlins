#pragma once

#include "raylib.h"

#include <algorithm>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>

const int screen_width = 1920;
const int screen_height = 1080;

namespace vix {

    enum policy {
        COLLIDE,
        DETECT
    };

    struct game_object {
        Rectangle bounds;
        Color color;
        unsigned int policy = policy::COLLIDE;
        std::string name = "";
    };

    bool check_collision_circle_rec_this(Vector2 center, float radius, Rectangle rect) {
        Vector2 closest_point;
        closest_point.x = std::clamp(center.x, rect.x, rect.x + rect.width);
        closest_point.y = std::clamp(center.y, rect.y, rect.y + rect.height);

        //Subtracting the two vectors
        Vector2 distance;
        distance.x = center.x - closest_point.x;
        distance.y = center.y - closest_point.y;

        //Calculating the squared distance
        float distance_squared = (distance.x * distance.x) + (distance.y * distance.y);

        return distance_squared <= (radius * radius);
    }
}