#pragma once
#include "ECS/Entity.h"
#include <array>
#include <cassert>
#include <queue>
#include <iostream>
class EntityManager
{
public:
    EntityManager();
    ~EntityManager();
    Entity createEntity();
    void destroyEntity(Entity t_entity);
    void setSignature(Entity entity, SignatureFilter signature);
    SignatureFilter getSignature(Entity entity);
private:
    // Queue of unused entity IDs
    std::queue<Entity> m_currentEntities{};

    // Array of signatures where the index corresponds to the entity ID
    std::array<SignatureFilter, MAX_ENTITIES> m_signatureFilter{};

    // Total living entities - used to keep limits on how many exist
    uint32_t m_countOfEntities{};
};