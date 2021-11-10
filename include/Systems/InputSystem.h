#pragma once
#include "ECS/System.h"
#include <SDL.h>
class InputSystem : public System
{
public:
	void Init();
	void handleEvents(SDL_Event& t_event);
};