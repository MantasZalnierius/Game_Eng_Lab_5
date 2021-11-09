#pragma once
#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>
#include "RectShape.h"
#include "PositionComponent.h"
#include "HealthComponent.h"

struct Renderable
{
    RectShape m_rectShape;
};