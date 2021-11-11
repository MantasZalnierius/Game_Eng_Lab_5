#pragma once
#include "ECS/System.h"
#include <SDL.h>
#include <iostream>
class InputSystem : public System
{
public:
	InputSystem();
	~InputSystem();
	void Init();
	void handleEvents(SDL_Event& t_event);
};