#include "../../Public/Particle/ParticleFireball.h"



ParticleFireball::ParticleFireball(const double& mass, const Vector3D& position, const Vector3D& velocity,
                                   const Vector3D& acceleration, const float radius) : Particle(mass,position,velocity,acceleration,radius), ATS(this,1000)
{
    
}
void ParticleFireball::Setup()
{
    Particle::Setup();
    this->SetColor(ofColor::red);
    ATS.StartAnimation();
}

void ParticleFireball::Update(clock_t f)
{
    ATS.Update(f);
    Particle::Update(f);
    
}

void ParticleFireball::Draw() const
{
    ATS.Draw();
    Particle::Draw();
}

