#pragma once

#include "defs.h"
#include "raylib.h"
#include "entity.h"

struct Viewport {
    Camera2D camera;
    Entity* parent;

    void init(Entity* following) {
        camera = {0};
        
        camera.offset = { SCREEN_W / 2.f, SCREEN_H / 2.f };
        camera.rotation = 0.f;
        camera.zoom = 1.2f;

        parent = following;
    }

    void update() {
        camera.target = parent->position;
    }
};