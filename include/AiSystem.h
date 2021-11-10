#pragma once
#include "System.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "PositionComponent.h"

class AiSystem : public System
{
public:
	void Init();
	void Update();
};