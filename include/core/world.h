#ifndef WORLD_H
#define WORLD_H

#include "core/node.h"
#include "core/spring.h"
#include <vector>

struct World {
    std::vector<Node> nodes ;
    std::vector<Spring> springs ;

    int addHook(glm::vec2& pos , float radius) ;
    int addMass(glm::vec2& pos , glm::vec2& vel , float mass , float radius) ;
    int addSpring(int nodeA , int nodeB , float restLength , float stiffness , float damping) ;
    void initWorld() ;
};

#endif