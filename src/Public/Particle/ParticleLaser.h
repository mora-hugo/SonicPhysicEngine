#pragma once
#include "Particle.h"
#include "Animations/AnimationTrailsSystem.h"

class ParticleLaser : public Particle
{
public:
    
    ParticleLaser(const double &mass = 1, const float lifetime = 10, const Vector3D &position = Vector3D::Zero(), const Vector3D &velocity = Vector3D::Zero(), const Vector3D &acceleration = Vector3D::Zero(), const float radius = 10);

    void Setup() override;

    void Update(double f) override;

    void Draw() const override;


    
    
    
};
