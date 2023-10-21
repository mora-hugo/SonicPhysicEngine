#include "../../Public/Particle/ParticleFireball.h"



ParticleFireball::ParticleFireball(const double& mass, const float lifetime, const Vector3D& position, const Vector3D& velocity,
                                   const Vector3D& acceleration, const float radius) : Particle(mass,lifetime, position,velocity,radius), ATS(this,6)
{
    
}
void ParticleFireball::Setup()
{
    Particle::Setup();
    this->SetColor(ofColor::red);
    ATS.StartAnimation();
}

void ParticleFireball::Update(double f)
{
    Particle::Update(f);
    ATS.Update(f);
    
}

void ParticleFireball::Draw() const
{
    Particle::Draw();
    ATS.Draw();
}

void ParticleFireball::OnAnimationFinished()
{
    Particle::OnAnimationFinished();
    //std::cout << "test" << std::endl;
    SetIsFinished(true);

}

