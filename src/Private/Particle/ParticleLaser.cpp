#include "../../Public/Particle/ParticleLaser.h"



ParticleLaser::ParticleLaser(const double& mass, const float lifetime, const Vector3D& position, const Vector3D& velocity,
                                   const Vector3D& acceleration, const float radius) : Particle(mass,lifetime, position,velocity,radius)
{
    
}
void ParticleLaser::Setup()
{
    Particle::Setup();
    this->SetColor(ofColor::red);
}

void ParticleLaser::Update(double f)
{
    Particle::Update(f);
    
}

void ParticleLaser::Draw()
{
    Particle::Draw();
}

