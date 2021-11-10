#pragma once
#include "ECS/System.h"
#include <SDL.h>
class HealthSystem : public System
{
public:
	void Init();
	void Update(SDL_Event& t_event);
};