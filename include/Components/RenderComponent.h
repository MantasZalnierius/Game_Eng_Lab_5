#pragma once
#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>
#include "RectShape.h"
#include "Components/PositionComponent.h"
#include "Components/HealthComponent.h"

struct Renderable
{
    RectShape m_rectShape;
};