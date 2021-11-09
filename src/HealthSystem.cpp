#include "HealthSystem.h"
#include "Coordinator.h"
#include "HealthComponent.h"
extern Coordinator m_Coordinator;

void HealthSystem::Init()
{
}

void HealthSystem::Update(SDL_Event& t_event)
{
	for (auto const& entity : mEntities)
	{
		auto& health = m_Coordinator.getComponent<Health>(entity);
        if(t_event.type == SDL_KEYDOWN)
        {
            if(t_event.key.keysym.sym == SDLK_DOWN)
            {
                if((health.m_health - 1) <= 0) 
                {
                    health.m_health = 0;
                }
                else
                {
                    health.m_health--;
                }
            }
            if(t_event.key.keysym.sym == SDLK_UP)
            {
                health.m_health++;
            }
        }
	}
}
