#ifndef SOLVER_H
#define SOLVER_H

#include "core/world.h"
#include "physics/collision.h"

class Solver {
public:
    static void resolveContacts(World& world , std::vector<BallContact>& contacts) ;
    static void resolveBoundaryContacts(World& world , std::vector<WallContact>& contacts) ;
    static void addSpringDamping(World& world) ;
};

#endif