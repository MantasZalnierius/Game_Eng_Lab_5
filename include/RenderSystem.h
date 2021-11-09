#pragma once
#include "System.h"
#include <SDL.h>
class RenderSystem : public System
{
public:
	void Init();
	void Update();
    void Render();
};