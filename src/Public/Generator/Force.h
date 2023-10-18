#pragma once
#include "ForceGenerator.h"
#include "../../Public/Math/Vector3D.h"

class Force
{
public:
    Vector3D movement;
    double lifetime;
    Particle* particle;

    Force(const Vector3D& movement, double lifetime, Particle* particle, ForceType type);

    ForceType type;
    
};
