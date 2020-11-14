#include "components/AnimationLoop.hpp"

const Sprite &AnimationLoop::getCurrentFrame() const
{
    return this->frames[this->current_frame];
}
