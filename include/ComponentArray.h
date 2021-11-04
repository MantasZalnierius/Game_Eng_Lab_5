#pragma once
#include "Entity.h"
#include <array>
#include <unordered_map>
class ComponentArray
{
public:
    virtual ~ComponentArray() = default;
    virtual void entityDestroyed(Entity t_entity) = 0;
};

template<typename T>
class ConcreteComponentArray : public ComponentArray
{
public:
    void insertData(Entity t_entity, T t_component)
    {
        // Put new entry at end and update the maps
        size_t newIndex = m_size;
        m_entityToIndexMap[t_entity] = newIndex;
        m_indexToEntityMap[newIndex] = t_entity;
        m_componentArray[newIndex] = t_component;
        ++m_size;
    }

    void removeData(Entity entity)
    {
        // Copy element at end into deleted element's place to maintain density
        size_t indexOfRemovedEntity = m_entityToIndexMap[entity];
        size_t indexOfLastElement = m_size - 1;
        m_componentArray[indexOfRemovedEntity] = m_componentArray[indexOfLastElement];

        // Update map to point to moved spot
        Entity entityOfLastElement = m_indexToEntityMap[indexOfLastElement];
        m_entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
        m_indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

        m_entityToIndexMap.erase(entity);
        m_indexToEntityMap.erase(indexOfLastElement);

        --m_size;
    }

    T& getData(Entity entity)
    {
        // Return a reference to the entity's component
        return m_componentArray[m_entityToIndexMap[entity]];
    }

    void entityDestroyed(Entity entity) override
    {
        if (m_entityToIndexMap.find(entity) != m_entityToIndexMap.end())
        {
            // Remove the entity's component if it existed
            removeData(entity);
        }
    }
private:
    std::array<T, MAX_ENTITIES> m_componentArray;
    std::unordered_map<Entity, size_t> m_entityToIndexMap;
    std::unordered_map<size_t, Entity> m_indexToEntityMap;
    size_t m_size;
};
