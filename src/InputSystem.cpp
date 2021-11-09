#include "InputSystem.h"
#include "Coordinator.h"
#include "PositionComponent.h"
#include "HealthComponent.h"
#include "InputControllerComponent.h"

extern Coordinator m_Coordinator;

void InputSystem::Init()
{
}

void InputSystem::Update(SDL_Event& t_event)
{
	for (auto const& entity : mEntities)
	{
        auto& input = m_Coordinator.getComponent<InputController>(entity);
        auto& position = m_Coordinator.getComponent<Position>(entity);
        input.m_event = t_event;
         if(input.m_event.type == SDL_KEYDOWN)
         {
            if(input.m_event.key.keysym.sym == SDLK_d)
            {
               position.m_x += 1;
            }
            if(input.m_event.key.keysym.sym == SDLK_w)
            {
               position.m_y -= 1;
            }
            if(input.m_event.key.keysym.sym == SDLK_a)
            {
               position.m_x -= 1;
            }
            if(input.m_event.key.keysym.sym == SDLK_s)
            {
               position.m_y += 1;
            }
         }
	}
}
