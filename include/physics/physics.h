#ifndef PHYSICS_H
#define PHYSICS_H

#include "core/world.h"

class Physics {
public:
    void simulate(World& world , float dt , glm::vec2& gravity) ;
};

#endif