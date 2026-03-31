#ifndef RENDERER_H
#define RENDERER_H

#include "core/world.h"
#include <SDL2/SDL_opengl.h>
#include <cmath>

class Renderer {
public:
    void initRenderer(int screenWidth , int screenHeight) ;
    void beginFrame() ;
    void drawObjects(World& world) ;
};

#endif