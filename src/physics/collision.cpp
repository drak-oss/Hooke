#include "physics/collision.h"

void CollisionDetection::findContactsBetweenBalls(World& world , std::vector<BallContact>& contacts) {
    for(int i = 0 ; i < world.nodes.size() ; i++) {
        for(int j = i + 1 ; j < world.nodes.size() ; j++) {
            float delta = glm::distance(world.nodes[j].pos , world.nodes[i].pos) ;
            float totRadius = world.nodes[i].radius + world.nodes[j].radius ;
            if(totRadius - delta >= 0.0f) {
                BallContact contact ;
                contact.nodeA = i , contact.nodeB = j ;
                contact.normal = glm::normalize(world.nodes[j].pos - world.nodes[i].pos) ;
                contact.penetration = totRadius - delta ;
                contacts.push_back(contact) ; 
            }
        }
    }
}

void CollisionDetection::findContactsBetweenBallsAndBoundaries(World& world , std::vector<WallContact>& contacts , int screenWidth , int screenHeight) {
    for(int i = 0 ; i < world.nodes.size() ; i++) {
        if(world.nodes[i].pos.x < world.nodes[i].radius) {
            WallContact contact ;
            contact.normal = {1.0f , 0.0f} ;
            contact.penetration = world.nodes[i].radius - world.nodes[i].pos.x  ;
            contact.node = i ;
            contacts.push_back(contact) ;
        }
        if(world.nodes[i].pos.y < world.nodes[i].radius) {
            WallContact contact ;
            contact.normal = {0.0f , 1.0f} ;
            contact.penetration = world.nodes[i].radius - world.nodes[i].pos.y ;
            contact.node = i ;
            contacts.push_back(contact) ;
        }
        if(world.nodes[i].pos.y > screenHeight - world.nodes[i].radius) {
            WallContact contact ;
            contact.normal = {0.0f , -1.0f} ;
            contact.penetration = world.nodes[i].pos.y - (screenHeight - world.nodes[i].radius) ;
            contact.node = i ;
            contacts.push_back(contact) ;
        }
        if(world.nodes[i].pos.x > screenWidth - world.nodes[i].radius) {
            WallContact contact ;
            contact.normal = {-1.0f , 0.0f} ;
            contact.penetration = world.nodes[i].pos.x - (screenWidth - world.nodes[i].radius) ;
            contact.node = i ;
            contacts.push_back(contact) ;
        }
    }
}

