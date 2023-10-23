#pragma once
#include "Particle.h"

class BlobParticle : public Particle
{
public:
    BlobParticle(const Vector3D & Position, const Vector3D & InitialVelocity = Vector3D::Zero(), int mass = 5000) : Particle(mass, 0, Position, InitialVelocity, RADIUS, true)
    {

    }
    void Setup() override;
    void Draw() const override;
    void Update(double f) override;

    constexpr inline static float RADIUS = 10;
};


