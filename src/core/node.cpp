#include "core/node.h"

Node::Node(int id , NodeType type , glm::vec2& pos , glm::vec2& vel , float mass , float radius)
    : id(id) , type(type) , pos(pos) , vel(vel) , force(0.0f , 0.0f) , mass(mass) , radius(radius) , isFixed(false) {
        if(type == NodeType::Hook) {
            isFixed = true ;
            mass = 0.0f ;
        }
}

bool Node::isHook() const {
    return type == NodeType::Hook ;
}

bool Node::isMass() const {
    return type == NodeType::Mass ;
}