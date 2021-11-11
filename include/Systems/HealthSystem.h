#pragma once
#include "ECS/System.h"
#include <SDL.h>
#include <iostream>
class HealthSystem : public System
{
public:
	HealthSystem();
	~HealthSystem();
	void Init();
	void Update(SDL_Event& t_event);
};