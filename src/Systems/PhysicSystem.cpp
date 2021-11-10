#include "Systems/PhysicSystem.h"
#include "Components/PositionComponent.h"
#include "ECS/EcsManager.h"
#include <iostream>

extern EcsManager m_ecsManager;

void PhysicsSystem::Init()
{
}

void PhysicsSystem::Update()
{
	for (auto const& entity : m_entities)
	{
		auto& position = m_ecsManager.getComponent<Position>(entity);

		position.m_x +=  0.05f;
		position.m_y +=  0.05f;

		std::cout << "X: " << position.m_x << std::endl;
		std::cout << "Y: " << position.m_y << std::endl;
	}
}
