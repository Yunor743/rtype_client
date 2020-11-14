#include "components/AnimationLoop.hpp"
#include "systems/rtype_systems.h"

void run_animation_loops(AnimationLoop &loop, Sprite &sprite)
{
    if (loop.frames.size() == 0)
        return;
    loop.duration_elapsed++;
    if (loop.duration_elapsed >= loop.delay) {
        loop.duration_elapsed = 0;
        loop.current_frame = (loop.current_frame + 1) % loop.frames.size();
    }
    sprite = loop.getCurrentFrame();
}
