#include "Systems/AiSystem.h"
#include "Components/AiComponent.h"
#include "ECS/EcsManager.h"
extern EcsManager m_ecsManager;

AiSystem::AiSystem()
{
	std::cout << "ALLOACTING AI SYSTEM" << std::endl;
	Init();
}

AiSystem::~AiSystem()
{
	std::cout << "DEALLOCATING AI SYSTEM " << std::endl;
}

void AiSystem::Init()
{
}

void AiSystem::Update()
{
	for (auto const& entity : m_entities)
	{
		auto& ai = m_ecsManager.getComponent<Ai>(entity);
		auto& position = m_ecsManager.getComponent<Position>(entity);

		int randomXDirection;
		int randomYDirection;

		if (ai.m_clock.getTimerAsSeconds() > 0.5f) 
		{
			int randomXDirection = rand() % 100 + 1;
			int randomYDirection = rand() % 100 + 1;

			ai.m_moveDirectionX = (randomXDirection >= 50) ? 0.4f : -0.4f;
			ai.m_moveDirectionY = (randomYDirection >= 50) ? 0.4f : -0.4f;

			ai.m_clock.restart();
		}

		position.m_x += ai.m_moveDirectionX;
		position.m_y += ai.m_moveDirectionY;
	}
}
