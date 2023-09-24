#pragma once
#include "of3dPrimitives.h"
#include "Particle.h"
#include "../../Public/Math/Vector3D.h"
#include "Animations/AnimationTrailsSystem.h"

class ParticleSparksTrails : public Particle
{
public:

    ParticleSparksTrails(const double &mass = 1, const float lifetime = 10, const Vector3D &position = Vector3D::Zero(), const Vector3D &velocity = Vector3D::Zero(), const Vector3D &acceleration = Vector3D::Zero(), const float radius = 10);

    void Setup() override;
    
    void Draw() const override;

    void Update(double f) override;

    void OnAnimationFinished() override;

protected:
    AnimationTrailsSystem ATS;
};
