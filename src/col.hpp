#include <algorithm>
#include <cstdlib>
#include <string>
#include <cstring>

const int screen_width = 800;
const int screen_height = 450;

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

void main_2() {
    //Initialization
    InitWindow(screen_width, screen_height, "Top Down Collision System");

    //Player setup
    Vector2 previous_player_position = { screen_width / 2, screen_height / 2 };
    Vector2 player_position = { screen_width / 2, screen_height / 2 };
    float player_radius = 20.0;
    Color player_color = BLUE;

    //Bounding box objects setup
    std::vector<vix::game_object> objects;
    vix::game_object obj1 = { { 200, 200, 100, 100 }, RED, vix::policy::COLLIDE, "red_box_name" };
    vix::game_object obj2 = { { 400, 300, 150, 50 }, GREEN, vix::policy::COLLIDE, "green_box_name"};
    vix::game_object obj3 = { { 100, 300, 400, 50 }, BLUE, vix::policy::DETECT, "blue_box_name"};
    objects.push_back(obj1);
    objects.push_back(obj2);
    objects.push_back(obj3);

    SetTargetFPS(60); //Set the framerate

    //Main game loop
    while (!WindowShouldClose()) {
        //Update

        previous_player_position = player_position;

        //Player movement
        if (IsKeyDown(KEY_RIGHT)) player_position.x += 5.0;
        else if (IsKeyDown(KEY_LEFT)) player_position.x -= 5.0;
        if (IsKeyDown(KEY_DOWN)) player_position.y += 5.0;
        else if (IsKeyDown(KEY_UP)) player_position.y -= 5.0;

        //Collision detection
        size_t length = objects.size();
        for (size_t i = 0; i < length; i++) {
            if (vix::check_collision_circle_rec_this(player_position, player_radius, objects[i].bounds)) {
                //Collision detected! Handle it here
                player_color = objects[i].color; //Change player color on collision
                if(objects[i].policy==vix::policy::COLLIDE)player_position = previous_player_position;
            }
        }

        //Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        //Draw bounding box objects
        for (size_t i = 0; i < length; i++) {
            DrawRectangleRec(objects[i].bounds, objects[i].color);
        }

        //Draw player
        DrawCircleV(player_position, player_radius, player_color);

        EndDrawing();
    }

    //Close window and OpenGL context
    CloseWindow();
    return;
}
