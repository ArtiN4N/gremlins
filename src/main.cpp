#include <../include/raylib.h>
#include <../include/defs.h>
#include <stdio.h>
    #include <cmath>

int SCREEN_W = 1600;
int SCREEN_H = 800;

enum Direction { NORTH = 0, EAST, SOUTH, WEST };

struct AttackBox {
    Vector2 offset;
    Vector2 size;
    Vector2 realSize;

    bool active;
    bool ready;

    float elapsed;
    float maxActive;
    float maxCooldown;

    void init(float width, float height, float mActive, float mCool) {
        size = {width, height};
        realSize = size;

        active = false;
        ready = true;

        elapsed = 0.f;
        maxActive = mActive;
        maxCooldown = mCool;
    }

    void update(Direction parentDir, float parentRad, float dt) {
        switch (parentDir) {
            case NORTH:
                realSize = size;
                offset = { -realSize.x / 2.f, -(realSize.y + parentRad) };
                break;
            case EAST:
                realSize = {size.y, size.x};
                offset = { parentRad, -realSize.y / 2.f };
                break;
            case SOUTH:
                realSize = size;
                offset = { -realSize.x / 2.f, parentRad };
                break;
            case WEST:
                realSize = {size.y, size.x};
                offset = { -(realSize.x + parentRad), -realSize.y / 2.f };
                break;
        }

        if (active) {
            ready = false;
            elapsed += dt;
        }
        else if (!ready) elapsed += dt;
        
        if (!active && !ready && elapsed >= maxCooldown) {
            elapsed = 0.f;
            ready = true;
        }

        if (active && elapsed >= maxActive) {
            elapsed = 0.f;
            active = false;
        }
    }

    void debugDraw(Vector2 parentPos) {
        if (!active) return;

        Vector2 drawPos = { parentPos.x + offset.x, parentPos.y + offset.y };
        DrawRectangleV(drawPos, realSize, {0, 0, 255, 120});
    }
};

struct Entity {
    Vector2 position;
    Vector2 velocity;

    float dashTrace;

    float radius;
    float speed;

    Direction dir;

    AttackBox attack;

    void init(float x, float y, float rad, float spd) {
        position = {x, y};
        velocity = { 0.f, 0.f };

        dashTrace = 0.f;

        radius = rad;

        speed = spd;

        dir = NORTH;

        attack.init(70, 50, .3f, .05f);
    }

    void update(float dt) {
        
        if (IsKeyDown(KEY_LEFT)) {
            position.x -= speed * dt;
            dir = WEST;
        }
        if (IsKeyDown(KEY_RIGHT)) {
            position.x += speed * dt;
            dir = EAST;
        }
        if (IsKeyDown(KEY_UP)) {
            position.y -= speed * dt;
            dir = NORTH;
        }
        if (IsKeyDown(KEY_DOWN)) {
            position.y += speed * dt;
            dir = SOUTH;
        }

        if (IsKeyPressed(KEY_Z) && attack.ready) attack.active = true;

        if (IsKeyPressed(KEY_X) && dashTrace == 0.f && !attack.active) {
            switch (dir) {
                case NORTH:
                    velocity.y += -3000;
                    break;
                case EAST:
                    velocity.x += 3000;
                    break;
                case SOUTH:
                    velocity.y += 3000;
                    break;
                case WEST:
                    velocity.x += -3000;
                    break;
            }

            dashTrace = 3000;
        }

        attack.update(dir, radius, dt);

        position.x += velocity.x * dt;
        position.y += velocity.y * dt;

        float f = .0005f;
        velocity.x *= pow(f, dt);
        velocity.y *= pow(f, dt);
        dashTrace *= pow(f, dt);

        if (velocity.x > 0.f && velocity.x < 50.f) velocity.x = 0.f;
        if (velocity.x < 0.f && velocity.x > -50.f) velocity.x = 0.f;

        if (velocity.y > 0.f && velocity.y < 50.f) velocity.y = 0.f;
        if (velocity.y < 0.f && velocity.y > -50.f) velocity.y = 0.f;

        if (dashTrace > 0.f && dashTrace < 50.f) dashTrace = 0.f;
        if (dashTrace < 0.f && dashTrace > -50.f) dashTrace = 0.f;
    }

    void draw() {
        DrawCircleV(position, radius, RED);
        attack.debugDraw(position);
    }
};

struct Viewport {
    Camera2D camera;
    Entity* parent;

    void init(Entity* following) {
        camera = {0};
        
        camera.offset = { SCREEN_W / 2.f, SCREEN_H / 2.f };
        camera.rotation = 0.f;
        camera.zoom = 1.f;

        parent = following;
    }

    void update() {
        camera.target = parent->position;
    }
};

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(SCREEN_W, SCREEN_H, "template");

    Entity player;
    player.init(200, 100, 25, 350);

    Viewport cam;
    cam.init(&player);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // UPDATE
        player.update(dt);
        cam.update();

        // DRAW
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(cam.camera);

        DrawCircle(10, 10, 20, BLUE);

        player.draw();

        EndMode2D();

        DrawText(TextFormat("elapsed: %.2f\n active: %d\n ready: %d\n player vel: { %.2f, %.2f }", player.attack.elapsed, player.attack.active, player.attack.ready, player.velocity.x, player.velocity.y), 10, 40, 10, WHITE);
        
        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}