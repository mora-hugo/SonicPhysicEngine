#pragma once
#include "Particle.h"

class BlobParticle : public Particle
{
public:
    BlobParticle(const Vector3D & Position, const Vector3D & InitialVelocity = Vector3D::Zero()) : Particle(10, 0, Position, InitialVelocity, Vector3D::Zero(), RADIUS)
    {

    }
    void Setup() override;
    void Draw() const override;
    void Update(double f) override;

    constexpr inline static float RADIUS = 10;
};


