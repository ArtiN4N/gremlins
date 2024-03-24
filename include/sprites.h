#pragma once

#include "defs.h"
#include "raylib.h"
#include "entity.h"

#include <vector>

struct PlayerSprites {
    Texture2D idle[4];

    Texture2D walk[4];

    void init() {
        for (int i = 0; i < 4; i++) {
            Image img = LoadImage(TextFormat("assets/gramps/idle%d.png", i + 1));
            idle[i] = LoadTextureFromImage(img);
            UnloadImage(img);
        }

        for (int i = 0; i < 4; i++) {
            Image img = LoadImage(TextFormat("assets/gramps/walk%d.png", i + 1));
            walk[i] = LoadTextureFromImage(img);
            UnloadImage(img);
        }
    }

    void unload() {
        for (int i = 0; i < 4; i++) {
            UnloadTexture(idle[i]);
        }
        for (int i = 0; i < 4; i++) {
            UnloadTexture(walk[i]);
        }
    }

    void initEntity(Entity* en) {
        en->tex = &(idle[1]);
    }

    void draw(Entity en) {
        Texture2D drawing = *(en.tex);
        Rectangle sourceRec = { 0.0f, 0.0f, (float) drawing.width, (float) drawing.height };

        Rectangle destRec = { en.position.x, en.position.y - 10, en.radius * 3, en.radius * 3 };

        DrawTexturePro(drawing, sourceRec, destRec, { en.radius * 3/2, en.radius * 3/2 }, 0.f, WHITE);
        en.attack.debugDraw(en.position);
    }
};

struct HumanSprites {
    Texture2D idle;

    Texture2D walk[2];

    void init() {
        Image img = LoadImage(TextFormat("assets/humans/idle.png"));
        idle = LoadTextureFromImage(img);
        UnloadImage(img);

        for (int i = 0; i < 2; i++) {
            Image img = LoadImage(TextFormat("assets/humans/walk%d.png", i + 1));
            walk[i] = LoadTextureFromImage(img);
            UnloadImage(img);
        }
    }

    void unload() {
        UnloadTexture(idle);

        for (int i = 0; i < 2; i++) {
            UnloadTexture(walk[i]);
        }
    }

    void initEntity(Entity* en) {
        en->tex = &(idle);
    }

    void draw(Entity en) {
        Texture2D drawing = *(en.tex);
        Rectangle sourceRec = { 0.0f, 0.0f, (float) drawing.width, (float) drawing.height };

        Rectangle destRec = { en.position.x, en.position.y - 10, en.radius * 3, en.radius * 3 };

        DrawTexturePro(drawing, sourceRec, destRec, { en.radius * 3/2, en.radius * 3/2 }, 0.f, WHITE);
        en.attack.debugDraw(en.position);
    }
};

struct GhostSprites {
    Texture2D idle;

    Texture2D walk[2];

    void init() {
        Image img = LoadImage(TextFormat("assets/ghosts/idle.png"));
        idle = LoadTextureFromImage(img);
        UnloadImage(img);

        for (int i = 0; i < 2; i++) {
            Image img = LoadImage(TextFormat("assets/ghosts/walk%d.png", i + 1));
            walk[i] = LoadTextureFromImage(img);
            UnloadImage(img);
        }
    }

    void unload() {
        UnloadTexture(idle);

        for (int i = 0; i < 2; i++) {
            UnloadTexture(walk[i]);
        }
    }

    void initEntity(Entity* en) {
        en->tex = &(idle);
    }

    void draw(Entity en) {
        Texture2D drawing = *(en.tex);
        Rectangle sourceRec = { 0.0f, 0.0f, (float) drawing.width, (float) drawing.height };

        Rectangle destRec = { en.position.x, en.position.y - 10, en.radius * 3, en.radius * 3 };

        DrawTexturePro(drawing, sourceRec, destRec, { en.radius * 3/2, en.radius * 3/2 }, 0.f, WHITE);
        en.attack.debugDraw(en.position);
    }
};

struct WizardSprites {
    Texture2D idle;

    Texture2D walk;

    Texture2D attack[2];

    void init() {
        Image img = LoadImage(TextFormat("assets/wizards/idle.png"));
        idle = LoadTextureFromImage(img);
        UnloadImage(img);

        Image img2 = LoadImage(TextFormat("assets/wizards/walk.png"));
        walk = LoadTextureFromImage(img2);
        UnloadImage(img2);

        for (int i = 0; i < 2; i++) {
            Image img = LoadImage(TextFormat("assets/wizards/attack%d.png", i + 1));
            attack[i] = LoadTextureFromImage(img);
            UnloadImage(img);
        }
    }

    void unload() {
        UnloadTexture(idle);
        UnloadTexture(walk);

        for (int i = 0; i < 2; i++) {
            UnloadTexture(attack[i]);
        }
    }

    void initEntity(Entity* en) {
        en->tex = &(idle);
    }

    void draw(Entity en) {
        Texture2D drawing = *(en.tex);
        Rectangle sourceRec = { 0.0f, 0.0f, (float) drawing.width, (float) drawing.height };

        Rectangle destRec = { en.position.x, en.position.y - 10, en.radius * 3, en.radius * 3 };

        DrawTexturePro(drawing, sourceRec, destRec, { en.radius * 3/2, en.radius * 3/2 }, 0.f, WHITE);
        en.attack.debugDraw(en.position);
    }
};

struct GwizardSprites {
    Texture2D idle;

    Texture2D walk;

    Texture2D attack[2];

    void init() {
        Image img = LoadImage(TextFormat("assets/wizards/idle.png"));
        idle = LoadTextureFromImage(img);
        UnloadImage(img);

        Image img2 = LoadImage(TextFormat("assets/wizards/walk.png"));
        walk = LoadTextureFromImage(img2);
        UnloadImage(img2);

        for (int i = 0; i < 2; i++) {
            Image img = LoadImage(TextFormat("assets/wizards/attack%d.png", i + 1));
            attack[i] = LoadTextureFromImage(img);
            UnloadImage(img);
        }
    }

    void unload() {
        UnloadTexture(idle);
        UnloadTexture(walk);

        for (int i = 0; i < 2; i++) {
            UnloadTexture(attack[i]);
        }
    }

    void initEntity(Entity* en) {
        en->tex = &(idle);
    }

    void draw(Entity en) {
        Texture2D drawing = *(en.tex);
        Rectangle sourceRec = { 0.0f, 0.0f, (float) drawing.width, (float) drawing.height };

        Rectangle destRec = { en.position.x, en.position.y - 10, en.radius * 3, en.radius * 3 };

        DrawTexturePro(drawing, sourceRec, destRec, { en.radius * 3/2, en.radius * 3/2 }, 0.f, WHITE);
        en.attack.debugDraw(en.position);
    }
};