#pragma once
#include "ECS/System.h"
#include <SDL.h>
#include <iostream>
class RenderSystem : public System
{
public:
	RenderSystem();
	~RenderSystem();
	void Init();
	void Update();
    void Render();
};