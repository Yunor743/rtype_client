#include "components/Transform.hpp"
#include "components/Velocity.hpp"
#include "components/Trajectory.hpp"

void velocity_applicator(Transform &transform, const Velocity &velocity)
{
        transform.location.x += velocity.x;
        transform.location.y += velocity.y;
}

void trajectory_applicator(Transform &transform, const Trajectory &trajectory)
{
    trajectory.update(transform);
}
