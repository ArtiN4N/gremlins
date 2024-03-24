
    class item_driver {
    public:
        Vector2 position;
        float radius;

        item_driver(Vector2 pos, float r) : position(pos), radius(r) {}

        void draw() {
            DrawCircleV(position, radius, VIOLET);
            DrawLine(position.x - radius, position.y - radius, position.x + radius, position.y + radius, VIOLET);
            DrawLine(position.x - radius, position.y + radius, position.x + radius, position.y - radius, VIOLET);
        }

        bool check_collision(Vector2 player_pos, float player_radius) {
            float dx = position.x - player_pos.x;
            float dy = position.y - player_pos.y;
            float distance = sqrt(dx * dx + dy * dy);
        return (distance <= (radius + player_radius));
    }
    };

    std::vector<item_driver> items_list;