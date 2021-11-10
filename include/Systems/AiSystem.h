#pragma once
#include "ECS/System.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Components/PositionComponent.h"
class AiSystem : public System
{
public:
	void Init();
	void Update();
};