#pragma once
#include "System.h"
#include <cassert>
#include <memory>
#include <unordered_map>
class SystemManager
{
public:
    template<typename T>
    std::shared_ptr<T> RegisterSystem()
    {
        const char* typeName = typeid(T).name();

        auto system = std::make_shared<T>();
        m_systems.insert({ typeName, system });
        return system;
    }

    template<typename T>
    void SetSignature(SignatureFilter t_signatureFilter)
    {
        const char* typeName = typeid(T).name();

        m_signatureFliters.insert({ typeName, t_signatureFilter });
    }

    void EntityDestroyed(Entity t_entity)
    {
        for (auto const& pair : m_systems)
        {
            auto const& system = pair.second;

            system->mEntities.erase(t_entity);
        }
    }

    void EntitySignatureChanged(Entity t_entity, SignatureFilter t_entitySignature)
    {
        for (auto const& pair : m_systems)
        {
            auto const& type = pair.first;
            auto const& system = pair.second;
            auto const& systemSignature = m_signatureFliters[type];

            if ((t_entitySignature & systemSignature) == systemSignature)
            {
                system->mEntities.insert(t_entity);
            }
            else
            {
                system->mEntities.erase(t_entity);
            }
        }
    }

private:
    // Map from system type string pointer to a signature
    std::unordered_map<const char*, SignatureFilter> m_signatureFliters{};

    // Map from system type string pointer to a system pointer
    std::unordered_map<const char*, std::shared_ptr<System>> m_systems{};
};