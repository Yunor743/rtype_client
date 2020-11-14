#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

// Transform Component
struct Dimensional {
    float x;
    float y;
};

class Transform {
public:
    Dimensional location;
    Dimensional rotation;
    Dimensional scale;
public:
    Transform();
    Transform(Dimensional, Dimensional, Dimensional);
    Transform(Transform const &);
    ~Transform();
};

#endif
