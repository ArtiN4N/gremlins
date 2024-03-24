#pragma once

#include "defs.h"
#include "raylib.h"
#include "entity.h"

#include <vector>

struct PlayerSprites {
    Texture2D idle[4];

    Texture2D walk[4];

    Texture2D attack[4];

    float fps;
    float elapsed;
    int frame;
    int maxFrame;

    void init() {
        fps = .6f;
        elapsed = 0.f;
        frame = 0;
        maxFrame = 1;

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

        for (int i = 0; i < 4; i++) {
            Image img = LoadImage(TextFormat("assets/gramps/attack%d.png", i + 1));
            attack[i] = LoadTextureFromImage(img);
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

    void update(Entity* en, float dt) {
        maxFrame = 1;
        switch (en->dir) {
            case NORTH:
                en->tex = &(idle[1]);
                break;
            case SOUTH:
                en->tex = &(idle[0]);
                break;
            case WEST:
                en->tex = &(idle[3]);
                break;
            case EAST:
                en->tex = &(idle[2]);
                break;
        }
        if (en->moveVelocity.x != 0.f || en->moveVelocity.y != 0.f) {
            maxFrame = 6;
            switch (en->dir) {
                case NORTH:
                    en->tex = &(walk[1]);
                    break;
                case SOUTH:
                    en->tex = &(walk[0]);
                    break;
                case WEST:
                    en->tex = &(walk[3]);
                    break;
                case EAST:
                    en->tex = &(walk[2]);
                    break;
            }
        }
        if (en->attack.active) {
            maxFrame = 7;
            switch (en->dir) {
                case NORTH:
                    en->tex = &(attack[1]);
                    break;
                case SOUTH:
                    en->tex = &(attack[0]);
                    break;
                case WEST:
                    en->tex = &(attack[3]);
                    break;
                case EAST:
                    en->tex = &(attack[2]);
                    break;
            }
        }

        elapsed += dt * .5f;
        if (elapsed > fps) frame++;
        if (frame > maxFrame - 1) frame = 0;
        
    }

    void draw(Entity en) {
        Texture2D drawing = *(en.tex);
        Rectangle sourceRec = { (float) frame * ((float) drawing.width / (float) maxFrame), 0.0f, (float) drawing.width / (float) maxFrame, (float) drawing.height };

        Rectangle destRec = { en.position.x, en.position.y, en.radius * 5, en.radius * 5 };

        DrawCircleV(en.position, en.radius, RED);

        DrawTexturePro(drawing, sourceRec, destRec, { en.radius * 5/2, en.radius * 5/2 }, 0.f, WHITE);
        en.attack.debugDraw(en.position);
    }
};

struct HumanSprites {
    Texture2D idle;

    Texture2D walk[2];

    void init() {
        Image img = LoadImage(TextFormat("assets/human/human.png"));
        idle = LoadTextureFromImage(img);
        UnloadImage(img);

        for (int i = 0; i < 2; i++) {
            Image img = LoadImage(TextFormat("assets/human/run%d.png", i + 1));
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

    void update(Entity* en, float dt) {
        en->maxFrame = 1;
        en->tex = &(idle);

        if (en->moveVelocity.x != 0.f || en->moveVelocity.y != 0.f) {
            
            if (en->moveVelocity.x > 0.f) {
                en->tex = walk;
            }else {
                en->tex = walk + 1;
            }
            en->maxFrame = 6;
        }

        en->elapsed += dt * .5f;
        if (en->elapsed > en->fps) en->frame++;
        if (en->frame > en->maxFrame - 1) en->frame = 0;
        
    }

    void draw(Entity en) {
        Texture2D drawing = *(en.tex);

        Rectangle sourceRec = { (float) en.frame * ((float) drawing.width / (float) en.maxFrame), 0.0f, (float) drawing.width / (float) en.maxFrame, (float) drawing.height };

        Rectangle destRec = { en.position.x, en.position.y, en.radius * 5, en.radius * 5 };

        DrawCircleV(en.position, en.radius, RED);
        

        DrawTexturePro(drawing, sourceRec, destRec, { en.radius * 5/2, en.radius * 5/2 }, 0.f, WHITE);
    }
};

struct GhostSprites {
    Texture2D idle;

    Texture2D walk[2];

    void init() {
        Image img = LoadImage(TextFormat("assets/ghost/idle.png"));
        idle = LoadTextureFromImage(img);
        UnloadImage(img);

        for (int i = 0; i < 2; i++) {
            Image img = LoadImage(TextFormat("assets/ghost/walk%d.png", i + 1));
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

        DrawCircleV(en.position, en.radius, BLUE);

        DrawTexturePro(drawing, sourceRec, destRec, { en.radius * 3/2, en.radius * 3/2 }, 0.f, WHITE);
        en.attack.debugDraw(en.position);
    }
};

struct WizardSprites {
    Texture2D idle;

    Texture2D walk;

    Texture2D attack;

    void init() {
        Image img = LoadImage(TextFormat("assets/wizard/idle.png"));
        idle = LoadTextureFromImage(img);
        UnloadImage(img);

        Image img2 = LoadImage(TextFormat("assets/wizard/walk.png"));
        walk = LoadTextureFromImage(img2);
        UnloadImage(img2);

        Image img3 = LoadImage(TextFormat("assets/wizard/attack.png"));
        walk = LoadTextureFromImage(img3);
        UnloadImage(img3);
    }

    void unload() {
        UnloadTexture(idle);
        UnloadTexture(walk);
        UnloadTexture(attack);
    }

    void initEntity(Entity* en) {
        en->tex = &(idle);
    }

    void draw(Entity en) {
        Texture2D drawing = *(en.tex);
        Rectangle sourceRec = { 0.0f, 0.0f, (float) drawing.width, (float) drawing.height };

        Rectangle destRec = { en.position.x, en.position.y - 10, en.radius * 3, en.radius * 3 };

        DrawCircleV(en.position, en.radius, BLUE);

        DrawTexturePro(drawing, sourceRec, destRec, { en.radius * 3/2, en.radius * 3/2 }, 0.f, WHITE);
        en.attack.debugDraw(en.position);
    }
};

struct GwizardSprites {
    Texture2D idle;

    Texture2D walk;

    Texture2D attack;

    void init() {
        Image img = LoadImage(TextFormat("assets/wizard/idle.png"));
        idle = LoadTextureFromImage(img);
        UnloadImage(img);

        Image img2 = LoadImage(TextFormat("assets/wizard/walk.png"));
        walk = LoadTextureFromImage(img2);
        UnloadImage(img2);

        Image img3 = LoadImage(TextFormat("assets/wizard/attack.png"));
        walk = LoadTextureFromImage(img3);
        UnloadImage(img3);
    }

    void unload() {
        UnloadTexture(idle);
        UnloadTexture(walk);
        UnloadTexture(attack);
    }

    void initEntity(Entity* en) {
        en->tex = &(idle);
    }

    void draw(Entity en) {
        Texture2D drawing = *(en.tex);
        Rectangle sourceRec = { 0.0f, 0.0f, (float) drawing.width, (float) drawing.height };

        DrawCircleV(en.position, en.radius, BLUE);

        Rectangle destRec = { en.position.x, en.position.y - 10, en.radius * 3, en.radius * 3 };

        DrawTexturePro(drawing, sourceRec, destRec, { en.radius * 3/2, en.radius * 3/2 }, 0.f, WHITE);
        en.attack.debugDraw(en.position);
    }
};

struct ProjectileSprites {
    Texture2D idle;

    void init() {
        Image img = LoadImage(TextFormat("assets/arrow/idle.png"));
        idle = LoadTextureFromImage(img);
        UnloadImage(img);
    }

    void unload() {
        UnloadTexture(idle);
    }

    void initEntity(Entity* en) {
        en->tex = &(idle);
    }

    void draw(Entity en) {
        Rectangle sourceRec = { 0.0f, 0.0f, (float) idle.width, (float) idle.height };
        Rectangle destRec = { en.position.x, en.position.y - 10, en.radius * 10, en.radius * 10 };

        DrawTexturePro(idle, sourceRec, destRec, { en.radius * 3/2, en.radius * 3/2 }, 0.f, WHITE);
        en.attack.debugDraw(en.position);
    }
};