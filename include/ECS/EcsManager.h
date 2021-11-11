#pragma once
#include "ECS/ComponentManager.h"
#include "ECS/EntityManager.h"
#include "ECS/SystemManager.h"
#include "ECS/Entity.h"
#include <memory>
#include <iostream>
class EcsManager
{
	public:
		EcsManager()
		{
			std::cout << "ALLOCATING ECS MANAGER" << std::endl;
		}
		~EcsManager()
		{
			std::cout << "DEALLOCATING ECS MANAGER" << std::endl;
		}
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

		void destroyEntity(Entity t_entity)
		{
			m_entityManager->destroyEntity(t_entity);
			m_componentManager->entityDestroyed(t_entity);
			m_systemManager->EntityDestroyed(t_entity);
		}


		// Component methods
		template<typename T>
		void registerComponent()
		{
			m_componentManager->registerComponent<T>();
		}

		template<typename T>
		void addComponent(Entity t_entity, T t_component)
		{
			m_componentManager->addComponent<T>(t_entity, t_component);
			auto signature = m_entityManager->getSignature(t_entity);
			signature.set(m_componentManager->getComponentType<T>(), true);
			m_entityManager->setSignature(t_entity, signature);

			m_systemManager->EntitySignatureChanged(t_entity, signature);
		}

		template<typename T>
		void removeComponent(Entity t_entity)
		{
			m_componentManager->removeComponent<T>(t_entity);

			auto signature = m_entityManager->getSignature(t_entity);
			signature.set(m_componentManager->getComponentType<T>(), false);
			m_entityManager->setSignature(t_entity, signature);

			m_systemManager->EntitySignatureChanged(t_entity, signature);
		}

		template<typename T>
		T& getComponent(Entity t_entity)
		{
			return m_componentManager->getComponent<T>(t_entity);
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
		void setSystemSignature(SignatureFilter t_signature)
		{
			m_systemManager->SetSignature<T>(t_signature);
		}
	private:
		std::unique_ptr<ComponentManager> m_componentManager;
		std::unique_ptr<EntityManager> m_entityManager;
		std::unique_ptr<SystemManager> m_systemManager;
};