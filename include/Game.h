#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>
#include <SDL_ttf.h>
#include "ECS/EcsManager.h"
#include "Components/HealthComponent.h"
#include "Components/PositionComponent.h"
#include "Components/RenderComponent.h"
#include "Components/InputControllerComponent.h"
#include "Components/AiComponent.h"
#include "Systems/RenderSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/HealthSystem.h"
#include "Systems/AiSystem.h"

class Game
{
public:
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
    void setUpECS();
    void handleEvents();
    void setUpSystems();
    void setUpPlayer();
    void setUpVillan();
    void setUpCortana();
    void setUpDinkyDi();
    void setUpCoordinator();
    std::shared_ptr<RenderSystem> m_renderSystem;
    std::shared_ptr<InputSystem> m_inputSystem;
    std::shared_ptr<HealthSystem> m_healthSystem;
    std::shared_ptr<AiSystem> m_aiSystem;
};