#ifndef RTYPE_ANIMATIONLOOP_H_
#define RTYPE_ANIMATIONLOOP_H_

#include <vector>
#include <string>

#include "components/Sprite.hpp"

struct AnimationLoop {
    std::vector<Sprite> frames;
    unsigned delay;
    unsigned current_frame = 0;
    unsigned duration_elapsed = 0;

    const Sprite &getCurrentFrame() const;
};

#endif // RTYPE_ANIMATIONLOOP_H_
