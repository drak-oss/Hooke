#ifndef COLLISION_H
#define COLLISION_H

#include "core/world.h"
#include <glm/glm.hpp>

struct BallContact {
    int nodeA , nodeB ;
    glm::vec2 normal ;
    float penetration ;
};

struct WallContact {
    int node ;
    glm::vec2 normal ;
    float penetration ;
};

class CollisionDetection {
public:
    static void findContactsBetweenBalls(World& world , std::vector<BallContact>& contacts) ;
    static void findContactsBetweenBallsAndBoundaries(World& world , std::vector<WallContact>& contacts , int screenWidth , int screenHeight) ;
};

#endif