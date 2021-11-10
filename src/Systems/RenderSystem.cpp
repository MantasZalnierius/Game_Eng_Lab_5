#include "Systems/RenderSystem.h"
#include "Components/RenderComponent.h"
#include "ECS/EcsManager.h"
extern EcsManager m_ecsManager;

void RenderSystem::Init()
{

}

void RenderSystem::Update()
{
    for (auto const& entity : m_entities)
	{
		auto& rendreable = m_ecsManager.getComponent<Renderable>(entity);
        auto& position = m_ecsManager.getComponent<Position>(entity);
        auto& health = m_ecsManager.getComponent<Health>(entity);
        rendreable.m_rectShape.update(health.m_health, position.m_x, position.m_y);
	}
}

void RenderSystem::Render()
{
    for (auto const& entity : m_entities)
	{
		auto& rendreable = m_ecsManager.getComponent<Renderable>(entity);
        rendreable.m_rectShape.render();
	}
}