#ifndef RTYPE_SPRITE_COMPONENT_H
#define RTYPE_SPRITE_COMPONENT_H

#include "Modules.hpp"
#include <string>

struct Sprite {
    std::string name;
    unsigned tile_id;
    bool hidden = false;
};

#endif // RTYPE_SPRITE_COMPONENT_H
