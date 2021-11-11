#pragma once
#include "ECS/System.h"
#include <iostream>
class PhysicsSystem : public System
{
public:
	PhysicsSystem();
	~PhysicsSystem();
	void Init();
	void Update();
};