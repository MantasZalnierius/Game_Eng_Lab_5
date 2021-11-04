#include "../include/Coordinator.h"
#include "../include/PhysicSystem.h"
#include "../include/PositionComponent.h"
#include <chrono>
#include <random>

Coordinator gCoordinator;

int main()
{
	gCoordinator.init();

	gCoordinator.registerComponent<Position>();

	auto physicsSystem = gCoordinator.registerSystem<PhysicsSystem>();

	SignatureFilter signature;
	signature.set(gCoordinator.getComponentType<Position>());
	gCoordinator.setSystemSignature<PhysicsSystem>(signature);

	std::vector<Entity> entities(MAX_ENTITIES);

	for (auto& entity : entities)
	{
		entity = gCoordinator.createEntity();

		gCoordinator.addComponent(
			entity,
			Position{100.0f, 100.0f});
	}

	while (true)
	{
		physicsSystem->Update();
	}
}