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
	}
}
