#include "Systems/HealthSystem.h"
#include "ECS/EcsManager.h"
#include "Components/HealthComponent.h"

extern EcsManager m_ecsManager;

void HealthSystem::Init()
{
}

void HealthSystem::Update(SDL_Event& t_event)
{
	for (auto const& entity : m_entities)
	{
		auto& health = m_ecsManager.getComponent<Health>(entity);
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
