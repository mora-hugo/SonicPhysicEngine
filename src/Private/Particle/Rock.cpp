#include "../../Public/Particle/Rock.h"

Rock::Rock(const Vector3D& Position, int Radius) : Particle(1000, 0, Position, Vector3D::Zero(), Radius, false)
{
}

void Rock::Setup()
{
    Particle::Setup();
}

void Rock::Draw() const
{
    
    Particle::Draw();
}

void Rock::Update(double f)
{
    Particle::Update(f);
}
