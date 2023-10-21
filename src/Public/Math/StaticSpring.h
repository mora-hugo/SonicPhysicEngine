#pragma once
#include "ClassicSpring.h"

class StaticSpring : public ClassicSpring
{
public:
    StaticSpring();
    StaticSpring(GameObject* p1, GameObject* p2, double springConstant, double restlenght, double dampong);
    void applyForce() override;
    
};
