#include <cstdlib>
#include <cmath>
namespace vix {

    enum item_type {
        NONE,
        BOOTS,
        HEALTH,
        COIN,
        RELIC,
        STAFF,
        GEM
    };

    class item_driver {
    public:
        Vector2 position;
        float radius;
        uint32_t item_type;

        item_driver(Vector2 pos, float r, uint32_t i_type) : position(pos), radius(r), item_type(i_type) {}

        void draw() {
            DrawCircleV(position, radius, VIOLET);
        }

        uint32_t check_collision(Vector2 player_pos, float player_radius) {
            float dx = position.x - player_pos.x;
            float dy = position.y - player_pos.y;
            float distance = sqrt(dx * dx + dy * dy);
            if (!(distance <= (radius + player_radius))) return 0;
        return item_type;
    }

    };



    std::vector<item_driver> items_list;
}