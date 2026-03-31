#include "ui/ui.h"

void UserInterface::initUI(SDL_Window* window , SDL_GLContext glContext) {
    IMGUI_CHECKVERSION() ;
    ImGui::CreateContext() ;
    ImGuiIO& io = ImGui::GetIO() ;

    ImGui::StyleColorsDark() ;
    ImGui_ImplSDL2_InitForOpenGL(window , glContext) ;
    ImGui_ImplOpenGL3_Init("#version 130") ;
}

void UserInterface::HookUIControls(SDL_Event* event) {
    ImGui_ImplSDL2_ProcessEvent(event) ;
}

void UserInterface::renderUI(float fps , int springCount , int massCount , int hookCount , bool* isPlaying , bool* stepOnce , bool* resetSim , glm::vec2& gravity , float* timeScale) {
    ImGui_ImplOpenGL3_NewFrame() ;
    ImGui_ImplSDL2_NewFrame() ;
    ImGui::NewFrame() ;

    ImGui::Begin("Simulation Controls" , nullptr , ImGuiWindowFlags_AlwaysAutoResize) ;

    ImGui::Text("FPS : %.2f" , fps) ;
    ImGui::Text("Springs : %d" , springCount) ;
    ImGui::Text("Masses : %d" , massCount) ;
    ImGui::Text("Hooks : %d" , hookCount) ;
    ImGui::Separator() ;
 
    if(ImGui::Button(*isPlaying ? "Pause" : "Play")) *isPlaying = !(*isPlaying) ;
    ImGui::SameLine() ;
    if(ImGui::Button("Step")) *stepOnce = true ;
    ImGui::SameLine() ;
    if(ImGui::Button("Reset")) *resetSim = true ;
    ImGui::Separator() ;

    ImGui::Text("Gravity") ;
    ImGui::SliderFloat("##gravity" , &gravity.y , -2000.0f , 2000.0f , "%.1f") ;
    ImGui::Separator() ;

    ImGui::Text("TimeScale") ;
    ImGui::SliderFloat("##timescale" , timeScale , 0.1f , 2.0f , "%.2f") ;

    ImGui::End() ;

    ImGui::Render() ;
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()) ;
}

void UserInterface::shutdownUI() {
    ImGui_ImplOpenGL3_Shutdown() ;
    ImGui_ImplSDL2_Shutdown() ;
    ImGui::DestroyContext() ;
}