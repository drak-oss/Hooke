#include "physics/physics.h"

void Physics::simulate(World& world , float dt , glm::vec2& gravity) {
    for(auto& node : world.nodes) {
        node.force = {0.0f , 0.0f} ;
    }

    for(auto& spring : world.springs) {
        Node& a = world.nodes[spring.NodeA] ;
        Node& b = world.nodes[spring.NodeB] ;

        glm::vec2 delta = b.pos - a.pos ;
        float dist = std::sqrt(delta.x * delta.x + delta.y * delta.y) ;

        if(dist == 0.0f) continue ;
        float springDelta = dist - spring.restLength ;

        glm::vec2 force = glm::normalize(delta) ;
        force *= spring.stifness * springDelta ;

        if(!a.isFixed) a.force += force ;
        if(!b.isFixed) b.force += force * (-1.0f) ;
    }

    for(auto& node : world.nodes) {
        if(node.isFixed) continue ;

        glm::vec2 acc = node.force / node.mass + gravity ;
        node.vel += acc * dt ;
        node.pos += node.vel * dt ;
    }
}

