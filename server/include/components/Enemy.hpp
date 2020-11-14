#ifndef RTYPE_ENEMY_H_
#define RTYPE_ENEMY_H_

#include "components/Velocity.hpp"
#include <vector>

struct Pattern {
    Velocity velocity;
    unsigned duration;
};

struct Enemy {
    std::vector<Pattern> pattern;
    unsigned health;
    unsigned pattern_id = 0;
    unsigned duration_elapsed = 0;

    const Pattern &currentPattern();
};

#endif // RTYPE_ENEMY_H_
