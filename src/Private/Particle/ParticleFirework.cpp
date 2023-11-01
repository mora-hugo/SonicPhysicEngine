#include "../../Public/Particle/ParticleFirework.h"



ParticleFirework::ParticleFirework(const double& mass, const float lifetime, const Vector3D& position, const Vector3D& velocity,
                                   const Vector3D& acceleration, const float radius) : Particle(mass,lifetime, position,velocity,radius), AES(this,4,12)
{
    
}



void ParticleFirework::Setup()
{
    Particle::Setup();
    this->SetColor(ofColor::red);
    ExplosionSound.load("FireworkExplosion.wav");
}

void ParticleFirework::Update(double f)
{
    Particle::Update(f);
    AES.Update(f);
    if(!AES.ItWasPlayed() && GetLifetimeRemaining() <= 0)
    {
        //play explosion sound
        ExplosionSound.play();
        AES.StartAnimation();
    }
    
}

void ParticleFirework::Draw()
{
    
    AES.Draw();
    if(AES.ItWasPlayed()) return;
    Particle::Draw();

}

void ParticleFirework::OnAnimationFinished()
{
    Particle::OnAnimationFinished();
    //std::cout << "test" << std::endl;
    SetIsFinished(true);

}

