#pragma once
#include "ForceGenerator.h"

class GeneratorGravity : public ForceGenerator
{
public:
    void UpdateForce(Force force) override;
    void AddForce(Force force) override;
};
