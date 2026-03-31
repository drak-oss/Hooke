#include "physics/solver.h"
#include <iostream>

void Solver::resolveContacts(World& world , std::vector<BallContact>& contacts) {
    for(int i = 0 ; i < contacts.size() ; i++) {
        if(world.nodes[contacts[i].nodeA].isHook() && world.nodes[contacts[i].nodeB].isHook()) {
            std::cout << "Two Hooks Cannot Overlap Each Other !" << std::endl ;
        }
        else if(world.nodes[contacts[i].nodeA].isHook() && world.nodes[contacts[i].nodeB].isMass()) {
            glm::vec2 normal = contacts[i].normal ;
            glm::vec2 tangent = {-contacts[i].normal.y , contacts[i].normal.x} ;

            glm::vec2 posNormalComp = glm::dot(normal , world.nodes[contacts[i].nodeB].pos) * normal ;
            glm::vec2 posTangentComp = glm::dot(tangent , world.nodes[contacts[i].nodeB].pos) * tangent ;
            posNormalComp = posNormalComp - contacts[i].penetration - 0.5f ;
            world.nodes[contacts[i].nodeB].pos = posNormalComp + posTangentComp ;

            glm::vec2 velNormalComp = glm::dot(normal , world.nodes[contacts[i].nodeB].vel) * normal ;
            glm::vec2 velTangentComp = glm::dot(tangent , world.nodes[contacts[i].nodeB].vel) * tangent ;

            velNormalComp = -velNormalComp ;
            world.nodes[contacts[i].nodeB].vel = velNormalComp + velTangentComp ;
        }
        else if(world.nodes[contacts[i].nodeA].isMass() && world.nodes[contacts[i].nodeB].isHook()) {
            glm::vec2 normal = contacts[i].normal ;
            glm::vec2 tangent = {-contacts[i].normal.y , contacts[i].normal.x} ;

            glm::vec2 posNormalComp = glm::dot(normal , world.nodes[contacts[i].nodeA].pos) * normal ;
            glm::vec2 posTangentComp = glm::dot(tangent , world.nodes[contacts[i].nodeA].pos) * tangent ;
            posNormalComp = posNormalComp + contacts[i].penetration + 0.5f ;
            world.nodes[contacts[i].nodeA].pos = posNormalComp + posTangentComp ;

            glm::vec2 velNormalComp = glm::dot(normal , world.nodes[contacts[i].nodeA].vel) * normal ;
            glm::vec2 velTangentComp = glm::dot(tangent , world.nodes[contacts[i].nodeA].vel) * tangent ;

            world.nodes[contacts[i].nodeA].vel = velNormalComp + velTangentComp ;
        }
        else {
            float massA = world.nodes[contacts[i].nodeA].mass , massB = world.nodes[contacts[i].nodeB].mass ;

            glm::vec2 normal = contacts[i].normal ;
            glm::vec2 tangent = {-contacts[i].normal.y , contacts[i].normal.x} ;

            glm::vec2 posNormalComp = glm::dot(normal , world.nodes[contacts[i].nodeA].pos) * normal ;
            glm::vec2 posTangentComp = glm::dot(tangent , world.nodes[contacts[i].nodeA].pos) * tangent ;
            posNormalComp = posNormalComp - contacts[i].penetration - 0.5f ;
            world.nodes[contacts[i].nodeA].pos = posNormalComp + posTangentComp ;

            posNormalComp = glm::dot(normal , world.nodes[contacts[i].nodeB].pos) * normal ;
            posTangentComp = glm::dot(tangent , world.nodes[contacts[i].nodeB].pos) * tangent ;
            posNormalComp = posNormalComp + contacts[i].penetration + 0.5f ;
            world.nodes[contacts[i].nodeB].pos = posNormalComp + posTangentComp ;

            glm::vec2 velNormalCompA = -glm::dot(normal , world.nodes[contacts[i].nodeA].vel) * normal ;
            glm::vec2 velTangentCompA = glm::dot(tangent , world.nodes[contacts[i].nodeA].vel) * tangent ;

            glm::vec2 velNormalCompB = glm::dot(normal , world.nodes[contacts[i].nodeB].vel) * normal ;
            glm::vec2 velTangentCompB = glm::dot(tangent , world.nodes[contacts[i].nodeB].vel) * tangent ;

            glm::vec2 tempvelA = velNormalCompA , tempvelB = velNormalCompB ;

            tempvelA = ((massA - massB) / (massA + massB)) * velNormalCompA + ((2 * massB) / (massA + massB)) * velNormalCompB;
            tempvelB = ((2 * massA) / (massA + massB)) * velNormalCompA + ((massB - massA) / (massA + massB)) * velNormalCompB;

            world.nodes[contacts[i].nodeA].vel = tempvelA + velTangentCompA ;
            world.nodes[contacts[i].nodeB].vel = tempvelB + velTangentCompB ;
        }
    }
}

void Solver::resolveBoundaryContacts(World& world , std::vector<WallContact>& contacts) {
    for(int i = 0 ; i < contacts.size() ; i++) {
        glm::vec2 normal = contacts[i].normal ;
        glm::vec2 tangent = {-contacts[i].normal.y , contacts[i].normal.x} ;

        world.nodes[contacts[i].node].pos += normal * contacts[i].penetration ;

        glm::vec2 velNormalComp = glm::dot(normal , world.nodes[contacts[i].node].vel) * normal ;
        glm::vec2 velTangentComp = glm::dot(tangent , world.nodes[contacts[i].node].vel) * tangent ;

        world.nodes[contacts[i].node].vel = -0.8f * velNormalComp + 0.8f * velTangentComp ;
    }
}

void Solver::addSpringDamping(World& world) {
    for(auto& s: world.springs) {
        Node& a = world.nodes[s.NodeA] ;
        Node& b = world.nodes[s.NodeB] ;

        glm::vec2 dir = b.pos - a.pos ;
        float len = glm::length(dir) ;

        if(len < 1e-6f) continue ;

        glm::vec2 n = dir / len ;
        float vrel = glm::dot(b.vel - a.vel , n) ;
        float dampingImpulse = s.damping * vrel ;

        if(a.isMass()) a.vel += dampingImpulse * n ;
        if(b.isMass()) b.vel -= dampingImpulse * n ;
    }
}