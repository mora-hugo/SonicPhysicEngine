#pragma once
#include "Particle.h"
#include "Animations/AnimationTrailsSystem.h"

class ParticleFireball : public Particle
{
public:
    
    ParticleFireball(const double &mass = 1, const Vector3D &position = Vector3D::Zero(), const Vector3D &velocity = Vector3D::Zero(), const Vector3D &acceleration = Vector3D::Zero(), const float radius = 10);

    void Setup() override;

    void Update(clock_t f) override;

    void Draw() const override;

    

private:
    AnimationTrailsSystem ATS;
};
