#include "renderer/renderer.h"

void Renderer::initRenderer(int screenWidth , int screenHeight) {
    glMatrixMode(GL_PROJECTION) ;
    glLoadIdentity() ;
    glViewport(0, 0, screenWidth, screenHeight) ;
    glOrtho(0 , screenWidth , screenHeight , 0 , -1 , 1) ;
    glMatrixMode(GL_MODELVIEW) ;
}

void Renderer::beginFrame() {
    glClearColor(0.1f , 0.1f , 0.1f , 0.1f) ;
    glClear(GL_COLOR_BUFFER_BIT) ;
    glLoadIdentity() ;
}

void drawCircle(glm::vec2& pos , float radius , NodeType type) {
    const float PI = 3.141509f ;
    if(type == NodeType::Hook) glColor4f(0.769f , 0.643f , 0.518f , 1.0f) ;
    else glColor4f(1.0f , 1.0f , 1.0f , 1.0f) ;

    glBegin(GL_TRIANGLE_FAN) ;
    glVertex2f(pos.x , pos.y) ;

    for(int i = 0 ; i <= 360 ; i++) {
        float angle = i * PI / 180.0f ;
        glVertex2f(pos.x + cos(angle) * radius , pos.y + sin(angle) * radius) ;
    }
    glEnd() ;
}

void drawSpring(glm::vec2& pos1 , glm::vec2& pos2) {
    glColor4f(1.0f , 1.0f , 1.0f , 1.0f) ;
    glBegin(GL_LINES) ;
    glVertex2f(pos1.x , pos1.y) ;
    glVertex2f(pos2.x , pos2.y) ;
    glEnd() ;
}

void Renderer::drawObjects(World& world) {
    for(auto& spring : world.springs) {
        Node& a = world.nodes[spring.NodeA] ;
        Node& b = world.nodes[spring.NodeB] ;
        drawSpring(a.pos , b.pos) ;
    }

    for(auto& node : world.nodes) {
        if(node.isFixed) drawCircle(node.pos , node.radius , NodeType::Hook) ;
        else drawCircle(node.pos , node.radius , NodeType::Mass) ;
    }
}