#pragma once
#include "ECS/System.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Components/PositionComponent.h"
#include <iostream>
class AiSystem : public System
{
public:
	AiSystem();
	~AiSystem();
	void Init();
	void Update();
};