#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <vector>
#include <glm/glm.hpp>


#include "physics/physics.h"
#include "renderer/renderer.h"
#include "ui/ui.h"
#include "physics/collision.h"
#include "physics/solver.h"

struct SimSettings {
    bool isPlaying ;
    bool stepOnce ;
    float timeScale ;
} ;

class App {
public:
    bool initApp() ;
    void runApp() ;
    void shutdownApp() ;

    const int screenWidth = 1280 ;
    const int screenHeight = 720 ;

private:
    Physics phy ;
    World world ;
    Renderer renderer ;
    UserInterface ui ;
    SimSettings simsets ;
    CollisionDetection cod ;
    Solver solver ;

    glm::vec2 gravity = {0.0f , 1200.0f} ;

    float accumulator = 0.0f ;
    const float fixedDT = 1.0f / 120.0f ;
    bool isRunning = true ;

    SDL_Window* window ;
    SDL_GLContext glContext ;
} ;
