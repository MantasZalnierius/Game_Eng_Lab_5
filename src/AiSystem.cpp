#include "AiSystem.h"
#include "AiComponent.h"
#include "Coordinator.h"
extern Coordinator m_Coordinator;

void AiSystem::Init()
{
}

void AiSystem::Update()
{
	for (auto const& entity : mEntities)
	{
		auto& ai = m_Coordinator.getComponent<Ai>(entity);
		auto& position = m_Coordinator.getComponent<Position>(entity);

		int randomXDirection;
		int randomYDirection;

		if (ai.m_clock.getTimerAsSeconds() > 0.5f) 
		{
			int randomXDirection = rand() % 100 + 1;
			int randomYDirection = rand() % 100 + 1;

			ai.m_moveDirectionX = (randomXDirection >= 50) ? 1 : -1;
			ai.m_moveDirectionY = (randomYDirection >= 50) ? 1 : -1;

			ai.m_clock.restart();
		}

		position.m_x += ai.m_moveDirectionX;
		position.m_y += ai.m_moveDirectionY;
	}
}
