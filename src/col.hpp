#include <algorithm>

const int screenWidth = 800;
const int screenHeight = 450;

struct GameObject {
    Rectangle bounds;
    Color color;
};

bool CheckCollisionCircleRecThis(Vector2 center, float radius, Rectangle rect) {
    Vector2 closestPoint;
    closestPoint.x = std::clamp(center.x, rect.x, rect.x + rect.width);
    closestPoint.y = std::clamp(center.y, rect.y, rect.y + rect.height);

    //Subtracting the two vectors
    Vector2 distance;
    distance.x = center.x - closestPoint.x;
    distance.y = center.y - closestPoint.y;

    //Calculating the squared distance
    float distanceSquared = (distance.x * distance.x) + (distance.y * distance.y);

    return distanceSquared <= (radius * radius);
}

void main_2() {
    //Initialization
    InitWindow(screenWidth, screenHeight, "Top Down Collision System");

    //Player setup
    Vector2 previousPlayerPosition = { screenWidth / 2, screenHeight / 2 };
    Vector2 playerPosition = { screenWidth / 2, screenHeight / 2 };
    float playerRadius = 20.0f;
    Color playerColor = BLUE;

    //Bounding box objects setup
    std::vector<GameObject> objects;
    GameObject obj1 = { { 200, 200, 100, 100 }, RED };
    GameObject obj2 = { { 400, 300, 150, 50 }, GREEN };
    GameObject obj3 = { { 100, 300, 400, 50 }, BLUE };
    objects.push_back(obj1);
    objects.push_back(obj2);
    objects.push_back(obj3);

    SetTargetFPS(60); //Set the framerate

    //Main game loop
    while (!WindowShouldClose()) {
        //Update

        previousPlayerPosition = playerPosition;

        //Player movement
        if (IsKeyDown(KEY_RIGHT)) playerPosition.x += 5.0f;
        else if (IsKeyDown(KEY_LEFT)) playerPosition.x -= 5.0f;
        if (IsKeyDown(KEY_DOWN)) playerPosition.y += 5.0f;
        else if (IsKeyDown(KEY_UP)) playerPosition.y -= 5.0f;

        //Collision detection
        for (const auto& obj : objects) {
            if (CheckCollisionCircleRecThis(playerPosition, playerRadius, obj.bounds)) {
                //Collision detected! Handle it here
                playerColor = obj.color; //Change player color on collision
                playerPosition = previousPlayerPosition;
            }
        }

        //Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        //Draw bounding box objects
        for (const auto& obj : objects) {
            DrawRectangleRec(obj.bounds, obj.color);
        }

        //Draw player
        DrawCircleV(playerPosition, playerRadius, playerColor);

        EndDrawing();
    }

    //Close window and OpenGL context
    CloseWindow();
    return;
}
