#ifndef COLLISION_BOX_HPP
#define COLLISION_BOX_HPP

#include "GameObject.hpp"
#include <functional>
#include <optional>

struct CollisionBox {
    float width;
    float height;
    float offset_x = 0;
    float offset_y = 0;
    unsigned roughness = 1;
    std::optional<GameObject> collidingWith = {};
    float colliderRoughness = 0;
};

#endif
