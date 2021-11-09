#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>
#include <SDL_ttf.h>
#include "Coordinator.h"
#include "HealthComponent.h"
#include "PositionComponent.h"
#include "RenderComponent.h"
#include "InputControllerComponent.h"
#include "RenderSystem.h"
#include "InputSystem.h"
#include "HealthSystem.h"
class Game
{
public:
    Game() = default;
    Game(const char* t_title, unsigned int t_x, unsigned int t_y, unsigned int t_width, unsigned int t_height, Uint32 t_flags);
    void update();
    void render();
    bool isRunning();
    void cleanUp();
    void run();
private:
    ~Game();
    bool m_isRunning;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    TTF_Font* m_font;
    void setUpWindow(const char* t_title, unsigned int t_x, unsigned int t_y, unsigned int t_width, unsigned int t_height, Uint32 t_flags);
    void setUpPlayer();
    void handleEvents();
    std::shared_ptr<RenderSystem> m_renderSystem;
    std::shared_ptr<InputSystem> m_inputSystem;
    std::shared_ptr<HealthSystem> m_healthSystem;
};