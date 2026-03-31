#ifndef NODE_H
#define NODE_H

#include <glm/glm.hpp>
#include <vector>

enum class NodeType {
    Hook ,
    Mass
} ;

struct Node {
    int id ;
    NodeType type ;

    glm::vec2 pos ;
    glm::vec2 vel ;
    glm::vec2 force ;

    float mass ;
    float radius ;
    bool isFixed ;

    std::vector<int> connectedSprings ;

    Node(int id , NodeType type , glm::vec2& pos , glm::vec2& vel , float mass , float radius) ;

    bool isHook() const ;
    bool isMass() const ;
} ;

#endif