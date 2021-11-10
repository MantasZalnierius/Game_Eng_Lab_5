#include "ECS/EntityManager.h"
EntityManager::EntityManager()
{
    for(Entity currentEntity = 0; currentEntity < MAX_ENTITIES; ++currentEntity)
    {
        m_currentEntities.push(currentEntity);
    }
}

Entity EntityManager::createEntity()
{
    Entity id = m_currentEntities.front();
    m_currentEntities.pop();
    ++m_countOfEntities;
    return id;
}

void EntityManager::destroyEntity(Entity t_entity)
{
    // Invalidate the destroyed entity's signature
	m_signatureFilter[t_entity].reset();

    // Put the destroyed ID at the back of the queue
    m_currentEntities.push(t_entity);
    --m_countOfEntities;
}

void EntityManager::setSignature(Entity t_entity, SignatureFilter t_signature)
{
    m_signatureFilter[t_entity] = t_signature;
}

SignatureFilter EntityManager::getSignature(Entity t_entity)
{
    return m_signatureFilter[t_entity];
}