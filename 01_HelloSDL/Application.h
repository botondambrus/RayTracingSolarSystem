#pragma once

#include <GL/glew.h>

#include <SDL.h>
#include <SDL_opengl.h>

#include <vector>
#include <ctime>

#include "Camera.h"
#include "SolarSystem.h"
#include "Scene.h"

class Application {
private:
    Camera* camera;
    SDL_Window* window;
    SDL_GLContext context;

    uint32_t aciveSceneIndex;
    std::vector<Scene*> scenes;

    void handle_errors(void (Application::* callback)());
    void runner();

    void initialize_graphical_context();
    void initialize_gl_debug_context();
    void initialize_window_context();
    
    void game_loop();
    
    void exit_instance();

    void update(float delta_time);
    void render();
    void switch_scenes(const SDL_KeyboardEvent& key);

    void handleKeyDownEvent(const SDL_KeyboardEvent& key);
    void handleKeyUpEvent(const SDL_KeyboardEvent& key);

public:
    Application();
    ~Application();

    void run();
};