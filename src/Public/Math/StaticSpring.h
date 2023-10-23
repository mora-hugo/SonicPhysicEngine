﻿#pragma once
#include "ClassicSpring.h"

class StaticSpring : public Spring
{
public:
    StaticSpring() {};
    StaticSpring(GameObject* p1, GameObject* p2, double springConstant, double restlenght, double damping);
    void applyForce() override;
    
};
