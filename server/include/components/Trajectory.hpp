#ifndef TRAJECTORY_HPP
#define TRAJECTORY_HPP

#include "components/Transform.hpp"
#include <functional>

struct Trajectory {
    std::function<void(Transform &)> update;
};

#endif
