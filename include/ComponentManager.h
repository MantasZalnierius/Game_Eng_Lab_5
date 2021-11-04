#pragma once
#include "ComponentArray.h"
#include "Entity.h"
#include <any>
#include <memory>
#include <unordered_map>

class ComponentManager
{
public:
    template <typename T>
    void registerComponent()
    {
        const char* typeName = typeid(T).name();
        m_componentTypes.insert({ typeName, m_nextComponentType });
        m_arrayOfComponents.insert({ typeName, std::make_shared<ConcreteComponentArray<T>>() });
        ++m_nextComponentType;
    }

    template <typename T>
    ComponentType getComponentType()
    {
        const char* typeName = typeid(T).name();
        return m_componentTypes[typeName];
    }

    template <typename T>
    void addComponent(Entity t_entity, T t_component)
    {
        GetComponentArray<T>()->insertData(t_entity, t_component);
    }

    template <typename T>
    void removeComponent(Entity t_entity)
    {
        GetComponentArray<T>()->RemoveData(t_entity);
    }

    template <typename T>
    T& getComponent(Entity t_entity)
    {
        return GetComponentArray<T>()->getData(t_entity);
    }

    void entityDestroyed(Entity t_entity)
    {
        for (auto const& pair : m_arrayOfComponents)
        {
            auto const& component = pair.second;
            component->entityDestroyed(t_entity);
        }
    }
private:
    std::unordered_map<const char*, ComponentType> m_componentTypes{};
    std::unordered_map<const char*, std::shared_ptr<ComponentArray>> m_arrayOfComponents{};
    ComponentType m_nextComponentType{};

    template <typename T>
    std::shared_ptr<ConcreteComponentArray<T>> GetComponentArray()
    {
        const char* typeName = typeid(T).name();
        return std::static_pointer_cast<ConcreteComponentArray<T>>(m_arrayOfComponents[typeName]);
    }
};
