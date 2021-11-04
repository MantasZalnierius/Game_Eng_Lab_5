#pragma once
#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include "Entity.h"
#include <memory>

class Coordinator
{
	public:
		void init()
		{
			// Create pointers to each manager
			m_componentManager = std::make_unique<ComponentManager>();
			m_entityManager = std::make_unique<EntityManager>();
			m_systemManager = std::make_unique<SystemManager>();
		}

		// Entity methods
		Entity createEntity()
		{
			return m_entityManager->createEntity();
		}

		void destroyEntity(Entity entity)
		{
			m_entityManager->destroyEntity(entity);
			m_componentManager->entityDestroyed(entity);
			m_systemManager->EntityDestroyed(entity);
		}


		// Component methods
		template<typename T>
		void registerComponent()
		{
			m_componentManager->registerComponent<T>();
		}

		template<typename T>
		void addComponent(Entity entity, T component)
		{
			m_componentManager->addComponent<T>(entity, component);

			auto signature = m_entityManager->getSignature(entity);
			signature.set(m_componentManager->getComponentType<T>(), true);
			m_entityManager->setSignature(entity, signature);

			m_systemManager->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		void removeComponent(Entity entity)
		{
			m_componentManager->removeComponent<T>(entity);

			auto signature = m_entityManager->getSignature(entity);
			signature.set(m_componentManager->getComponentType<T>(), false);
			m_entityManager->setSignature(entity, signature);

			m_systemManager->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		T& getComponent(Entity entity)
		{
			return m_componentManager->getComponent<T>(entity);
		}

		template<typename T>
		ComponentType getComponentType()
		{
			return m_componentManager->getComponentType<T>();
		}


		// System methods
		template<typename T>
		std::shared_ptr<T> registerSystem()
		{
			return m_systemManager->RegisterSystem<T>();
		}

		template<typename T>
		void setSystemSignature(SignatureFilter signature)
		{
			m_systemManager->SetSignature<T>(signature);
		}
	private:
		std::unique_ptr<ComponentManager> m_componentManager;
		std::unique_ptr<EntityManager> m_entityManager;
		std::unique_ptr<SystemManager> m_systemManager;
};