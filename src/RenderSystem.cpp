#include "RenderSystem.h"
#include "RenderComponent.h"
#include "Coordinator.h"
extern Coordinator m_Coordinator;

void RenderSystem::Init()
{

}

void RenderSystem::Update()
{
    for (auto const& entity : mEntities)
	{
		auto& rendreable = m_Coordinator.getComponent<Renderable>(entity);
        auto& position = m_Coordinator.getComponent<Position>(entity);
        auto& health = m_Coordinator.getComponent<Health>(entity);
        rendreable.m_rectShape.update(health.m_health, position.m_x, position.m_y);
	}
}

void RenderSystem::Render()
{
    for (auto const& entity : mEntities)
	{
		auto& rendreable = m_Coordinator.getComponent<Renderable>(entity);
        rendreable.m_rectShape.render();
	}
}