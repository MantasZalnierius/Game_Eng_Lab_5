#pragma once
#include "ECS/Entity.h"
#include <set>


class System
{
public:
	std::set<Entity> m_entities;
};