#include "app/app.h"

bool App::initApp() {
    SDL_Init(SDL_INIT_VIDEO) ;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION , 2) ;
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION , 1) ;
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK , SDL_GL_CONTEXT_PROFILE_CORE) ;

    window = SDL_CreateWindow("Hooke" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , screenWidth , screenHeight , SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE) ;
    if(window == nullptr) return false ;

    glContext = SDL_GL_CreateContext(window) ;
    if(glContext == nullptr) return false ;

    SDL_GL_MakeCurrent(window , glContext) ;
    SDL_GL_SetSwapInterval(1) ;

    //gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress) ;
    glViewport(0 , 0 , screenWidth , screenHeight) ;

    ui.initUI(window , glContext) ;
    renderer.initRenderer(screenWidth , screenHeight) ;
    world.initWorld() ;

    simsets.isPlaying = true ;
    simsets.timeScale = 1.0f ;
    simsets.stepOnce = false ;

    return true ;
}

void HandleEvents(SDL_Event* event , bool* isRunning , SDL_Window* window , UserInterface& ui) {
    while(SDL_PollEvent(event)) {
        ui.HookUIControls(event) ;
        SDL_Event event_ = *event ;
        if(event_.type == SDL_QUIT) *isRunning = false ;
        else if(event_.type == SDL_KEYDOWN) {
            if(event_.key.keysym.sym == SDLK_ESCAPE) *isRunning = false ;
        }
        else if(event_.type == SDL_WINDOWEVENT_CLOSE) {
            if(window != nullptr) {
                SDL_DestroyWindow(window) ;
                window = nullptr ;
            }
        }
    }
}

void App::runApp() {
    Uint32 lastTicks = SDL_GetTicks() ;
    glm::vec2 gravity = {0.0f , 1200.0f} ;
    std::vector<WallContact> wallContacts ;
    std::vector<BallContact> ballContacts ;
    while(isRunning) {
        SDL_Event event ;
        HandleEvents(&event , &isRunning , window , ui) ;
 
        Uint32 curTicks = SDL_GetTicks() ;
        float rawDT = (curTicks - lastTicks) / 1000.0f ;
        lastTicks = curTicks ;

        if(rawDT > 0.016f) rawDT = 0.016f ;
        if(rawDT <= 0.0f) continue ;

        if(simsets.isPlaying) accumulator += rawDT * simsets.timeScale ;
        if(simsets.stepOnce) accumulator += rawDT ;

        while(accumulator >= rawDT) {
            phy.simulate(world , fixedDT , gravity) ;
            accumulator -= fixedDT ;

            if(simsets.stepOnce) {
                simsets.stepOnce = false ;
                simsets.isPlaying = false ;
                accumulator = 0.0f ;
                break ;
            }

            cod.findContactsBetweenBallsAndBoundaries(world , wallContacts , screenWidth , screenHeight) ;
            solver.resolveBoundaryContacts(world , wallContacts) ;
            wallContacts.clear() ;

            cod.findContactsBetweenBalls(world , ballContacts) ;
            solver.resolveContacts(world , ballContacts) ;
            solver.addSpringDamping(world) ;
            ballContacts.clear() ;
        } 

        float fps = 1 / fixedDT ;
        int springCount = world.springs.size() , massCount = 0 , hookCount = 0 ;
        for(auto& node : world.nodes) {
            if(node.isFixed) hookCount++ ;
            else massCount++ ;
        }

        renderer.beginFrame() ;
        ui.renderUI(fps , springCount , massCount , hookCount , &simsets.isPlaying , &simsets.stepOnce , &ui.resetSim , gravity , &simsets.timeScale) ;
        renderer.drawObjects(world) ;
        SDL_GL_SwapWindow(window) ;
    }
}

void App::shutdownApp() {
    ui.shutdownUI() ;
    SDL_GL_DeleteContext(glContext) ;
    SDL_DestroyWindow(window) ;
    SDL_Quit() ;
}

