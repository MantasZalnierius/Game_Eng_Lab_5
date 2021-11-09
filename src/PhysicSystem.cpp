#include "PhysicSystem.h"
#include "PositionComponent.h"
#include "Coordinator.h"
#include <iostream>

extern Coordinator m_Coordinator;

void PhysicsSystem::Init()
{
}

void PhysicsSystem::Update()
{
	for (auto const& entity : mEntities)
	{
		auto& position = m_Coordinator.getComponent<Position>(entity);

		position.m_x +=  0.05f;
		position.m_y +=  0.05f;

		std::cout << "X: " << position.m_x << std::endl;
		std::cout << "Y: " << position.m_y << std::endl;
	}
}
