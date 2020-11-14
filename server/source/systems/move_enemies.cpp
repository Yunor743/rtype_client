#include "components/Enemy.hpp"
#include "systems/rtype_systems.h"

void move_enemies(Enemy &enemy, Velocity &velocity)
{
    if (enemy.pattern.size() == 0)
        return;
    enemy.duration_elapsed++;
    if (enemy.duration_elapsed >= enemy.currentPattern().duration) {
        enemy.duration_elapsed = 0;
        enemy.pattern_id = (enemy.pattern_id + 1) % enemy.pattern.size();
    }
    velocity = enemy.currentPattern().velocity;
}
