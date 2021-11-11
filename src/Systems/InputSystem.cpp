#include "Systems/InputSystem.h"
#include "ECS/EcsManager.h"
#include "Components/PositionComponent.h"
#include "Components/HealthComponent.h"
#include "Components/InputControllerComponent.h"
#include <iostream>
extern EcsManager m_ecsManager;

void InputSystem::Init()
{
}

InputSystem::InputSystem()
{
    std::cout << "ALLOCATING INPUT SYSTEM" << std::endl;
    Init();
}

InputSystem::~InputSystem()
{
    std::cout << "DEALLOCATING INPUT SYSTEM" << std::endl;
}


void InputSystem::handleEvents(SDL_Event& t_event)
{
	for (auto const& entity : m_entities)
	{
        auto& input = m_ecsManager.getComponent<InputController>(entity);
        auto& position = m_ecsManager.getComponent<Position>(entity);
        input.m_event = t_event;
         if(input.m_event.type == SDL_KEYDOWN)
         {
            if(input.m_event.key.keysym.sym == SDLK_d)
            {
               position.m_x += 3;
            }
            if(input.m_event.key.keysym.sym == SDLK_w)
            {
               position.m_y -= 3;
            }
            if(input.m_event.key.keysym.sym == SDLK_a)
            {
               position.m_x -= 3;
            }
            if(input.m_event.key.keysym.sym == SDLK_s)
            {
               position.m_y += 3;
            }
         }
	}
}
