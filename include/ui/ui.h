#ifndef UI_H
#define UI_H

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <glm/glm.hpp>

class UserInterface {
public:
    void initUI(SDL_Window* window , SDL_GLContext glContext) ;
    void HookUIControls(SDL_Event* event) ;
    void renderUI(float fps , int springCount , int massCount , int hookCount , bool* isPlaying , bool* stepOnce , bool* resetSim , glm::vec2& gravity , float* timeScale) ;
    void shutdownUI() ;

    bool resetSim ;
};

#endif