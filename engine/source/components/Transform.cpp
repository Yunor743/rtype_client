#include "components/Transform.hpp"

Transform::Transform()
{}

Transform::Transform(Dimensional l, Dimensional r, Dimensional s)
: location(l), rotation(r), scale(s)
{}

Transform::Transform(Transform const &other)
: location(other.location), rotation(other.rotation), scale(other.scale)
{}

Transform::~Transform()
{}
