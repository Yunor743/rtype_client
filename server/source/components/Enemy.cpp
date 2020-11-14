#include "components/Enemy.hpp"

const Pattern &Enemy::currentPattern()
{
    return this->pattern.at(this->pattern_id);
}
